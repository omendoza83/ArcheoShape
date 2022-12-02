//=================================================================================================================
/**
 *  @file       RandomNumber.h
 *  @brief      nct::random::RandomNumber abstract class.
 *  @details    Declaration file of the nct::random::RandomNumber class.
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

#ifndef NCT_RANDOM_NUMBER_H_INCLUDE
#define NCT_RANDOM_NUMBER_H_INCLUDE

//=================================================================================================================
//        HEADERS
//=================================================================================================================
#include <nct/nct.h>
#include <nct/nct_exception.h>

#include <ctime>

//=================================================================================================================
namespace nct {
/**
 *  @brief      Random number generators.
 *  @details    This namespace contains classes that are used to generate pseudo-random numbers.
 */
namespace random {
/**
 *  @brief      Base class for pseudo-random number generators.
 *  @details    This abstract base class is used as base class of pseudo-random number generators. 
 */

class NCT_EXPIMP RandomNumber {

public:

    ////////// Definitions //////////
    
    /* The following definition is required to consider the random number generators of this
       library as Uniform Random Bit Generators. */

    using result_type = unsigned long long;     /**< The result type of the generator. */

    ////////// Constructors //////////
    
    /**
     *  @brief      Default constructor.
     *  @details    This constructor initializes an instance of this class using the default configuration.
     */
    RandomNumber() noexcept = default;

    /**
     *  @brief      Copy constructor.
     *  @details    This constructor is deleted.
     */
    RandomNumber(const RandomNumber&) = delete;
    
    /**
     *  @brief      Move constructor.
     *  @details    This constructor moves the contents of an object to the new class instance.
     *  @param[in]  other  Another object of the same type whose contents are acquired.
     */
    RandomNumber(RandomNumber&& other) noexcept = default;
    
    ////////// Destructor //////////

    /**
     *  @brief      Destructor.
     *  @details    Class destructor. 
     */
    virtual ~RandomNumber() noexcept = default;

    ////////// Operators //////////        
    
    /**
     *  @brief      Assignment operator.
     *  @details    This operator is deleted.
     *  @returns    N/A.
     */
    RandomNumber& operator=(const RandomNumber&) = delete;
    
    /**
     *  @brief      Move-assignment operator.
     *  @details    This operator acquires the contents of another object.
     *  @param[in]  other  Another object of the same type whose contents are acquired.
     *  @returns    A reference to the object.
     */
    RandomNumber& operator=(RandomNumber&& other) noexcept = default;

    /**
     *  @brief      Generate random number.
     *  @details    This operator returns a new pseudo-random number.     
     *  @returns    The new generated number.
     */
    virtual unsigned long long operator()() noexcept = 0;

    ////////// Member functions //////////

    /**
     *  @brief      Reset state.
     *  @details    This function resets the state of the generator and sets the seed with a new value.
     *  @param[in]  s The new seed.
     */
    virtual void seed(unsigned long long s = std::time(0)) noexcept = 0;

    /**
     *  @brief      Discard n numbers.
     *  @details    This function discard the next n numbers of the random sequence.
     *  @param[in]  n  The total of numbers to be discarded.
     */
    virtual void discard(unsigned long long n) noexcept = 0;

    /**
     *  @brief      Random number.
     *  @details    This function returns the next random number in double format (between 0 and 1). 
     *  @returns    The next number in the sequence.
     */
    virtual double random() noexcept = 0;

    /**
     *  @brief      Random number.
     *  @details    This function returns the next random number in float format (between 0 and 1). 
     *  @returns    The next number in the sequence.
     */
    virtual float randomFloat() noexcept = 0;

    /**
     *  @brief      Random number.
     *  @details    This function returns the next random number in UINT64 format (between 0 and (2^64 - 1)). 
     *  @returns    The next number in the sequence.
     */
    virtual unsigned long long randomUInt64() noexcept = 0;

    /**
     *  @brief      Random number.
     *  @details    This function returns the next random number in UINT32 format (between 0 and (2^32 - 1)). 
     *  @returns    The next number in the sequence.
     */
    virtual unsigned int randomUInt32() noexcept = 0;

    /**
     *  @brief      Random number.
     *  @details    This function returns the next random number in UINT16 format (between 0 and (2^16 - 1)). 
     *  @returns    The next number in the sequence.
     */
    virtual unsigned short randomUInt16() noexcept = 0;

