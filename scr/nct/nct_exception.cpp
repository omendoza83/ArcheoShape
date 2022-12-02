//=================================================================================================================
/**
 *  @file       nct_exception.cpp
 *  @brief      Implementation of nct::nct_exception class.
 *  @details    This file contains the implementation of the nct::nct_exception class and its derivated
 *              classes.
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
#include <nct/nct_exception.h>
#include <chrono>
#include <fstream>

//=================================================================================================================
//        CLASS nct_exception
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
nct::nct_exception::nct_exception(const std::exception_ptr& father)
{
    error_ = "";
    info_ = "";
    sourceInfo_ = "";
    fatherException_ = father;    

    time_t tError = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    timestamp_ = ctime(&tError);
    timestamp_ = timestamp_.substr(0, timestamp_.length() - 1);
}

//-----------------------------------------------------------------------------------------------------------------
nct::nct_exception::nct_exception(const std::string& errorMessage, const std::exception_ptr& father)
{
    error_ = "";
    info_ = errorMessage;
    sourceInfo_ = "";
    fatherException_ = father;

    time_t tError = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    timestamp_ = ctime(&tError);
    timestamp_ = timestamp_.substr(0, timestamp_.length() - 1);
}

//-----------------------------------------------------------------------------------------------------------------
nct::nct_exception::nct_exception(const std::string& errorMessage, 
const std::string& source, const std::exception_ptr& father)
{    
    error_ = "";
    info_ = errorMessage;
    sourceInfo_ = source;    
    fatherException_ = father;

    time_t tError = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    timestamp_ = ctime(&tError);
    timestamp_ = timestamp_.substr(0, timestamp_.length() - 1);
}

//-----------------------------------------------------------------------------------------------------------------
const char* nct::nct_exception::what() const noexcept
{
    return completeErrorDescription().c_str();
}

//-----------------------------------------------------------------------------------------------------------------
const std::string& nct::nct_exception::completeErrorDescription() const noexcept
{
    if (error_.length() == 0) {                                            
        if (info_.length() > 0) {
            error_ += exc_info;
            error_ += info_;
        }    
        
        if (sourceInfo_.length() > 0) {
            if (error_.length() > 0)
                error_ += "\n";

            error_ += exc_source;
            error_ += sourceInfo_;
        }

        if (error_.length() > 0)
            error_ += "\n";

        error_ += exc_timestamp;
        error_ += timestamp_;

        if (fatherException_ != nullptr) {
            error_ += exc_father_exception;
            try {
                std::rethrow_exception(fatherException_);            
            }
            catch (const nct_exception& ex) {
                error_ += ex.what();
            }
            catch (const std::exception& ex) {
                error_ += ex.what();
            }
            catch (...) {
                error_ += exc_unknown;
            }        
        }        
    }

    return error_;
}

//-----------------------------------------------------------------------------------------------------------------
const std::string& nct::nct_exception::errorInfo() const noexcept
{
    return info_;
}

//-----------------------------------------------------------------------------------------------------------------
const std::string& nct::nct_exception::source() const noexcept
{
    return sourceInfo_;
}

//-----------------------------------------------------------------------------------------------------------------
const std::string& nct::nct_exception::exceptionTimestamp() const noexcept
{
    return timestamp_;
}

//-----------------------------------------------------------------------------------------------------------------
const std::exception_ptr& nct::nct_exception::fatherException() const noexcept
{
    return fatherException_;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::nct_exception::appendToLogFile(std::string& logFile)
{
    std::ofstream file;
    
    file.open(logFile.c_str(), std::ios_base::app);
    if (file.fail())
        return ;
    file << exc_log_separator << std::endl;
    file << completeErrorDescription() << std::endl;

    file.close();
}

//=================================================================================================================
//        CLASS MemoryException
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
nct::MemoryException::MemoryException(const std::exception_ptr& father) : nct_exception{father}
{
    info_ = exc_memory_exception;
}

//-----------------------------------------------------------------------------------------------------------------
nct::MemoryException::MemoryException(const std::string& source, 
    const std::exception_ptr& father) : nct_exception{"", source, father}
{    
    info_ = exc_memory_exception;
}

//=================================================================================================================
//        CLASS ArgumentException
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
nct::ArgumentException::ArgumentException()
{
    info_ = exc_bad_arguments;
}

//-----------------------------------------------------------------------------------------------------------------
nct::ArgumentException::ArgumentException(const std::string& arguments, const std::string& details, 
    const std::string& source) : nct_exception{"", source}
{    
    info_ = exc_bad_arguments;

    if (arguments!="") {
        info_ += "\n";
        info_ += exc_arguments;
        info_ += arguments;
    }        
    if (details!="") {
        info_ += "\n";
        info_ += exc_details;
        info_ += details;
    }
}

//-----------------------------------------------------------------------------------------------------------------
nct::ArgumentException::ArgumentException(const std::string& arguments, 
    const std::string& source) : nct_exception{"", source}
{    
    info_ = exc_bad_arguments;

    if (arguments!="") {
        info_ += "\n";
        info_ += exc_arguments;
        info_ += arguments;
    }        
}

//-----------------------------------------------------------------------------------------------------------------
nct::ArgumentException::ArgumentException(const std::string& argumentName, const std::string& value, 
    const std::string& validValues, const std::string& source) : nct_exception{"", source}
{    
    info_ = exc_bad_argument;

    if (argumentName!="") {
        info_ += "\n";
        info_ += exc_argument;
        info_ += argumentName;
    }        
    if (value!="") {
        info_ += "\n";
        info_ += exc_value;
        info_ += value;
    }
    if (validValues!="") {
        info_ += "\n";
        info_ += exc_valid_values;
        info_ += validValues;
    }
}

//-----------------------------------------------------------------------------------------------------------------
nct::ArgumentException::ArgumentException(const std::string& argumentName, double value,
    const std::string& source) : nct_exception{"", source}
{    
    info_ = exc_bad_argument;    
    if (argumentName!="") {
        info_ += "\n";
        info_ += exc_argument;
        info_ += argumentName;
    }        

    info_ += "\n";
    info_ += exc_value; 
    info_ += std::to_string(value);
}

//-----------------------------------------------------------------------------------------------------------------
nct::ArgumentException::ArgumentException(const std::string& argumentName, double value, double limit, 
    RelationalOperator relationalOperator, const std::string& source) : nct_exception{"", source}
{    
    info_ = exc_bad_argument;    

    if (argumentName!="") {
        info_ += "\n";
        info_ += exc_argument;
        info_ += argumentName;
    }        
    
    info_ += "\n";
    info_ += exc_value;
    info_ += std::to_string(value);
    
    info_ += "\n";
    info_ += exc_valid_range;

    switch (relationalOperator) {
        case RelationalOperator::Equal:
            info_ += "= ";
            break;
        case RelationalOperator::NotEqual:
            info_ += "!= ";
            break;
        case RelationalOperator::LowerThan:
            info_ += "< ";
            break;            
        case RelationalOperator::LowerThanOrEqualTo:
            info_ += "<= ";
            break;            
        case RelationalOperator::GreaterThan:
            info_ += "> ";
            break;            
        case RelationalOperator::GreaterThanOrEqualTo:
            info_ += ">= ";
            break;
    }

    info_ += std::to_string(limit);
}

//-----------------------------------------------------------------------------------------------------------------
nct::ArgumentException::ArgumentException(const std::string& argumentName, double value, double limit1, 
    double limit2, RelationalOperator relationalOperator1, RelationalOperator relationalOperator2, 
    const std::string& source) : nct_exception{"", source}
{    
    info_ = exc_bad_argument;    

    if (argumentName!="") {
        info_ += "\n";
        info_ += exc_argument;
        info_ += argumentName;
    }        
    
    info_ += "\n";
    info_ += exc_value;
    info_ += std::to_string(value);
    
    info_ += "\n";
    info_ += exc_valid_range;

    switch (relationalOperator1) {
        case RelationalOperator::Equal:
            info_ += "= ";
            break;
        case RelationalOperator::NotEqual:
            info_ += "!= ";
            break;
        case RelationalOperator::LowerThan:
            info_ += "< ";
            break;
        case RelationalOperator::LowerThanOrEqualTo:
            info_ += "<= ";
            break;
        case RelationalOperator::GreaterThan:
            info_ += "> ";
            break;
        case RelationalOperator::GreaterThanOrEqualTo:
            info_ += ">= ";
            break;
    }

    info_ += std::to_string(limit1);

    switch (relationalOperator2) {
        case RelationalOperator::Equal:
            info_ += ", = ";
            break;
        case RelationalOperator::NotEqual:
            info_ += ", != ";
            break;
        case RelationalOperator::LowerThan:
            info_ += ", < ";
            break;            
        case RelationalOperator::LowerThanOrEqualTo:
            info_ += ", <= ";
            break;            
        case RelationalOperator::GreaterThan:
            info_ += ", > ";
            break;            
        case RelationalOperator::GreaterThanOrEqualTo:
            info_ += ", >= ";
            break;
    }

    info_ += std::to_string(limit2);
}

//-----------------------------------------------------------------------------------------------------------------
nct::ArgumentException::ArgumentException(const std::string& argumentName, int value,
    const std::string& source) : nct_exception{"", source}
{    
    info_ = exc_bad_argument;    
    if (argumentName!="") {
        info_ += "\n";
        info_ += exc_argument;
        info_ += argumentName;
    }            
    
    info_ += "\n";
    info_ += exc_value;
    info_ += std::to_string(value);
}

//-----------------------------------------------------------------------------------------------------------------
nct::ArgumentException::ArgumentException(const std::string& argumentName, int value, int limit,
    RelationalOperator relationalOperator, const std::string& source) : nct_exception{"", source}
{    
    info_ = exc_bad_argument;    

    if (argumentName!="") {
        info_ += "\n";
        info_ += exc_argument;
        info_ += argumentName;
    }        
    
    info_ += "\n";
    info_ += exc_value;
    info_ += std::to_string(value);
    
    info_ += "\n";
    info_ += exc_valid_range;

    switch (relationalOperator) {
        case RelationalOperator::Equal:
            info_ += "= ";
            break;
        case RelationalOperator::NotEqual:
            info_ += "!= ";
            break;
        case RelationalOperator::LowerThan:
            info_ += "< ";
            break;
        case RelationalOperator::LowerThanOrEqualTo:
            info_ += "<= ";
            break;
        case RelationalOperator::GreaterThan:
            info_ += "> ";
            break;
        case RelationalOperator::GreaterThanOrEqualTo:
            info_ += ">= ";
            break;
    }

    info_ += std::to_string(limit);
}

//-----------------------------------------------------------------------------------------------------------------
nct::ArgumentException::ArgumentException(const std::string& argumentName, int value, int limit1,
    int limit2, RelationalOperator relationalOperator1, RelationalOperator relationalOperator2,
    const std::string& source) : nct_exception{"", source}
{    
    info_ = exc_bad_argument;    

    if (argumentName!="") {
        info_ += "\n";
        info_ += exc_argument;
        info_ += argumentName;
    }        
    
    info_ += "\n";
    info_ += exc_value;
    info_ += std::to_string(value);
    
    info_ += "\n";
    info_ += exc_valid_range;

    switch (relationalOperator1) {
        case RelationalOperator::Equal:
            info_ += "= ";
            break;
        case RelationalOperator::NotEqual:
            info_ += "!= ";
            break;
        case RelationalOperator::LowerThan:
            info_ += "< ";
            break;
        case RelationalOperator::LowerThanOrEqualTo:
            info_ += "<= ";
            break;
        case RelationalOperator::GreaterThan:
            info_ += "> ";
            break;
        case RelationalOperator::GreaterThanOrEqualTo:
            info_ += ">= ";
            break;
    }

    info_ += std::to_string(limit1);

    switch (relationalOperator2) {
        case RelationalOperator::Equal:
            info_ += ", = ";
            break;
        case RelationalOperator::NotEqual:
            info_ += ", != ";
            break;
        case RelationalOperator::LowerThan:
            info_ += ", < ";
            break;
        case RelationalOperator::LowerThanOrEqualTo:
            info_ += ", <= ";
            break;
        case RelationalOperator::GreaterThan:
            info_ += ", > ";
            break;
        case RelationalOperator::GreaterThanOrEqualTo:
            info_ += ", >= ";
            break;
    }

    info_ += std::to_string(limit2);
}

//-----------------------------------------------------------------------------------------------------------------
nct::ArgumentException::ArgumentException(const std::string& argumentName, unsigned int value,
    const std::string& source) : nct_exception{"", source}
{    
    info_ = exc_bad_argument;    
    if (argumentName!="") {
        info_ += "\n";
        info_ += exc_argument;
        info_ += argumentName;
    }            
    
    info_ += "\n";
    info_ += exc_value;
    info_ += std::to_string(value);
}

//-----------------------------------------------------------------------------------------------------------------
nct::ArgumentException::ArgumentException(const std::string& argumentName, unsigned int value, 
    unsigned int limit, RelationalOperator relationalOperator,
    const std::string& source) : nct_exception{"", source}
{    
    info_ = exc_bad_argument;    

    if (argumentName!="") {
        info_ += "\n";
        info_ += exc_argument;
        info_ += argumentName;
    }        
    
    info_ += "\n";
    info_ += exc_value;
    info_ += std::to_string(value);
    
    info_ += "\n";
    info_ += exc_valid_range;

    switch (relationalOperator) {
        case RelationalOperator::Equal:
            info_ += "= ";
            break;
        case RelationalOperator::NotEqual:
            info_ += "!= ";
            break;
        case RelationalOperator::LowerThan:
            info_ += "< ";
            break;
        case RelationalOperator::LowerThanOrEqualTo:
            info_ += "<= ";
            break;
        case RelationalOperator::GreaterThan:
            info_ += "> ";
            break;
        case RelationalOperator::GreaterThanOrEqualTo:
            info_ += ">= ";
            break;
    }

    info_ += std::to_string(limit);
}

//-----------------------------------------------------------------------------------------------------------------
nct::ArgumentException::ArgumentException(const std::string& argumentName, unsigned int value, 
    unsigned int limit1, unsigned int limit2, RelationalOperator relationalOperator1, 
    RelationalOperator relationalOperator2,
    const std::string& source) : nct_exception{"", source}
{    
    info_ = exc_bad_argument;    

    if (argumentName!="") {
        info_ += "\n";
        info_ += exc_argument;
        info_ += argumentName;
    }        
    
    info_ += "\n";
    info_ += exc_value;
    info_ += std::to_string(value);

    info_ += "\n";
    info_ += exc_valid_range;
    
    switch (relationalOperator1) {
        case RelationalOperator::Equal:
            info_ += "= ";
            break;
        case RelationalOperator::NotEqual:
            info_ += "!= ";
            break;
        case RelationalOperator::LowerThan:
            info_ += "< ";
            break;
        case RelationalOperator::LowerThanOrEqualTo:
            info_ += "<= ";
            break;
        case RelationalOperator::GreaterThan:
            info_ += "> ";
            break;
        case RelationalOperator::GreaterThanOrEqualTo:
            info_ += ">= ";
            break;
    }

    info_ += std::to_string(limit1);

    switch (relationalOperator2) {
        case RelationalOperator::Equal:
            info_ += ", = ";
            break;
        case RelationalOperator::NotEqual:
            info_ += ", != ";
            break;
        case RelationalOperator::LowerThan:
            info_ += ", < ";
            break;
        case RelationalOperator::LowerThanOrEqualTo:
            info_ += ", <= ";
            break;
        case RelationalOperator::GreaterThan:
            info_ += ", > ";
            break;
        case RelationalOperator::GreaterThanOrEqualTo:
            info_ += ", >= ";
            break;
    }

    info_ += std::to_string(limit2);
}

//-----------------------------------------------------------------------------------------------------------------
nct::ArgumentException::ArgumentException(const std::string& argumentName, long long value,
    const std::string& source) : nct_exception{"", source}
{    
    info_ = exc_bad_argument;    
    if (argumentName!="") {
        info_ += "\n";
        info_ += exc_argument;
        info_ += argumentName;
    }            
    
    info_ += "\n";
    info_ += exc_value;
    info_ += std::to_string(value);
}

//-----------------------------------------------------------------------------------------------------------------
nct::ArgumentException::ArgumentException(const std::string& argumentName, long long value, 
    long long limit, RelationalOperator relationalOperator, 
    const std::string& source) : nct_exception{"", source}
{    
    info_ = exc_bad_argument;    

    if (argumentName!="") {
        info_ += "\n";
        info_ += exc_argument;
        info_ += argumentName;
    }        
    
    info_ += "\n";
    info_ += exc_value;
    info_ += std::to_string(value);

    info_ += "\n";
    info_ += exc_valid_range;
    
    switch (relationalOperator) {
        case RelationalOperator::Equal:
            info_ += "= ";
            break;
        case RelationalOperator::NotEqual:
            info_ += "!= ";
            break;
        case RelationalOperator::LowerThan:
            info_ += "< ";
            break;
        case RelationalOperator::LowerThanOrEqualTo:
            info_ += "<= ";
            break;
        case RelationalOperator::GreaterThan:
            info_ += "> ";
            break;
        case RelationalOperator::GreaterThanOrEqualTo:
            info_ += ">= ";
            break;
    }

    info_ += std::to_string(limit);
}

//-----------------------------------------------------------------------------------------------------------------
nct::ArgumentException::ArgumentException(const std::string& argumentName, 
    long long value, long long limit1, long long limit2, RelationalOperator relationalOperator1,
    RelationalOperator relationalOperator2, const std::string& source) : nct_exception{"", source}
{    
    info_ = exc_bad_argument;    

    if (argumentName!="") {
        info_ += "\n";
        info_ += exc_argument;
        info_ += argumentName;
    }        
    
    info_ += "\n";
    info_ += exc_value;
    info_ += std::to_string(value);

    info_ += "\n";
    info_ += exc_valid_range;
    
    switch (relationalOperator1) {
        case RelationalOperator::Equal:
            info_ += "= ";
            break;
        case RelationalOperator::NotEqual:
            info_ += "!= ";
            break;
        case RelationalOperator::LowerThan:
            info_ += "< ";
            break;
        case RelationalOperator::LowerThanOrEqualTo:
            info_ += "<= ";
            break;
        case RelationalOperator::GreaterThan:
            info_ += "> ";
            break;
        case RelationalOperator::GreaterThanOrEqualTo:
            info_ += ">= ";
            break;
    }

    info_ += std::to_string(limit1);

    switch (relationalOperator2) {
        case RelationalOperator::Equal:
            info_ += ", = ";
            break;
        case RelationalOperator::NotEqual:
            info_ += ", != ";
            break;
        case RelationalOperator::LowerThan:
            info_ += ", < ";
            break;
        case RelationalOperator::LowerThanOrEqualTo:
            info_ += ", <= ";
            break;
        case RelationalOperator::GreaterThan:
            info_ += ", > ";
            break;
        case RelationalOperator::GreaterThanOrEqualTo:
            info_ += ", >= ";
            break;
    }

    info_ += std::to_string(limit2);
}

//-----------------------------------------------------------------------------------------------------------------
nct::ArgumentException::ArgumentException(const std::string& argumentName, unsigned long long value,
    const std::string& source) : nct_exception{"", source}
{    
    info_ = exc_bad_argument;    
    if (argumentName!="") {
        info_ += "\n";
        info_ += exc_argument;
        info_ += argumentName;
    }            
    
    info_ += "\n";
    info_ += exc_value;
    info_ += std::to_string(value);
}

//-----------------------------------------------------------------------------------------------------------------
nct::ArgumentException::ArgumentException(const std::string& argumentName, unsigned long long value,
    unsigned long long limit, RelationalOperator relationalOperator, 
    const std::string& source) : nct_exception{"", source}
{    
    info_ = exc_bad_argument;    

    if (argumentName!="") {
        info_ += "\n";
        info_ += exc_argument;
        info_ += argumentName;
    }        
    
    info_ += "\n";
    info_ += exc_value;
    info_ += std::to_string(value);

    info_ += "\n";
    info_ += exc_valid_range;
    
    switch (relationalOperator) {
        case RelationalOperator::Equal:
            info_ += "= ";
            break;
        case RelationalOperator::NotEqual:
            info_ += "!= ";
            break;
        case RelationalOperator::LowerThan:
            info_ += "< ";
            break;
        case RelationalOperator::LowerThanOrEqualTo:
            info_ += "<= ";
            break;
        case RelationalOperator::GreaterThan:
            info_ += "> ";
            break;
        case RelationalOperator::GreaterThanOrEqualTo:
            info_ += ">= ";
            break;
    }

    info_ += std::to_string(limit);
}

//-----------------------------------------------------------------------------------------------------------------
nct::ArgumentException::ArgumentException(const std::string& argumentName, unsigned long long value, 
    unsigned long long limit1, unsigned long long limit2, RelationalOperator relationalOperator1,
    RelationalOperator relationalOperator2, const std::string& source) : nct_exception{"", source}
{    
    info_ = exc_bad_argument;    

    if (argumentName!="") {
        info_ += "\n";
        info_ += exc_argument;
        info_ += argumentName;
    }        
    
    info_ += "\n";
    info_ += exc_value;
    info_ += std::to_string(value);

    info_ += "\n";
    info_ += exc_valid_range;
    
    switch (relationalOperator1) {
        case RelationalOperator::Equal:
            info_ += "= ";
            break;
        case RelationalOperator::NotEqual:
            info_ += "!= ";
            break;
        case RelationalOperator::LowerThan:
            info_ += "< ";
            break;
        case RelationalOperator::LowerThanOrEqualTo:
            info_ += "<= ";
            break;
        case RelationalOperator::GreaterThan:
            info_ += "> ";
            break;
        case RelationalOperator::GreaterThanOrEqualTo:
            info_ += ">= ";
            break;
    }

    info_ += std::to_string(limit1);

    switch (relationalOperator2) {
        case RelationalOperator::Equal:
            info_ += ", = ";
            break;
        case RelationalOperator::NotEqual:
            info_ += ", != ";
            break;
        case RelationalOperator::LowerThan:
            info_ += ", < ";
            break;
        case RelationalOperator::LowerThanOrEqualTo:
            info_ += ", <= ";
            break;
        case RelationalOperator::GreaterThan:
            info_ += ", > ";
            break;
        case RelationalOperator::GreaterThanOrEqualTo:
            info_ += ", >= ";
            break;
    }

    info_ += std::to_string(limit2);
}

//=================================================================================================================
//        CLASS IndexOutOfRangeException
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
nct::IndexOutOfRangeException::IndexOutOfRangeException()
{
    info_ = exc_index_out_of_range;    
}

//-----------------------------------------------------------------------------------------------------------------
nct::IndexOutOfRangeException::IndexOutOfRangeException(const std::string& source) : 
    nct_exception{"", source}
{    
    info_ = exc_index_out_of_range;    
}

//-----------------------------------------------------------------------------------------------------------------
nct::IndexOutOfRangeException::IndexOutOfRangeException(const std::string& indexName, 
    const std::string& source) : nct_exception{"", source}
{    
    info_ = exc_index_out_of_range;    

    if (indexName!="") {
        info_ += "\n";
        info_ += exc_index;
        info_ += indexName;
    }        
}

//-----------------------------------------------------------------------------------------------------------------
nct::IndexOutOfRangeException::IndexOutOfRangeException(const std::string& indexName, 
    const std::string& value, const std::string& validValues, 
    const std::string& source) : nct_exception{"", source}
{    
    info_ = exc_index_out_of_range;    

    if (indexName!="") {
        info_ += "\n";
        info_ += exc_index;
        info_ += indexName;
    }        
    if (value!="") {
        info_ += "\n";
        info_ += exc_value;
        info_ += value;
    }
    if (validValues!="") {
        info_ += "\n";
        info_ += exc_valid_values;
        info_ += validValues;
    }
}

//-----------------------------------------------------------------------------------------------------------------
nct::IndexOutOfRangeException::IndexOutOfRangeException(const std::string& indexName, 
    diff_t value, const std::string& source) : nct_exception{"", source}
{    
    info_ = exc_index_out_of_range;    
    if (indexName!="") {
        info_ += "\n";
        info_ += exc_index;
        info_ += indexName;
    }            
    
    info_ += "\n";
    info_ += exc_value;
    info_ += std::to_string(value);
}

//-----------------------------------------------------------------------------------------------------------------
nct::IndexOutOfRangeException::IndexOutOfRangeException(const std::string& indexName,
    diff_t value, diff_t limit,
    RelationalOperator relationalOperator, const std::string& source) : nct_exception{"", source}
{    
    info_ = exc_index_out_of_range;    

    if (indexName!="") {
        info_ += "\n";
        info_ += exc_index;
        info_ += indexName;
    }        
    
    info_ += "\n";
    info_ += exc_value;
    info_ += std::to_string(value);
    
    info_ += "\n";
    info_ += exc_valid_range;

    switch (relationalOperator) {
        case RelationalOperator::Equal:
            info_ += "= ";
            break;
        case RelationalOperator::NotEqual:
            info_ += "!= ";
            break;
        case RelationalOperator::LowerThan:
            info_ += "< ";
            break;
        case RelationalOperator::LowerThanOrEqualTo:
            info_ += "<= ";
            break;
        case RelationalOperator::GreaterThan:
            info_ += "> ";
            break;
        case RelationalOperator::GreaterThanOrEqualTo:
            info_ += ">= ";
            break;
    }

    info_ += std::to_string(limit);
}

//-----------------------------------------------------------------------------------------------------------------
nct::IndexOutOfRangeException::IndexOutOfRangeException(const std::string& indexName, diff_t value,
    diff_t limit1, diff_t limit2, RelationalOperator relationalOperator1,
    RelationalOperator relationalOperator2, 
    const std::string& source) : nct_exception{"", source}
{    
    info_ = exc_index_out_of_range;    

    if (indexName!="") {
        info_ += "\n";
        info_ += exc_index;
        info_ += indexName;
    }        
    
    info_ += "\n";
    info_ += exc_value;
    info_ += std::to_string(value);

    info_ += "\n";
    info_ += exc_valid_range;
    
    switch (relationalOperator1) {
        case RelationalOperator::Equal:
            info_ += "= ";
            break;
        case RelationalOperator::NotEqual:
            info_ += "!= ";
            break;
        case RelationalOperator::LowerThan:
            info_ += "< ";
            break;
        case RelationalOperator::LowerThanOrEqualTo:
            info_ += "<= ";
            break;
        case RelationalOperator::GreaterThan:
            info_ += "> ";
            break;
        case RelationalOperator::GreaterThanOrEqualTo:
            info_ += ">= ";
            break;
    }

    info_ += std::to_string(limit1);

    switch (relationalOperator2) {
        case RelationalOperator::Equal:
            info_ += ", = ";
            break;
        case RelationalOperator::NotEqual:
            info_ += ", != ";
            break;
        case RelationalOperator::LowerThan:
            info_ += ", < ";
            break;
        case RelationalOperator::LowerThanOrEqualTo:
            info_ += ", <= ";
            break;
        case RelationalOperator::GreaterThan:
            info_ += ", > ";
            break;
        case RelationalOperator::GreaterThanOrEqualTo:
            info_ += ", >= ";
            break;
    }

    info_ += std::to_string(limit2);
}

//-----------------------------------------------------------------------------------------------------------------
nct::IndexOutOfRangeException::IndexOutOfRangeException(const std::string& indexName, 
    size_t value, const std::string& source) : nct_exception{"", source}
{    
    info_ = exc_index_out_of_range;    
    if (indexName!="") {
        info_ += "\n";
        info_ += exc_index;
        info_ += indexName;
    }            
    
    info_ += "\n";
    info_ += exc_value;
    info_ += std::to_string(value);
}

//-----------------------------------------------------------------------------------------------------------------
nct::IndexOutOfRangeException::IndexOutOfRangeException(const std::string& indexName,
    size_t value, size_t limit,
    RelationalOperator relationalOperator, const std::string& source) : nct_exception{"", source}
{    
    info_ = exc_index_out_of_range;    

    if (indexName!="") {
        info_ += "\n";
        info_ += exc_index;
        info_ += indexName;
    }        
    
    info_ += "\n";
    info_ += exc_value;
    info_ += std::to_string(value);
    
    info_ += "\n";
    info_ += exc_valid_range;

    switch (relationalOperator) {
        case RelationalOperator::Equal:
            info_ += "= ";
            break;
        case RelationalOperator::NotEqual:
            info_ += "!= ";
            break;
        case RelationalOperator::LowerThan:
            info_ += "< ";
            break;
        case RelationalOperator::LowerThanOrEqualTo:
            info_ += "<= ";
            break;
        case RelationalOperator::GreaterThan:
            info_ += "> ";
            break;
        case RelationalOperator::GreaterThanOrEqualTo:
            info_ += ">= ";
            break;
    }

    info_ += std::to_string(limit);

}

//-----------------------------------------------------------------------------------------------------------------
nct::IndexOutOfRangeException::IndexOutOfRangeException(const std::string& indexName, size_t value,
    size_t limit1, size_t limit2, RelationalOperator relationalOperator1,
    RelationalOperator relationalOperator2, 
    const std::string& source) : nct_exception{"", source}
{    
    info_ = exc_index_out_of_range;    

    if (indexName!="") {
        info_ += "\n";
        info_ += exc_index;
        info_ += indexName;
    }        
    
    info_ += "\n";
    info_ += exc_value;
    info_ += std::to_string(value);

    info_ += "\n";
    info_ += exc_valid_range;
    
    switch (relationalOperator1) {
        case RelationalOperator::Equal:
            info_ += "= ";
            break;
        case RelationalOperator::NotEqual:
            info_ += "!= ";
            break;
        case RelationalOperator::LowerThan:
            info_ += "< ";
            break;
        case RelationalOperator::LowerThanOrEqualTo:
            info_ += "<= ";
            break;
        case RelationalOperator::GreaterThan:
            info_ += "> ";
            break;
        case RelationalOperator::GreaterThanOrEqualTo:
            info_ += ">= ";
            break;
    }

    info_ += std::to_string(limit1);

    switch (relationalOperator2) {
        case RelationalOperator::Equal:
            info_ += ", = ";
            break;
        case RelationalOperator::NotEqual:
            info_ += ", != ";
            break;
        case RelationalOperator::LowerThan:
            info_ += ", < ";
            break;
        case RelationalOperator::LowerThanOrEqualTo:
            info_ += ", <= ";
            break;
        case RelationalOperator::GreaterThan:
            info_ += ", > ";
            break;
        case RelationalOperator::GreaterThanOrEqualTo:
            info_ += ", >= ";
            break;
    }

    info_ += std::to_string(limit2);
}

//=================================================================================================================
//        CLASS IteratorException
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
nct::IteratorException::IteratorException()
{
    info_ = exc_bad_iterator;
}

//-----------------------------------------------------------------------------------------------------------------
nct::IteratorException::IteratorException(const std::string& source) : nct_exception{"", source}
{    
    info_ = exc_bad_iterator;
}

//-----------------------------------------------------------------------------------------------------------------
nct::IteratorException::IteratorException(const std::string& iteratorName, 
    const std::string& source) : nct_exception{"", source}
{    
    info_ = exc_bad_iterator;
    if (iteratorName!="") {
        info_ += "\n";
        info_ += exc_iterator;
        info_ += iteratorName;
    }                
}

//=================================================================================================================
//        CLASS NullIteratorException
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
nct::NullIteratorException::NullIteratorException()
{
    info_ = exc_null_iterator;
}

//-----------------------------------------------------------------------------------------------------------------
nct::NullIteratorException::NullIteratorException(
    const std::string& source) : nct_exception{"", source}
{    
    info_ = exc_null_iterator;
}

//-----------------------------------------------------------------------------------------------------------------
nct::NullIteratorException::NullIteratorException(const std::string& iteratorName, 
    const std::string& source) : nct_exception{"", source}
{    
    info_ = exc_null_iterator;
    if (iteratorName!="") {
        info_ += "\n";
        info_ += exc_iterator;
        info_ += iteratorName;
    }                
}

//=================================================================================================================
//        CLASS RangeException
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
nct::RangeException::RangeException()
{
    info_ = exc_bad_range;
}

//-----------------------------------------------------------------------------------------------------------------
nct::RangeException::RangeException(const std::string& source) : nct_exception{"", source}
{    
    info_ = exc_bad_range;
}

//-----------------------------------------------------------------------------------------------------------------
nct::RangeException::RangeException(const std::string& range, 
    const std::string& source) : nct_exception{"", source}
{    
    info_ = exc_bad_range;
    if (range!="") {
        info_ += "\n";
        info_ += exc_bad_range;
        info_ += range;
    }                
}

//-----------------------------------------------------------------------------------------------------------------
nct::RangeException::RangeException(const std::string& range, const std::string& details,
    const std::string& source) : nct_exception{"", source}
{
    info_ = exc_bad_range;
    if (range != "") {
        info_ += "\n";
        info_ += exc_bad_range;
        info_ += range;
    }
    if (details != "") {
        info_ += "\n";
        info_ += exc_details;
        info_ += details;
    }
}

//=================================================================================================================
//        CLASS NullPointerException
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
nct::NullPointerException::NullPointerException()
{
    info_ = exc_null_pointer;
}

//-----------------------------------------------------------------------------------------------------------------
nct::NullPointerException::NullPointerException(const std::string& source) :
    nct_exception{"", source}
{
    info_ = exc_null_pointer;
}

//-----------------------------------------------------------------------------------------------------------------
nct::NullPointerException::NullPointerException(const std::string& pointerName,
    const std::string& source) : nct_exception{"", source}
{
    info_ = exc_null_pointer;
    if (pointerName != "") {
        info_ += "\n";
        info_ += exc_pointer;
        info_ += pointerName;
    }
}

//=================================================================================================================
//        CLASS InitializationException
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
nct::InitializationException::InitializationException(const std::exception_ptr& father) : nct_exception{father}
{
    info_ = exc_initialization_error;
}

//-----------------------------------------------------------------------------------------------------------------
nct::InitializationException::InitializationException(const std::string& source,
    const std::exception_ptr& father) : nct_exception{"", source, father}
{    
    info_ = exc_initialization_error;
}

//=================================================================================================================
//        CLASS MemberException
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
nct::MemberException::MemberException(const std::exception_ptr& father) : nct_exception{father}
{
    info_ = exc_bad_class_member;
}

//-----------------------------------------------------------------------------------------------------------------
nct::MemberException::MemberException(const std::string& source, 
    const std::exception_ptr& father) : nct_exception{"", source, father}
{    
    info_ = exc_bad_class_member;
}

//-----------------------------------------------------------------------------------------------------------------
nct::MemberException::MemberException(const std::string& details, const std::string& source,
    const std::exception_ptr& father) : nct_exception{"", source, father}
{
    info_ = exc_bad_class_member;
    if (details != "") {
        info_ += "\n";
        info_ += exc_details;
        info_ += details;
    }
}

//=================================================================================================================
//        CLASS ArithmeticException
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
nct::ArithmeticException::ArithmeticException(const std::exception_ptr& father) : nct_exception{father}
{
    info_ = exc_arithmetic_error;
}

//-----------------------------------------------------------------------------------------------------------------
nct::ArithmeticException::ArithmeticException(const std::string& details, 
    const std::string& source, const std::exception_ptr& father) : nct_exception{"", source, father}
{    
    info_ = exc_arithmetic_error;
    if (details!="") {
        info_ += "\n";
        info_ += exc_details;
        info_ += details;
    }    
}

//=================================================================================================================
//        CLASS ConfigurationException
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
nct::ConfigurationException::ConfigurationException(const std::exception_ptr& father) : nct_exception{father}
{
    info_ = exc_bad_configuration;
}

//-----------------------------------------------------------------------------------------------------------------
nct::ConfigurationException::ConfigurationException(const std::string& source, 
    const std::exception_ptr& father) : nct_exception{"", source, father}
{
    info_ = exc_bad_configuration;
}

//-----------------------------------------------------------------------------------------------------------------
nct::ConfigurationException::ConfigurationException(const std::string& details, 
    const std::string& source, const std::exception_ptr& father) : nct_exception{"", source, father}
{    
    info_ = exc_bad_configuration;
    if (details!="") {
        info_ += "\n";
        info_ += exc_details;
        info_ += details;
    }    
}

//=================================================================================================================
//        CLASS IOException
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
nct::IOException::IOException(const std::exception_ptr& father) : nct_exception{father}
{
    info_ = exc_io_exception;
}

//-----------------------------------------------------------------------------------------------------------------
nct::IOException::IOException(const std::string& details, 
    const std::string& source, 
    const std::exception_ptr& father) : nct_exception{"", source, father}
{    
    info_ = exc_io_exception;
    if (details!="") {
        info_ += "\n";
        info_ += exc_details;
        info_ += details;
    }    
}

//-----------------------------------------------------------------------------------------------------------------
nct::IOException::IOException(const std::string& file, const std::string& details, 
    const std::string& source, const std::exception_ptr& father) : nct_exception{"", source, father}
{    
    info_ = exc_io_exception;
    if (file!="") {
        info_ += "\n";
        info_ += exc_file;
        info_ += file;
    }    
    if (details!="") {
        info_ += "\n";
        info_ += exc_details;
        info_ += details;
    }    
}

//=================================================================================================================
//        CLASS OperationException
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
nct::OperationException::OperationException(const std::exception_ptr& father) : nct_exception{father}
{
    info_ = exc_operation_error;
}

//-----------------------------------------------------------------------------------------------------------------
nct::OperationException::OperationException(const std::string& details, 
    const std::string& source, const std::exception_ptr& father) : nct_exception{"", source, father}
{    
    info_ = exc_operation_error;
    if (details!="") {
        info_ += "\n";
        info_ += exc_details;
        info_ += details;
    }    
}

//-----------------------------------------------------------------------------------------------------------------
nct::OperationException::OperationException(const std::string& details, const std::string& step,
    const std::string& source, const std::exception_ptr& father) : nct_exception{"", source, father}
{
    info_ = exc_operation_error;

    if (details != "") {
        info_ += "\n";
        info_ += exc_details;
        info_ += details;
    }

    if (step != "") {
        info_ += "\n";
        info_ += exc_step;
        info_ += step;
    }
}

//-----------------------------------------------------------------------------------------------------------------
nct::OperationException::OperationException(const std::string& details, size_t step,
    const std::string& source, const std::exception_ptr& father) : nct_exception{"", source, father}
{
    info_ = exc_operation_error;
    if (details != "") {
        info_ += "\n";
        info_ += exc_details;
        info_ += details;
    }

    info_ += "\n";
    info_ += exc_step;
    info_ += std::to_string(step);
}

//=================================================================================================================
//        CLASS EmptyArrayException
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
nct::EmptyArrayException::EmptyArrayException()
{
    info_ = exc_empty_array;
}

//-----------------------------------------------------------------------------------------------------------------
nct::EmptyArrayException::EmptyArrayException(const std::string& source) : nct_exception{"", source}
{
    info_ = exc_empty_array;
}

//-----------------------------------------------------------------------------------------------------------------
nct::EmptyArrayException::EmptyArrayException(const std::string& arrayName,
    const std::string& source) : nct_exception{"", source}
{
    info_ = exc_empty_array;
    if (arrayName != "") {
        info_ += "\n";
        info_ += exc_array;
        info_ += arrayName;
    }
}

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
