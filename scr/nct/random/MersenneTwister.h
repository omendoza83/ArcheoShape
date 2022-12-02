//=================================================================================================================
/**
 *  @file       MersenneTwister.h
 *  @brief      nct::random::MersenneTwister class.
 *  @details    Declaration file of the nct::random::MersenneTwister class.
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

#ifndef NCT_MERSENE_TWISTER_H_INCLUDE
#define NCT_MERSENE_TWISTER_H_INCLUDE

//=================================================================================================================
//        HEADERS
//=================================================================================================================
#include <nct/random/RandomNumber.h>
#include <vector>

//=================================================================================================================
namespace nct {
namespace random {

/**
 *  @brief      Mersenne twister algorithm for 64-bit words.
 *  @details    This class generates pseudo-random numbers by using the 64-bit Mersenne twister 19937
 *              algorithm.
 */
class NCT_EXPIMP MersenneTwister final : public RandomNumber {

public:

    ////////// Constructors //////////

    /**
     *  @brief      Default constructor.
     *  @details    This constructor initializes an instance of this class using the specified arguments.
     *  @param[in]  s  The seed used to initialize the random sequence.
     *  @param[in]  n  The number of state elements in the sequence.
     *  @param[in]  m  The shift size on twists.
     *  @param[in]  r  The number of bits that mark the separation point of words.
     *  @param[in]  a  The XOR mask to apply.
     *  @param[in]  tu  Tempering shift parameter.
     *  @param[in]  td  Tempering bitmask parameter.
     *  @param[in]  ts  Tempering shift parameter.
     *  @param[in]  tb  Tempering bitmask parameter.
     *  @param[in]  tt  Tempering shift parameter.
     *  @param[in]  tc  Tempering bitmask parameter.
     *  @param[in]  tl  Tempering shift parameter.
     *  @param[in]  f  The initialization multiplier.
     */
    explicit MersenneTwister(unsigned long long s = std::time(0), 
        size_t n = 312, size_t m = 156, unsigned long long r = 31,
        unsigned long long a = 0xb5026f5aa96619e9ULL, unsigned long long tu = 29, 
        unsigned long long td = 0x5555555555555555ULL, unsigned long long ts = 17, 
        unsigned long long tb = 0x71d67fffeda60000ULL, unsigned long long tt = 37,
        unsigned long long tc = 0xfff7eee000000000ULL, unsigned long long tl = 43,
        unsigned long long f = 6364136223846793005ULL) noexcept;
            
    ////////// Operators //////////   

    /**
     *  @brief      Generate random number.
     *  @details    This operator returns a new pseudo-random number.
     *  @returns    The new generated number.
     */
    unsigned long long operator()() noexcept override;

    ////////// Member functions //////////

    /**
     *  @brief      Reset state.
     *  @details    This function resets the state of the engine and sets all the parameters of the
     *              generator.
     *  @param[in]  s  The seed used to initialize the random sequence.
     *  @param[in]  s  The seed used to initialize the random sequence.
     *  @param[in]  n  The number of state elements in the sequence.
     *  @param[in]  m  The shift size on twists.
     *  @param[in]  r  The number of bits that mark the separation point of words.
     *  @param[in]  a  The XOR mask to apply.
     *  @param[in]  tu  Tempering shift parameter.
     *  @param[in]  td  Tempering bitmask parameter.
     *  @param[in]  ts  Tempering shift parameter.
     *  @param[in]  tb  Tempering bitmask parameter.
     *  @param[in]  tt  Tempering shift parameter.
     *  @param[in]  tc  Tempering bitmask parameter.
     *  @param[in]  tl  Tempering shift parameter.
     *  @param[in]  f  The initialization multiplier.
     */
    void reset(unsigned long long s = std::time(0), 
        size_t n = 312, size_t m = 156, unsigned long long r = 31,
        unsigned long long a = 0xb5026f5aa96619e9ULL, unsigned long long tu = 29,
        unsigned long long td = 0x5555555555555555ULL, unsigned long long ts = 17,
        unsigned long long tb = 0x71d67fffeda60000ULL, unsigned long long tt = 37,
        unsigned long long tc = 0xfff7eee000000000ULL, unsigned long long tl = 43,
        unsigned long long f = 6364136223846793005ULL) noexcept;