    /**
     *  @brief      Random number.
     *  @details    This function returns the next random number in UINT8 format (between 0 and (2^8 - 1)). 
     *  @returns    The next number in the sequence.
     */
    virtual unsigned char randomUInt8() noexcept = 0;

    /**
     *  @brief      Smallest possible value.
     *  @details    This function returns the smallest possible value in the output range of the generators.
     *  @returns    The smallest possible value that the generators can produce. This
     *              value is equal to 0u.
     */
    static constexpr unsigned long long min() noexcept;

    /**
     *  @brief      Largest possible value.
     *  @details    This function returns the largest possible value in the output range of the generators.
     *  @returns    The largest possible value that the generators can produce This
     *              value is equal to FFFFFFFFFFFFFFFFu.
     */
    static constexpr unsigned long long max() noexcept;

    /**
     *  @brief      Random permutation.
     *  @details    This function computes a random permutation of the numbers from 0 to n-1.
     *  @tparam     OutIt  The iterator type to be used to store the result.
     *  @tparam     IntType  The integer type that will define the numbers to permute.
     *  @param[out] out  Output iterator to the initial position in the destination sequence.
     *  @param[in]  n  Number of elements to permute.
     *  @param[in, out] secGenerator  Sequential number generator.
     */
    template<typename OutIt, std::integral IntType> 
    requires std::output_iterator<OutIt, IntType>
    static void randomPermutation(OutIt out, IntType n, RandomNumber& secGenerator);

    /**
     *  @brief      Random permutation.
     *  @details    This function computes a random permutation of the n elements of a sequence
     *              and places the result in another container.
     *  @tparam     InputIt  The iterator type to be used to traverse the elements to permute.
     *  @tparam     OutIt  The iterator type to be used to store the result.
     *  @param[out] out  Output iterator to the initial position in the destination sequence.
     *  @param[in]  begin  Input iterator to the initial position in the source sequence.
     *  @param[in]  end  Input iterator to the final position in the source sequence.
     *  @param[in, out] secGenerator  Sequential number generator.
     */
    template<std::input_iterator InputIt, typename OutIt>
    requires std::output_iterator<OutIt, typename InputIt::value_type>
    static void randomPermutation(OutIt out, InputIt begin, InputIt end,
        RandomNumber& secGenerator);

    /**
     *  @brief      Random permutations.
     *  @details    This function computes m random permutations of the numbers from 0 to n-1. 
     *  @tparam     OutIt  The iterator type to be used to store the result.
     *  @tparam     IntType  The integer type that will define the numbers to permute.
     *  @param[out] out  Output iterator to the initial position in the destination sequence. Each of the
     *              m permutations are stored in sequence in this container. The first n elements
     *              correspond to the first permutation, the second n elements correspond to the
     *              second permutation and so forth. The total of elements to be calculated are n x m.     
     *  @param[in]  n  Number of elements to permute.
     *  @param[in]  m  Number of random permutations.
     *  @param[in, out] secGenerator  Sequential number generator.
     */
    template<typename OutIt, std::integral IntType> 
    requires std::output_iterator<OutIt, IntType>
    static void randomPermutations(OutIt out, IntType n, size_t m, RandomNumber& secGenerator);

    /**
     *  @brief      Random permutations.
     *  @details    This function computes m random permutations of the n elements of a sequence
     *              and places the result in another container.
     *  @tparam     InputIt  The iterator type to be used to traverse the elements to permute.
     *  @tparam     OutIt  The iterator type to be used to store the result.
     *  @tparam     IntType  The integer type that will define the numbers to permute.
     *  @param[out] out  Output iterator to the initial position in the destination sequence. Each of the
     *              m permutations are stored in sequence in this container. The first n elements
     *              correspond to the first permutation, the second n elements correspond to the
     *              second permutation and so forth. The total of elements to be calculated are n x m.
     *  @param[in]  n  Number of elements to permute.
     *  @param[in]  begin  Input iterator to the initial position in the source sequence.
     *  @param[in]  end  Input iterator to the final position in the source sequence.
     *  @param[in]  m  Number of random permutations.
     *  @param[in, out] secGenerator  Sequential number generator.
     */
    template<std::input_iterator InputIt, typename OutIt>
    requires std::output_iterator<OutIt, typename InputIt::value_type>
    static void randomPermutations(OutIt out, InputIt begin, InputIt end,
        size_t m, RandomNumber& secGenerator);

