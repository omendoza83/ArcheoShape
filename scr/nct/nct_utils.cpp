//=================================================================================================================
/**
 *  @file       nct_utils.cpp
 *  @brief      Implementation of utility functions.
 *  @details    This file contains the implementation of utility functions of the nct namespace.            
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
//        HEADERS AND NAMESPACES
//=================================================================================================================
#include <nct/nct_utils.h>
#include <nct/nct_constants.h>

#include <list>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <array>
#include <thread>

//=================================================================================================================
//       FUNCTIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
std::string nct::valueToString(double v, int precision)
{
    std::stringstream stream;
    stream << std::fixed << std::setprecision(precision) << v;
    return stream.str();
}

//-----------------------------------------------------------------------------------------------------------------
std::string nct::toLowerCase(const std::string& str)
{
    std::string out;
    std::transform(str.begin(), str.end(), std::back_inserter(out), [](const char c)->char {
        return static_cast<char>(::tolower(c));
    });
    return out;
}

//-----------------------------------------------------------------------------------------------------------------
std::string nct::toUpperCase(const std::string& str)
{
    std::string out;
    transform(str.begin(), str.end(), std::back_inserter(out), [](const char c)->char {
        return static_cast<char>(::toupper(c));
    });
    return out;
}

//-----------------------------------------------------------------------------------------------------------------
std::string nct::trim(const std::string& str)
{
    char charSet[4] = {32, 9, 13, 0};
    return trim(str, charSet);
}

//-----------------------------------------------------------------------------------------------------------------
std::string nct::trim(const std::string& str, const std::string& charSet)
{    
    auto newStringBeginning = str.find_first_not_of(charSet);
    auto newStringEnd = str.find_last_not_of(charSet);

    if (newStringBeginning == std::string::npos)
        return std::string();

    return str.substr(newStringBeginning, (newStringEnd-newStringBeginning+1));
}

//-----------------------------------------------------------------------------------------------------------------
std::string nct::removeWhiteSpaces(const std::string& str)
{
    std::string charSet = { ' ', '\t', '\n', '\v', '\f', '\r' };
    return removeCharacters(str, charSet);
}

//-----------------------------------------------------------------------------------------------------------------
std::string nct::removeCharacters(const std::string& str, const std::string& charSet)
{
    auto size = str.length();
    auto sizeC = charSet.length();

    if (size == 0)
        return std::string();

    std::vector<char> newString(size);
        
    size_t newStringSize = 0;
    bool includeChar = false;
    for (index_t i=0; i<size; i++) {
        newString[i] = 0;
        includeChar = true;
        for (index_t j=0; j<sizeC; j++)
            includeChar = (includeChar) && (!(str.at(i) == charSet.at(j)));

        if (includeChar)
            newString[newStringSize++] = str.at(i);
    }

    std::string newStr = std::string(newString.data(), newStringSize);
    
    return newStr;
}

//-----------------------------------------------------------------------------------------------------------------
std::string nct::findAndReplace(const std::string& source,
    const std::string& find, const std::string& replace)
{
    auto newStr = source;
    for (index_t i = 0; (i = newStr.find(find, i)) != std::string::npos;) {
        newStr.replace(i, find.length(), replace);
        i += replace.length() - find.length() + 1;
    }

    return newStr;
}

//-----------------------------------------------------------------------------------------------------------------
std::vector<unsigned char> nct::xorEncryption(const std::vector<unsigned char>& str, 
    const std::vector<unsigned char>& key)
{
    auto outStr = str;
    auto n = key.size();
    for (index_t i = 0; i < str.size(); i++)
        outStr[i] = str[i] ^ key[i % n];

    return outStr;
}

//-----------------------------------------------------------------------------------------------------------------
unsigned int nct::randomHash32(unsigned int u) noexcept
{   
    // Mixing function of the 32-bit murmur3 algorithm
    u ^= u >> 16;
    u *= 0x85ebca6bU;
    u ^= u >> 13;
    u *= 0xc2b2ae35U;
    u ^= u >> 16;
    return u;
}

//-----------------------------------------------------------------------------------------------------------------
unsigned long long nct::randomHash64(unsigned long long u) noexcept
{
    // Mixing function of the 64-bit murmur3 algorithm
    u ^= (u >> 33);
    u *= 0xff51afd7ed558ccd;
    u ^= (u >> 33);
    u *= 0xc4ceb9fe1a85ec53;
    u ^= (u >> 33);
    return u;
}

//-----------------------------------------------------------------------------------------------------------------
double nct::randomHashDouble(unsigned long long u) noexcept
{
    return nct::UINT64_ESC * randomHash64(u);
}

//-----------------------------------------------------------------------------------------------------------------
std::string nct::dateString(const time_t& time)
{
    std::string date = ctime(&time);
    return date.substr(0, date.length() - 1);
}

//-----------------------------------------------------------------------------------------------------------------
bool nct::isScalarNumericType(const std::string& t)
{
    auto tt = toLowerCase(t);

    if ((tt == "int8") || (t == typeid(char).name()))
        return true;
    else if ((tt == "uint8") || (t == typeid(unsigned char).name()))
        return true;
    else if ((tt == "int16") || (t == typeid(short).name()))
        return true;
    else if ((tt == "uint16") || (t == typeid(unsigned short).name()))
        return true;
    else if ((tt == "int32") || (t == typeid(int).name()))
        return true;
    else if ((tt == "uint32") || (t == typeid(unsigned int).name()))
        return true;
    else if ((tt == "int64") || (t == typeid(long long).name()))
        return true;
    else if ((tt == "uint64") || (t == typeid(unsigned long long).name()))
        return true;
    else if ((tt == "float") || (t == typeid(float).name()))
        return true;
    else if ((tt == "double") || (t == typeid(double).name()))
        return true;

    return false;
}

//-----------------------------------------------------------------------------------------------------------------
std::string nct::numericTypeAlias(const std::string& t)
{
    auto tt = toLowerCase(t);

    if ((tt == "int8") || (t == typeid(char).name()))
        return "int8";
    else if ((tt == "uint8") || (t == typeid(unsigned char).name()))
        return "uint8";
    else if ((tt == "int16") || (t == typeid(short).name()))
        return "int16";
    else if ((tt == "uint16") || (t == typeid(unsigned short).name()))
        return "uint16";
    else if ((tt == "int32") || (t == typeid(int).name()))
        return "int32";
    else if ((tt == "uint32") || (t == typeid(unsigned int).name()))
        return "uint32";
    else if ((tt == "int64") || (t == typeid(long long).name()))
        return "int64";
    else if ((tt == "uint64") || (t == typeid(unsigned long long).name()))
        return "uint64";
    else if ((tt == "float") || (t == typeid(float).name()))
        return "float";
    else if ((tt == "double") || (t == typeid(double).name()))
        return "double";
    else if ((tt == "complex") || (t == typeid(Complex).name()))
        return "complex";

    return t;
}

//-----------------------------------------------------------------------------------------------------------------
bool nct::compareNumericTypeNames(const std::string& t1, const std::string& t2)
{
    // Basic comparison.
    if (t1 == t2)
        return true;

    // Compare known alias.
    auto tt1 = toLowerCase(t1);
    auto tt2 = toLowerCase(t2);

    // char
    if ((tt1 == "int8") || (t1 == typeid(char).name())) {

        if ((tt2 == "int8") || (t2 == typeid(char).name()))
            return true;
        return false;
    }

    // unsigned char
    if ((tt1 == "uint8") || (t1 == typeid(unsigned char).name())) {
        if ((tt2 == "uint8") || (t2 == typeid(unsigned char).name()))
            return true;
        return false;
    }

    // short
    if ((tt1 == "int16") || (t1 == typeid(short).name())) {

        if ((tt2 == "int16") || (t2 == typeid(short).name()))
            return true;
        return false;
    }

    // unsigned short
    if ((tt1 == "uint16") || (t1 == typeid(unsigned short).name())) {

        if ((tt2 == "uint16") || (t2 == typeid(unsigned short).name()))
            return true;
        return false;
    }

    // int
    if ((tt1 == "int32") || (t1 == typeid(int).name())) {

        if ((tt2 == "int32") || (t2 == typeid(int).name()))
            return true;
        return false;
    }

    // unsigned int
    if ((tt1 == "uint32") || (t1 == typeid(unsigned int).name())) {

        if ((tt2 == "uint32") || (t2 == typeid(unsigned int).name()))
            return true;
        return false;
    }

    // long long
    if ((tt1 == "int64") || (t1 == typeid(long long).name())) {

        if ((tt2 == "int64") || (t2 == typeid(long long).name()))
            return true;
        return false;
    }

    // unsigned long long
    if ((tt1 == "uint64") || (t1 == typeid(unsigned long long).name())) {

        if ((tt2 == "uint64") || (t2 == typeid(unsigned long long).name()))
            return true;
        return false;
    }

    // float
    if ((tt1 == "float") || (t1 == typeid(float).name())) {

        if ((tt2 == "float") || (t2 == typeid(float).name()))
            return true;
        return false;
    }

    // double
    if ((tt1 == "double") || (t1 == typeid(double).name())) {

        if ((tt2 == "double") || (t2 == typeid(double).name()))
            return true;
        return false;
    }

    // complex
    if ((tt1 == "complex") || (t1 == typeid(Complex).name())) {

        if ((tt2 == "complex") || (t2 == typeid(Complex).name()))
            return true;
        return false;
    }

    return false;
}

//-----------------------------------------------------------------------------------------------------------------
nct::size_t nct::numericTypeSize(const std::string& t)
{
    auto tt = toLowerCase(t);

    if ((tt == "int8") || (t == typeid(char).name()))
        return 1;
    else if ((tt == "uint8") || (t == typeid(unsigned char).name()))
        return 1;
    else if ((tt == "int16") || (t == typeid(short).name()))
        return 2;
    else if ((tt == "uint16") || (t == typeid(unsigned short).name()))
        return 2;
    else if ((tt == "int32") || (t == typeid(int).name()))
        return 4;
    else if ((tt == "uint32") || (t == typeid(unsigned int).name()))
        return 4;
    else if ((tt == "int64") || (t == typeid(long long).name()))
        return 8;
    else if ((tt == "uint64") || (t == typeid(unsigned long long).name()))
        return 8;
    else if ((tt == "float") || (t == typeid(float).name()))
        return 4;
    else if ((tt == "double") || (t == typeid(double).name()))
        return 8;
    else if ((tt == "complex") || (t == typeid(Complex).name()))
        return 16;

    return 0;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::stop()
{
    char garbage;
    std::string garbageString;
    std::cin.clear();
    std::cout << "\n<<< Press enter to continue...>>>" << std::endl;
    while (std::cin.readsome(&garbage, 1));
    std::getline(std::cin, garbageString);
}

//-----------------------------------------------------------------------------------------------------------------
void nct::sleep(double seconds) noexcept
{
    auto start = std::chrono::steady_clock::now();
    
    std::chrono::microseconds sleepTime(static_cast<unsigned long long>(seconds * 1000000));    
    std::this_thread::sleep_for(sleepTime);
}

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
