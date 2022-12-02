//=================================================================================================================
/**
 *  @file       nct_utils.h
 *  @brief      Utilities of the nct namespace.
 *  @details    Declaration file of utilities of the nct namespace.
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

#ifndef NCT_UTILS_H_INCLUDE
#define NCT_UTILS_H_INCLUDE

//=================================================================================================================
//        HEADERS
//=================================================================================================================
#include <nct/nct.h>
#include <nct/nct_exception.h>

#include <string>
#include <fstream>
#include <sstream>
#include <future>
#include <mutex>
#include <thread>
#include <atomic>

//=================================================================================================================
namespace nct {

////////// Functions for string manipulation //////////

/**
 *  @brief      To string.
 *  @details    This function returns a string with the representation of v.
 *  @tparam     T  The data type of the variable to be converted.
 *  @param[in]  v  Input number.
 *  @returns    The string representation of v.
 */
template<typename T>
std::string valueToString(const T& v);

/**
 *  @brief      To string.
 *  @details    This function returns a string with the representation of v.
 *  @param[in]  v  Input number.
 *  @returns    The string representation of v.
 */
NCT_EXPIMP std::string valueToString(double v, int precision);

/**
 *  @brief      To lower case.
 *  @details    This function transforms a string to its lower case representation.
 *  @param[in]  str  The string to be modified.
 *  @returns    The new string.
 */
NCT_EXPIMP std::string toLowerCase(const std::string& str);

/**
 *  @brief      To upper case.
 *  @details    This function transforms a string to its upper case representation.
 *  @param[in]  str  The string to be modified.
 *  @returns    The new string.
 */
NCT_EXPIMP std::string toUpperCase(const std::string& str);

/**
 *  @brief      Trim string.
 *  @details    This function eliminates the white spaces at the beginning and at the end of a string.
 *  @param[in]  str  The string to be trimmed.
 *  @returns    The new string.
 */
NCT_EXPIMP std::string trim(const std::string& str);

/**
 *  @brief      Trim string.
 *  @details    This function eliminates the characteres specified in the arguments at the beginning and
 *              at the end of a string.
 *  @param[in]  str  The stream to be trimmed.
 *  @param[in]  charSet  The characters to be removed.
 *  @returns    The new string.
 */
NCT_EXPIMP std::string trim(const std::string& str, const std::string& charSet);

/**
 *  @brief      Remove white spaces.
 *  @details    This function eliminates in a string the white spaces.
 *  @param[in]  str  The stream to be modified.
 *  @returns    The new string.
 */
NCT_EXPIMP std::string removeWhiteSpaces(const std::string& str);

/**
 *  @brief      Remove characteres.
 *  @details    This function eliminates in a string the characteres specified in the arguments.
 *  @param[in]  str  The stream to be modified.
 *  @param[in]  charSet  The characters to be removed.
 *  @returns    The new string.
 */
NCT_EXPIMP std::string removeCharacters(const std::string& str, const std::string& charSet);

/**
 *  @brief      Find and replace.
 *  @details    This function finds a string inside anotherone and replace all the ocurrencied with 
 *              another string.
 *  @param[in]  source  The source string.
 *  @param[in]  find  The string to find.
 *  @param[in]  replace  The string that replace the specified pattern. 
 *  @returns    The new string with the replaced elements.
 */
NCT_EXPIMP std::string findAndReplace(const std::string& source,
    const std::string& find, const std::string& replace);

/**
 *  @brief      XOR encryption.
 *  @details    This function encrypts/decrypts a byte array using the XOR algorithm.
 *  @param[in]  str  The array to encrypt.
 *  @param[in]  key  The key used for the encryption.
 *  @returns    The encrypted array.
 */
NCT_EXPIMP std::vector<unsigned char> xorEncryption(const std::vector<unsigned char>& inData, 
    const std::vector<unsigned char>& key);

/**
 *  @brief      Random hash of a 32-bit integer.
 *  @details    This function returns the random hash of an integer. This algorithm uses the mixing function
 *              of the murmur3 algorithm.
 *  @param[in]  u  Input integer.
 *  @returns    The random hash of u.
 */
NCT_EXPIMP unsigned int randomHash32(unsigned int u) noexcept;

/**
 *  @brief      Random hash of a 64-bit.
 *  @details    This function returns the random hash of an integer. This algorithm uses the mixing function
 *              of the murmur3 algorithm.
 *  @param[in]  u  Input integer.
 *  @returns    The random hash of u.
 */
NCT_EXPIMP unsigned long long randomHash64(unsigned long long u) noexcept;

/**
 *  @brief      Random hash in double format.
 *  @details    This function returns the random hash in double format of an integer.
 *  @param[in]  u  Input integer.
 *  @returns    The random hash of u.
 */
NCT_EXPIMP double randomHashDouble(unsigned long long u) noexcept;

/**
 *  @brief      Date string.
 *  @details    This function returns the string representation of the given time.
 *  @param[in]  time  The time point.
 *  @return        The date string of the specified time point.
 */
NCT_EXPIMP std::string dateString(const time_t& time);

////////// Object serialization functions //////////

/**
 *  @brief      Save in file.
 *  @details    This function saves in the specified output file one object. The input object must have
 *              implemented a write method that accepts as input argument an output stream.
 *  @tparam     Object  The data type of the object to be saved.
 *  @param[in]  obj  Object that will be saved in the output file.
 *  @param[in]  fileName  The output file name.
 */