    /**
     *  @brief      Resampling.
     *  @details    This function samples with replacement m times the numbers from 0 to n-1.
     *  @tparam     OutIt  The iterator type to be used to store the result.
     *  @tparam     IntType  The integer type that will define the numbers to permute.
     *  @param[out] out  Output iterator to the initial position in the destination sequence. 
     *  @param[in]  n  Number of elements to sample.
     *  @param[in]  m  Number of random samples.
     *  @param[in, out] secGenerator  Sequential number generator.
     */
    template<typename OutIt, std::integral IntType>
    requires std::output_iterator<OutIt, IntType>
    static void resampling(OutIt out, IntType n, size_t m, RandomNumber& secGenerator);

    /**
     *  @brief      Resampling.
     *  @details    This function samples with replacement m times the n elements of a sequence
     *              and places the result in another container.
     *  @tparam     InputIt  The iterator type to be used to traverse the elements to permute.
     *  @tparam     OutIt  The iterator type to be used to store the result.
     *  @tparam     IntType  The integer type that will define the numbers to permute.
     *  @param[out] out  Output iterator to the initial position in the destination sequence.
     *  @param[in]  begin  Input iterator to the initial position in the source sequence.
     *  @param[in]  end  Input iterator to the final position in the source sequence.      
     *  @param[in, out] secGenerator  Sequential number generator.
     */
    template<std::input_iterator InputIt, typename OutIt>
    requires std::output_iterator<OutIt, typename InputIt::value_type>
    static void resampling(OutIt out, InputIt begin, InputIt end, size_t m,
        RandomNumber& secGenerator);

    /**
     *  @brief      Balanced resampling.
     *  @details    This function samples with replacement the numbers from 0 to n-1. The result is
     *              divided in m blocks, each containing n elements in such a way that the samples
     *              altogether contain equal numbers of the original elements. 
     *  @tparam     OutIt  The iterator type to be used to store the result.
     *  @tparam     IntType  The integer type that will define the numbers to permute.
     *  @param[out] out  Output iterator to the initial position in the destination sequence. Each block
     *              is stored in sequence in this container. The first n elements correspond to the first
     *              block, the second n elements correspond to the second block and so forth. The total
     *              of samples are n x m.
     *  @param[in]  n  Number of elements to sample.
     *  @param[in]  m  Number of blocks of random samples.
     *  @param[in, out] secGenerator  Sequential number generator.
     */
    template<typename OutIt, std::integral IntType>
    requires std::output_iterator<OutIt, IntType>
    static void balancedResampling(OutIt out, IntType n, size_t m, RandomNumber& secGenerator);

    /**
     *  @brief      Balanced resampling.
     *  @details    This function samples with replacement the n elements of a sequence and places the
     *              result in another container. The result is divided in m blocks, each containing n
     *              elements in such a way that the samples altogether contain equal numbers of the
     *              original elements. 
     *  @tparam     InputIt  The iterator type to be used to traverse the elements to permute.
     *  @tparam     OutIt  The iterator type to be used to store the result.
     *  @tparam     IntType  The integer type that will define the numbers to permute.
     *  @param[out] out  Output iterator to the initial position in the destination sequence. Each block
     *              is stored in sequence in this container. The first n elements correspond to the first
     *              block, the second n elements correspond to the second block and so forth. The total
     *              of samples to be calcualted are n x m.
     *  @param[in]  begin  Input iterator to the initial position in the source sequence.
     *  @param[in]  end  Input iterator to the final position in the source sequence. 
     *  @param[in]  m  Number of blocks of random samples.
     *  @param[in, out] secGenerator  Sequential number generator.
     */
    template<std::input_iterator InputIt, typename OutIt>
    requires std::output_iterator<OutIt, typename InputIt::value_type>
    static void balancedResampling(OutIt out, InputIt begin, InputIt end,
        size_t m, RandomNumber& secGenerator);

};

}}

////////// Implementation of method templates //////////
#include <nct/random/RandomNumber_template.h> 

#endif

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