    /**
     *  @brief      Reset state.
     *  @details    This function resets the state of the generator and sets the seed with a new value.
     *  @param[in]  s The new seed.
     */
    void seed(unsigned long long s = std::time(0)) noexcept override;

    /**
     *  @brief      Discard n numbers.
     *  @details    This function discard the next n numbers of the random sequence.
     *  @param[in]  n  The total of numbers to be discarded.
     */
    void discard(unsigned long long n) noexcept override;
    
    /**
     *  @brief      Random number.
     *  @details    This function returns the next random number in double format (between 0 and 1). 
     *  @returns    The next number in the sequence.
     */
    double random() noexcept override;

    /**
     *  @brief      Random number.
     *  @details    This function returns the next random number in float format (between 0 and 1). 
     *  @returns    The next number in the sequence.
     */
    float randomFloat() noexcept override;

    /**
     *  @brief      Random number.
     *  @details    This function returns the next random number in UINT64 format (between 0 and (2^64 - 1)). 
     *  @returns    The next number in the sequence.
     */
    unsigned long long randomUInt64() noexcept override;

    /**
     *  @brief      Random number.
     *  @details    This function returns the next random number in UINT32 format (between 0 and (2^32 - 1)). 
     *  @returns    The next number in the sequence.
     */
    unsigned int randomUInt32() noexcept override;

    /**
     *  @brief      Random number.
     *  @details    This function returns the next random number in UINT16 format (between 0 and (2^16 - 1)). 
     *  @returns    The next number in the sequence.
     */
    unsigned short randomUInt16() noexcept override;

    /**
     *  @brief      Random number.
     *  @details    This function returns the next random number in UINT8 format (between 0 and (2^8 - 1)). 
     *  @returns    The next number in the sequence.
     */
    unsigned char randomUInt8() noexcept override;

private:

    /**
     *  @brief      Twist values.
     *  @details    This function twist the elements of the twisted array.
     */
    void twist();
        
    ////////// Data members //////////

    unsigned long long state_ {0};      /**< Current state of the generator. */

    char ui32Counter_ {0};              /**< Counter to generate numbers in UInt32 format. */

    char ui16Counter_ {0};              /**< Counter to generate numbers in UInt16 format. */

    char ui8Counter_ {0};               /**< Counter to generate numbers in UInt8 format. */

    std::vector<unsigned long long> twisted_;       /** Array of twisted values. */

    size_t n_ {0};                      /**< The number of state elements in the sequence. */

    size_t m_ {0};                      /**< The shift size on twists. */

    size_t firstHalf_ {0};              /** n - m. */

    size_t index_ {0};                  /** Index of the next table element. */

    unsigned long long r_ {0};          /**< The number of bits that mark the separation point of 
                                             words on each twist. */
    unsigned long long a_ {0};          /**< The XOR mask applied on each twist. */

    unsigned long long tu_ {0};         /**< Tempering shift parameter for the scrambling operation. */

    unsigned long long td_ {0};         /**< Tempering bitmask parameter for the scrambling operation. */

    unsigned long long ts_ {0};         /**< Tempering shift parameter for the scrambling operation. */

    unsigned long long tb_ {0};         /**< Tempering bitmask parameter for the scrambling operation. */

    unsigned long long tt_ {0};         /**< Tempering shift parameter for the scrambling operation. */

    unsigned long long tc_ {0};         /**< Tempering bitmask parameter for the scrambling operation. */

    unsigned long long tl_ {0};         /**< Tempering shift parameter for the scrambling operation. */

    unsigned long long f_ {0};          /**< Initialization multiplier. */

    unsigned long long hmask_ {0};      /**< Mask for the most significant bits. */

    unsigned long long lmask_ {0};      /**< Mask for the less significant bits. */

};

}}


#endif
//=================================================================================================================
//        END OF FILE
//=================================================================================================================
