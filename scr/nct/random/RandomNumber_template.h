//=================================================================================================================
/**
 *  @file       RandomNumber_template.h
 *  @brief      nct::random::RandomNumber class implementation file.
 *  @details    This file contains the implementation of template methods of 
 *              the nct::random::RandomNumber class.
 *  @author     Omar Mendoza Montoya (email: omendoz@live.com.mx).
 *  @copyright  Copyright (c) 2012 Omar Mendoza Montoya \n \n
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
//        MEMBER FUNCTIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
inline constexpr unsigned long long nct::random::RandomNumber::min() noexcept
{
    return 0;
}

//-----------------------------------------------------------------------------------------------------------------
inline constexpr unsigned long long nct::random::RandomNumber::max() noexcept
{
    return UINT64_MAX;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename OutIt, std::integral IntType>
requires std::output_iterator<OutIt, IntType>
void nct::random::RandomNumber::randomPermutation(OutIt out, IntType n,
    RandomNumber& secGenerator)
{
    if (n <= 0)
        return;

    for (IntType i = 0; i<n; i++)
        out[i] = static_cast<typename std::remove_cvref_t<decltype(*out)>>(i);
        
    for (IntType i=(n-1); i>0; --i) {
        auto index = static_cast<IntType>((i+1)*secGenerator.random());
        if (index == (i+1))
            index--;        
        std::swap(out[i], out[index]);        
    }
}

//-----------------------------------------------------------------------------------------------------------------
template<std::input_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type>
void nct::random::RandomNumber::randomPermutation(OutIt out, 
    InputIt begin, InputIt end, RandomNumber& secGenerator)
{
    auto n = end - begin;
    if (n <= 0)
        return;

    std::copy(begin, end, out);
        
    for (decltype(n) i=(n-1); i>0; --i) {
        auto index = static_cast<decltype(n)>((i+1)*secGenerator.random());
        if (index == (i+1))
            index--;
        std::swap(out[i], out[index]);    
    }
}

//-----------------------------------------------------------------------------------------------------------------
template<typename OutIt, std::integral IntType>
requires std::output_iterator<OutIt, IntType>
void nct::random::RandomNumber::randomPermutations(OutIt out, IntType n, size_t m,
    RandomNumber& secGenerator)
{
    if ((n <= 0) || (m <= 0))
        return;

    for (size_t p = 0; p<m; p++) {
        for (IntType i = 0; i<n; i++)
            out[n*p + i] = static_cast<typename std::remove_cvref_t<decltype(*out)>>(i);

        for (IntType i=(n-1); i>0; --i) {
            auto index = static_cast<IntType>((i+1)*secGenerator.random());
            if (index == (i+1))
                index--;
            std::swap(out[n*p + i], out[n*p + index]);            
        }
    }
}

//-----------------------------------------------------------------------------------------------------------------
template<std::input_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type>
void nct::random::RandomNumber::randomPermutations(OutIt out,
    InputIt begin, InputIt end, size_t m, RandomNumber& secGenerator)
{
    auto n = end - begin;
    if ((n <= 0) || (m <= 0))
        return;

    for (size_t p = 0; p<m; p++) {
        std::copy(begin, end, out + n*p);    
    
        for (decltype(n) i=(n-1); i>0; --i) {
            auto index = static_cast<decltype(n)>((i+1)*secGenerator.random());
            if (index == (i+1))
                index--;
            std::swap(out[n*p + i], out[n*p + index]);        
        }
    }
}

//-----------------------------------------------------------------------------------------------------------------
template<typename OutIt, std::integral IntType>
requires std::output_iterator<OutIt, IntType>
void nct::random::RandomNumber::resampling(OutIt out, IntType n,
    size_t m, RandomNumber& secGenerator)
{
    if ((n <= 0) || (m <= 0))
        return;

    for (size_t i=0; i<m; i++) {
        auto index = static_cast<size_t>(n*secGenerator.random());
        if (index == n)
            index--;        
        out[i] = static_cast<typename std::remove_cvref_t<decltype(*out)>>(index);
    }
}

//-----------------------------------------------------------------------------------------------------------------
template<std::input_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type>
void nct::random::RandomNumber::resampling(OutIt out, 
    InputIt begin, InputIt end, size_t m, RandomNumber& secGenerator)
{
    auto n = end - begin;
    if ((n <= 0) || (m <= 0))
        return;
    
    for (size_t i=0; i<m; i++) {
        auto index = static_cast<decltype(n)>(n*secGenerator.random());
        if (index == n)
            index--;        
        out[i] = static_cast<typename std::remove_cvref_t<decltype(*out)>>(begin[index]);
    }
}

//-----------------------------------------------------------------------------------------------------------------
template<typename OutIt, std::integral IntType>
requires std::output_iterator<OutIt, IntType>
void nct::random::RandomNumber::balancedResampling(OutIt out, IntType n, size_t m,
    RandomNumber& secGenerator)
{
    if ((n <= 0) || (m <= 0))
        return;

    for (size_t r = 0; r<m; r++)
        for (IntType i = 0; i<n; i++)
            out[n*r + i] = static_cast<typename std::remove_cvref_t<decltype(*out)>>(i);

    n*=m;
    for (IntType i=(n-1); i>0; --i) {
        auto index = static_cast<IntType>((i+1)*secGenerator.random());
        if (index == (i+1))
            index--;
        std::swap(out[i], out[index]);        
    }
}

//-----------------------------------------------------------------------------------------------------------------
template<std::input_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type>
void nct::random::RandomNumber::balancedResampling(OutIt out, 
    InputIt begin, InputIt end, size_t m, RandomNumber& secGenerator)
{
    auto n = end - begin;
    if ((n <= 0) || (m <= 0))
        return;
    
    for (size_t r = 0; r<m; r++)
        std::copy(begin, end, out + n*r);    

    n*=m;
    for (decltype(n) i=(n-1); i>0; --i) {
        auto index = static_cast<decltype(n)>((i+1)*secGenerator.random());
        if (index == (i+1))
            index--;
        std::swap(out[i], out[index]);        
    }
}

//=================================================================================================================
//        END OF FILE
//=================================================================================================================