template<typename Object>
void saveInFile(const Object& obj, const std::string& fileName);

/**
 *  @brief      Load from file.
 *  @details    This function loads an object from the specified input file. The output object class 
 *              must have implemented a read method that accepts as input argument an input stream.
 *  @tparam     Object  The data type of the object to be loaded.
 *  @param[in]  fileName  The input file name.
 *  @returns    The loaded object.
 */
template<typename Object>
Object loadFromFile(const std::string& fileName);

////////// Functions for data manipulation //////////

/**
 *  @brief      Safe cast for real numbers.
 *  @details    This function provides a safe method for casting real numbers to integer types.
 *  @tparam     IntegerType  The integer type of the result.
 *  @tparam     FloatType  The floating type of the number to be casted.
 *  @param[in]  FloatType  The floating point number to cast.
 *  @returns    The integer value equivalent to the specified real number.
 */
template<typename IntegerType, typename FloatType>
IntegerType safeCast(const FloatType& v);

/**
 *  @brief      Bounded cast for real numbers.
 *  @details    This function provides a method for casting real numbers to integer types.
 *              In case of overflow, the method returns the minimum or maximum values of the
 *              output integer type.
 *  @tparam     IntegerType  The integer type of the result.
 *  @tparam     FloatType  The floating type of the number to be casted.
 *  @param[in]  v  The floating point number to cast.
 *  @returns    The integer value equivalent to the specified real number.
 */
template<typename IntegerType, typename FloatType>
IntegerType boundedCast(const FloatType& v);

/**
 *  @brief      Swap endianness of one variable.
 *  @details    This function swaps the order of the bytes in one variable. Only use this function with
 *              ordinary data types (int, short, float, etc.). If this function is used in instances of
 *              classes or structures, an unespected behavior could be observed.
 *  @tparam     T  The data type of the variable whose endianness will be swapped.
 *  @param [in,out]    v  The variable to be modified.
 */
template<typename T>
inline void swapEndian(T& v) noexcept;

/**
 *  @brief      Is little endian?
 *  @details    This function returns true if the system is little endian. Otherwise, this function
 *              returns false.
 *  @return     True, if the system is little endian, false if not.
 */
NCT_EXPIMP constexpr bool isLittleEndian() noexcept;

/**
 *  @brief      Is big endian?
 *  @details    This function returns true if the system is big endian. Otherwise, this function returns
 *              false.
 *  @return     True, if the system is big endian, false if not.
 */
NCT_EXPIMP constexpr bool isBigEndian() noexcept;

/**
 *  @brief      Is scalar numeric type.
 *  @details    This function returns whether a type name represents a scalar numeric type.
 *              Complex or vectors are not considered scalar values.
 *  @param[in]  t  The string that represents the data type.
 *  @return     True, if the type name is a scalar number.
 */
NCT_EXPIMP bool isScalarNumericType(const std::string& t);

/**
 *  @brief      Type alias.
 *  @details    This function returns an alias (if exists) of the specified data type name.
 *  @param[in]  t  The string that represents the data type.
 *  @return     The alias of the data type name.
 */
NCT_EXPIMP std::string numericTypeAlias(const std::string& t);

/**
 *  @brief      Compare basic type names.
 *  @details    This function compares the names of two data types and returns true if both
 *              types are the same. This function is usefull when one type name refers to one known
 *              alias (i. e. uint8 instead of unsigned int).
 *  @return     True if both types are the same.
 */
NCT_EXPIMP bool compareNumericTypeNames(const std::string& t1,
    const std::string& t2);

/**
 *  @brief      Numeric type size.
 *  @details    This function returns the size in bytes of the specified numeric type.
 *  @param[in]  t  The string that represents the data type.
 *  @return     The size in bytes of the data type. If the data type was not recognized,
 *              this function returns 0.
 */
NCT_EXPIMP size_t numericTypeSize(const std::string& t);


////////// Functions that control the excecution of the program //////////

/**
 *  @brief      Stop.
 *  @details    This function stops the execution of a program.
 */
NCT_EXPIMP void stop();

/**
 *  @brief      Sleep.
 *  @details    This function stops the execution of a program for the specified number of seconds.
 *  @param[in]  seconds  The seconds that the execution is going to be stoped.
 */
NCT_EXPIMP void sleep(double seconds) noexcept;

/**
 *  @brief      Parallel for.
 *  @details    This helper function calls an indexed functor multiple times in separated threads.
 *  @note       In case of an exception inside a thread, this function cancels the rest of invocations
 *              and produces only one exception indicating the index that failed in the execution.
 *  @tparam     IntegerType  The type of index variable.
 *  @tparam     FunctionType  The type of function to be executed in parallel.
 *  @param[in]  first  The first index to be included in the iteration.
 *  @param[in]  last  The index one past the last index to be included in the iteration.
 *  @param[in]  f  The function to invoke. It must be a callabe object that takes as argument 
 *              an integer.
 */
template<typename IntegerType, typename FunctionType> 
requires std::integral<IntegerType> && std::invocable<FunctionType, IntegerType>
void parallel_for(IntegerType first, IntegerType last, FunctionType f);

}

////////// Template and inline functions //////////
#include <nct/nct_utils_template.h>

#endif
//=================================================================================================================
//        END OF FILE
//=================================================================================================================
