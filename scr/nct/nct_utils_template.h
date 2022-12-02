//=================================================================================================================
/**
 *  @file       nct_utils_template.h
 *  @brief      Utility function templates of the nct namespace.
 *  @details    Implementation of function templates of the nct namespace.
 *  @author     Omar Mendoza Montoya (email: omendoz@live.com.mx).
 *  @copyright  Copyright (c) 2010 Omar Mendoza Montoya \n \n
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 *  associated documentation files (the "Software"), to deal in the Software without restriction,  
 *  including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,  
 *  and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, 
 *  subject to the following conditions: \n
 *  The above copyright notice and this permission notice shall be included in all copies or substantial 
 *  portions of the Software. \n
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 *  LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 *  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 *  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
//=================================================================================================================

//=================================================================================================================
//       FUNCTIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<typename T>
std::string nct::valueToString(const T& v)
{
    std::stringstream stream;
    stream << v;
    return stream.str();
}

//-----------------------------------------------------------------------------------------------------------------
template<typename Object>
void nct::saveInFile(const Object& obj, const std::string& fileName)
{
    std::ofstream outStream;

    outStream.open(fileName.c_str(), std::ios::binary);
    if (outStream.fail())
        throw IOException(fileName, exc_error_opening_file, SOURCE_INFO);

    try {
        obj.write(outStream);
        if (outStream.fail())
            throw IOException(fileName, exc_error_writing_data, SOURCE_INFO);
    }
    catch (const nct_exception& ex) {
        throw IOException(fileName, SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (const std::exception& ex) {
        throw IOException(fileName, SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (...) {
        throw IOException(fileName, SOURCE_INFO);
    }

    outStream.close();
}

//-----------------------------------------------------------------------------------------------------------------
template<typename Object>
Object nct::loadFromFile(const std::string& fileName)
{
    std::ifstream inStream;

    inStream.open(fileName.c_str(), std::ios::binary);
    if (inStream.fail())
        throw IOException(fileName, exc_error_opening_file, SOURCE_INFO);

    Object obj;
    try {
        obj = Object::read(inStream);
        if (inStream.fail())
            throw IOException(fileName, exc_error_reading_input_file, SOURCE_INFO);
    }
    catch (const nct_exception& ex) {
        throw IOException(fileName, SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (const std::exception& ex) {
        throw IOException(fileName, SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (...) {
        throw IOException(fileName, SOURCE_INFO);
    }

    inStream.close();
    return obj;
}


//-----------------------------------------------------------------------------------------------------------------
template<typename IntegerType, typename FloatType>
IntegerType nct::safeCast(const FloatType& v)
{
    if constexpr (std::numeric_limits<IntegerType>::digits > std::numeric_limits<FloatType>::digits)
        throw ArgumentException("v", exc_bad_precision_for_safe_cast, SOURCE_INFO);

    if (v < static_cast<FloatType>(std::numeric_limits<IntegerType>::min()))
        throw ArgumentException("v", exc_value_under_lower_limit_in_safe_cast, SOURCE_INFO);

    if (v > static_cast<FloatType>(std::numeric_limits<IntegerType>::max()))
        throw ArgumentException("v", exc_value_above_upper_limit_in_safe_cast, SOURCE_INFO);

    return static_cast<IntegerType>(v);    
}

//-----------------------------------------------------------------------------------------------------------------
template<typename IntegerType, typename FloatType>
IntegerType nct::boundedCast(const FloatType& v)
{
    auto maxVal = static_cast<FloatType>(std::numeric_limits<IntegerType>::max());
    auto minVal = static_cast<FloatType>(std::numeric_limits<IntegerType>::min());

    if (static_cast<IntegerType>(maxVal) != std::numeric_limits<IntegerType>::max())
        maxVal = std::nexttoward(maxVal, (FloatType)-1);

    if (static_cast<IntegerType>(minVal) != std::numeric_limits<IntegerType>::min())
        minVal = std::nexttoward(minVal, (FloatType)1);

    if (v < minVal)
        return std::numeric_limits<IntegerType>::min();

    if (v > maxVal)
        return std::numeric_limits<IntegerType>::max();

    return static_cast<IntegerType>(v);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T>
inline void nct::swapEndian(T& v) noexcept
{
    auto size = sizeof(v);
    T v2 = v;
    char* c = reinterpret_cast<char*>(&v); 
    char* c2 = reinterpret_cast<char*>(&v2); 
    for (index_t i=0; i<size; i++)
        c[i] = c2[size-i-1];
}

//-----------------------------------------------------------------------------------------------------------------
constexpr bool nct::isLittleEndian() noexcept
{
    union {
        unsigned short s;                       // [______16______]
        unsigned char c[sizeof(short)];         // [___8__][___8__]
    } endianness {.s = 0xFF00};

    return (endianness.c[0] == 0x00 && endianness.c[1] == 0xFF);
}

//-----------------------------------------------------------------------------------------------------------------
constexpr bool nct::isBigEndian() noexcept
{
    union {
        unsigned short s;                       // [______16______]
        unsigned char c[sizeof(short)];         // [___8__][___8__]
    } endianness {.s = 0xFF00};

    return (endianness.c[0] == 0xFF && endianness.c[1] == 0x00);
}

//-----------------------------------------------------------------------------------------------------------------
template <typename IntegerType, typename FunctionType>
requires std::integral<IntegerType> && std::invocable<FunctionType, IntegerType>
void nct::parallel_for(IntegerType first, IntegerType last, FunctionType f)
{
    if (last <= first)
        return;

    auto n = last - first;
    auto maxThreads = static_cast<IntegerType>(std::thread::hardware_concurrency() > 0 ?
        std::thread::hardware_concurrency() : 1);
    auto steps = n / maxThreads + (n % maxThreads > 0);
    auto i = first;

    for (IntegerType step = 0; step < steps; step++) {

        std::atomic<bool> exceptionFlag = false;
        std::atomic<size_t> exceptionIndex = 0;
        std::exception_ptr exception = nullptr;
        std::list<std::future<void>> futureList;

        for (IntegerType j = 0; (j < maxThreads) && (i < last); i++, j++) {
            futureList.push_back(std::async(std::launch::async, [&] (IntegerType i) -> void {

                if (!exceptionFlag) {
                    try {
                        f(i);
                    }
                    catch (...) {
                        exceptionFlag = true;
                        exceptionIndex = i;
                        exception = std::current_exception();
                    }
                }

             }, i));
        }

        for (auto& fli : futureList)
            fli.get();

        if (exception) {
            throw OperationException(exc_error_invoking_function, exceptionIndex, 
                SOURCE_INFO, exception);
        }
    }
}

//=================================================================================================================
//        END OF FILE
//=================================================================================================================

