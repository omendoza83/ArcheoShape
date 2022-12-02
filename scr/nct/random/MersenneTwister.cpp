//=================================================================================================================
/**
 *  @file       MersenneTwister.cpp
 *  @brief      nct::random::MersenneTwister class implementation file.
 *  @details    This file contains the implementation of the nct::random::MersenneTwister class.
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
//        HEADERS AND NAMESPACES
//=================================================================================================================
#include <nct/random/MersenneTwister.h>
#include <nct/nct_constants.h>

//=================================================================================================================
//        CONSTRUCTORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
nct::random::MersenneTwister::MersenneTwister(unsigned long long s, size_t n,
    size_t m, unsigned long long r, unsigned long long a, unsigned long long tu,
    unsigned long long td, unsigned long long ts, unsigned long long tb, unsigned long long tt,
    unsigned long long tc, unsigned long long tl, unsigned long long f) noexcept : state_ {s}, 
    twisted_(n), n_ {n}, m_ {m}, r_ {r}, a_ {a}, tu_ {tu}, td_ {td},
    ts_ {ts}, tb_ {tb}, tt_ {tt}, tc_ {tc}, tl_ {tl}, f_ {f}
{    
    firstHalf_ = n_ - m_;

    hmask_ = 0xffffffffffffffff << r_;
    lmask_ = ~hmask_;    

    twisted_[0] = s;
    for (index_t i = 1; i < n; i++)
        twisted_[i] = f * (twisted_[i - 1] ^ (twisted_[i - 1] >> 62)) + i;

    twist();
}

//=================================================================================================================
//       OPERATORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
unsigned long long nct::random::MersenneTwister::operator()() noexcept
{
    return randomUInt64();
}

//=================================================================================================================
//        MEMBER FUNCTIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
void nct::random::MersenneTwister::twist()
{
    index_t i = 0;
    for (; i < firstHalf_; i++)
    {
        auto bits = (twisted_[i] & hmask_) | (twisted_[i + 1] & lmask_);
        twisted_[i] = twisted_[i + m_] ^ (bits >> 1) ^ ((bits & 1) * a_);
    }

    for (; i < n_ - 1; i++)
    {
        auto bits = (twisted_[i] & hmask_) | (twisted_[i + 1] & lmask_);
        twisted_[i] = twisted_[i - firstHalf_] ^ (bits >> 1) ^ ((bits & 1) * a_);
    }

    auto bits = (twisted_[i] & hmask_) | (twisted_[0] & lmask_);
    twisted_[i] = twisted_[m_ - 1] ^ (bits >> 1) ^ ((bits & 1) * a_);

    index_ = 0;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::random::MersenneTwister::reset(unsigned long long s, size_t n,
    size_t m, unsigned long long r, unsigned long long a, unsigned long long tu,
    unsigned long long td, unsigned long long ts, unsigned long long tb, unsigned long long tt,
    unsigned long long tc, unsigned long long tl, unsigned long long f) noexcept
{
    n_ = n;
    m_ = m;
    firstHalf_ = n_ - m_;

    r_ = r;
    a_ = a;
    tu_ = tu;
    td_ = td;
    ts_ = ts;
    tb_ = tb;
    tt_ = tt;
    tc_ = tc;
    tl_ = tl;
    f_ = f;
    hmask_ = 0xffffffffffffffff << r_;
    lmask_ = ~hmask_;
        
    twisted_.assign(n_, 0);

    state_ = s;
    ui32Counter_ = 0;
    ui16Counter_ = 0;
    ui8Counter_ = 0;
    
    twisted_[0] = s;
    for (index_t i = 1; i < n_; i++)
        twisted_[i] = f_ * (twisted_[i - 1] ^ (twisted_[i - 1] >> 62)) + i;

    twist();
}

//-----------------------------------------------------------------------------------------------------------------
void nct::random::MersenneTwister::seed(unsigned long long s) noexcept
{
    state_ = s;
    ui32Counter_ = 0;
    ui16Counter_ = 0;
    ui8Counter_ = 0;
   
    twisted_[0] = s;
    for (index_t i = 1; i < n_; i++)
        twisted_[i] = f_ * (twisted_[i - 1] ^ (twisted_[i - 1] >> 62)) + i;

    twist();
}

//-----------------------------------------------------------------------------------------------------------------
void nct::random::MersenneTwister::discard(unsigned long long n) noexcept
{
    for (; 0 < n; n--)
        randomUInt64();
}

//-----------------------------------------------------------------------------------------------------------------
double nct::random::MersenneTwister::random() noexcept
{
    return nct::UINT64_ESC*randomUInt64();
}

//-----------------------------------------------------------------------------------------------------------------
float nct::random::MersenneTwister::randomFloat() noexcept
{
    return static_cast<float>(nct::UINT64_ESC*randomUInt64());
}

//-----------------------------------------------------------------------------------------------------------------
inline unsigned long long nct::random::MersenneTwister::randomUInt64() noexcept
{
    if (index_ == n_)
        twist();

    state_ = twisted_[index_++];
    state_ ^= (state_ >> tu_) & td_;
    state_ ^= (state_ << ts_) & tb_;
    state_ ^= (state_ << tt_) & tc_;
    state_ ^= state_ >> tl_;

    return state_;
}

//-----------------------------------------------------------------------------------------------------------------
unsigned int nct::random::MersenneTwister::randomUInt32() noexcept
{
    if (ui32Counter_--) 
        return static_cast<unsigned int>(state_ >> ((ui32Counter_+1)*32));

    randomUInt64(); 
    ui32Counter_ = 1;

    return static_cast<unsigned int>(state_);
}

//-----------------------------------------------------------------------------------------------------------------
unsigned short nct::random::MersenneTwister::randomUInt16() noexcept
{
    if (ui16Counter_--) 
        return static_cast<unsigned short>(state_ >> ((ui16Counter_+1)*16));

    randomUInt64(); 
    ui16Counter_ = 3;

    return static_cast<unsigned short>(state_);
}

//-----------------------------------------------------------------------------------------------------------------
unsigned char nct::random::MersenneTwister::randomUInt8() noexcept
{
    if (ui8Counter_--) 
        return static_cast<unsigned char>(state_ >> ((ui8Counter_+1)*8));

    randomUInt64(); 
    ui8Counter_ = 7;

    return static_cast<unsigned char>(state_);
}

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
