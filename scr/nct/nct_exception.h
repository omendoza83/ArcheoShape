//=================================================================================================================
/**
 *  @file       nct_exception.h
 *  @brief      nct::nct_exception class.
 *  @details    Declaration file of the nct::nct_exception base class and derived classes.
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

#ifndef NCT_EXCEPTION_H_INCLUDE
#define NCT_EXCEPTION_H_INCLUDE
//=================================================================================================================
//        HEADERS
//=================================================================================================================
#include <nct/nct.h>
#include <nct/nct_exception_strings.h>
#include <exception>
#include <string>

//=================================================================================================================
namespace nct {

////////// Enumerators //////////

/**
 *  @brief      Relational operators.
 *  @details    List of relational operators.
 */
enum class RelationalOperator : unsigned char {

    Equal,                  /**< Equal to. */

    NotEqual,               /**< Not equal to. */

    LowerThan,              /**< Lower than. */

    LowerThanOrEqualTo,     /**< Lower than or equal to. */

    GreaterThan,            /**< Greater than. */

    GreaterThanOrEqualTo,   /**< Greater than or equal to. */
};

/**
 *  @brief      Class for exception handling.
 *  @details    This abstract class is used to define classes that report exceptions.
 */
class NCT_EXPIMP nct_exception : public std::exception {

public:

    ////////// Constructors //////////
        
    /**
     *  @brief      Default constructor.
     *  @details    Initialization of an empty exception.
     *  @param[in]  father  Exception that was produced previously. The data 
     *              is copied to the class instance and is not released.
     */
    explicit nct_exception(const std::exception_ptr& father = nullptr);

    /**
     *  @brief      Exception with a info.
     *  @details    This constructor initializes an exception with the specified info.
     *  @param[in]  errorMessage  Error info.
     *  @param[in]  father  Exception that was produced previously. The data
     *              is copied to the class instance and is not released.
     */
    explicit nct_exception(const std::string& errorMessage,
        const std::exception_ptr& father = nullptr);

    /**
     *  @brief      Exception with details about the error and information about the source.
     *  @details    This constructor initializes an exception with the specified info and 
     *              the specified information about the source.
     *  @param[in]  errorMessage  Error info.
     *  @param[in]  source  A string that identifies the source of the exception 
     *              (member function, class, namespace, etc.).
     *  @param[in]  father  Exception that was produced previously. The data
     *              is copied to the class instance and is not released.
     */
    nct_exception(const std::string& errorMessage, const std::string& source,
        const std::exception_ptr& father = nullptr);

    /**
     *  @brief      Copy constructor.
     *  @details    This constructor copies the contents of an object of the same type.
     *  @param[in]  other  Another object of the same type whose contents are copied.
     */
    nct_exception(const nct_exception& other) = default;

    /**
     *  @brief      Move constructor.
     *  @details    This constructor moves the contents of an object to the new class instance.
     *  @param[in]  other  Another object of the same type whose contents are acquired.
     */
    nct_exception(nct_exception&& other) = default;

    ////////// Destructor //////////

    /**
     *  @brief      Destructor.
     *  @details    Class destructor. 
     */
    virtual ~nct_exception() = default;

    ////////// Operators //////////        

    /**
     *  @brief      Assignment operator.
     *  @details    This operator copies the contents of an object of the same type.
     *  @param[in]  other  Another object of the same type whose contents are copied.
     *  @returns    A reference to the object.
     */
    nct_exception& operator=(const nct_exception& other) = default;

    /**
     *  @brief      Move-assignment operator.
     *  @details    This operator acquires the contents of another object.
     *  @param[in]  other  Another object of the same type whose contents are acquired.
     *  @returns    A reference to the object.
     */
    nct_exception& operator=(nct_exception&& other) = default;

    ////////// Member functions //////////        

    /**
     *  @brief      What?
     *  @details    This function returns a null terminated character sequence that may be used to identify the other.
     *  @returns    The description of the error.
     */
    virtual const char* what() const noexcept override;

    /**
     *  @brief      Exception string.
     *  @details    This function returns the full description of the exception.
     *  @returns    The string with the complete description of the exception.
     */
    virtual const std::string& completeErrorDescription() const noexcept;

    /**
     *  @brief      Error information.
     *  @details    This function returns the basic information of the error.
     *  @returns    The string with the information of the error.
     */
    virtual const std::string& errorInfo() const noexcept;

    /**
     *  @brief      Source information.
     *  @details    This function returns the source information of the error.
     *  @returns    The string with the information of the source.
     */
    virtual const std::string& source() const noexcept;

    /**
     *  @brief      Timestamp.
     *  @details    This function returns the information of the moment when the ecxeption occurred.
     *  @returns    The string with the timestamp.
     */
    virtual const std::string& exceptionTimestamp() const noexcept;

    /**
     *  @brief      Father exception.
     *  @details    This function returns the father exception information.
     *  @returns    The father exception information.
     */
    virtual const std::exception_ptr& fatherException() const noexcept;

    /**
     *  @brief      Append exception to log file.
     *  @details    This function writes the exception to a log file.
     *  @param[in]  logFile  Log file path.
     */
    void appendToLogFile(std::string& logFile);

protected:

    ////////// Data members //////////

    mutable std::string error_;         /**< Complete error message. */

    std::string info_;                  /**< Basic information of the exception. */

    std::string sourceInfo_;            /**< Source of the exception. */

    std::string timestamp_;             /**< Timestamp of the exception. */

    std::exception_ptr fatherException_;    /**< Original exception that produced this exception. */
};

/**
 *  @brief      Memory exception.
 *  @details    This class is used to report an exception related to memory allocation.
 */
class NCT_EXPIMP MemoryException final : public nct_exception {

public:

    ////////// Constructors //////////

    /**
     *  @brief      Default constructor.
     *  @details    Initialization of an empty exception.
     *  @param[in]  father  Exception that was produced previously. The data
     *              is copied to the class instance and is not released.
     */
    explicit MemoryException(const std::exception_ptr& father = nullptr);

    /**
     *  @brief      Exception with information about its source.
     *  @details    This constructor initializes an exception with information about its source.
     *  @param[in]  source  A string that identifies the source of the exception 
     *              (member function, class, namespace, etc.).
     *  @param[in]  father  Exception that was produced previously. The data
     *              is copied to the class instance and is not released.
     */
    explicit MemoryException(const std::string& source, const std::exception_ptr& father = nullptr);    

};

/**
 *  @brief      Argument exception.
 *  @details    This class is used to report exceptions related to bad arguments that are
 *              passed to a method or function.
 */
class NCT_EXPIMP ArgumentException final : public nct_exception {

public:

    ////////// Constructors //////////

    /**
     *  @brief      Default constructor.
     *  @details    Initialization of an empty exception.
     */
    ArgumentException();

    /**
     *  @brief      Exception with information about the error and its source.
     *  @details    This constructor initializes an exception with information about its source  
     *              and the bad arguments.
     *  @param[in]  arguments  Names of the bad arguments.
     *  @param[in]  details  Error description.
     *  @param[in]  source  A string that identifies the source of the exception 
     *              (member function, class, namespace, etc.).
     */
    ArgumentException(const std::string& arguments, const std::string& source);

    /**
     *  @brief      Exception with information about the error and its source.
     *  @details    This constructor initializes an exception with information about its source  
     *              and the bad arguments.
     *  @param[in]  arguments  Arguments with problems.
     *  @param[in]  source  A string that identifies the source of the exception 
     *              (member function, class, namespace, etc.).
     */
    ArgumentException(const std::string& arguments, const std::string& details,
        const std::string& source);

    /**
     *  @brief      Exception with information about the error and its source.
     *  @details    This constructor initializes an exception with information about its source 
     *              and the bad argument including the valid values.
     *  @param[in]  argumentName  Argument name.
     *  @param[in]  value  Argument value.
     *  @param[in]  validValues  Valid values.
     *  @param[in]  source  A string that identifies the source of the exception 
     *              (member function, class, namespace, etc.).
     */
    ArgumentException(const std::string& argumentName, const std::string& value,
        const std::string& validValues, const std::string& source);

    /**
     *  @brief      Exception with information about the error and its source.
     *  @details    This constructor initializes an exception with information about its source 
     *              and the bad argument. The argument type is double.
     *  @param[in]  argumentName  Argument name.
     *  @param[in]  value  Argument value.
     *  @param[in]  source  A string that identifies the source of the exception 
     *              (member function, class, namespace, etc.).
     */
    ArgumentException(const std::string& argumentName, double value, const std::string& source);

    /**
     *  @brief      Exception with information about the error and its source.
     *  @details    This constructor initializes an exception with information about its source 
     *              and the argument that is out of range. The argument type is double.
     *  @param[in]  argumentName  Argument name.
     *  @param[in]  value  Argument value.
     *  @param[in]  limit  Limit of valid values.
     *  @param[in]  relationalOperator  Limit operator relation. It's used to stablish the valid range of 
     *              values.
     *  @param[in]  source  A string that identifies the source of the exception 
     *              (member function, class, namespace, etc.).
     */
    ArgumentException(const std::string& argumentName, double value, double limit,
        RelationalOperator relationalOperator, const std::string& source);

    /**
     *  @brief      Exception with information about the error and its source.
     *  @details    This constructor initializes an exception with information about its source and the
     *              bad argument including the valid values. The argument type is double an it's limited
     *              by two bounds.
     *  @param[in]  argumentName  Argument name.
     *  @param[in]  value  Argument value.
     *  @param[in]  limit1  One of the limits of the valid range.
     *  @param[in]  limit2  One of the limits of the valid range.
     *  @param[in]  relationalOperator1  Limit operator relation for limit 1. It's used to stablish the
     *              valid range of values.
     *  @param[in]  relationalOperator2  Limit operator relation for limit 2. It's used to stablish the
     *              valid range of values.
     *  @param[in]  source  A string that identifies the source of the exception (member function, class,
     *              namespace, etc.).
     */
    ArgumentException(const std::string& argumentName, double value, double limit1, double limit2,
        RelationalOperator relationalOperator1, RelationalOperator relationalOperator2,
        const std::string& source);

    /**
     *  @brief      Exception with information about the error and its source.
     *  @details    This constructor initializes an exception with information about its source 
     *              and the bad argument. The argument type is int.
     *  @param[in]  argumentName  Argument name.
     *  @param[in]  value  Argument value.
     *  @param[in]  source  A string that identifies the source of the exception 
     *              (member function, class, namespace, etc.).
     */
    ArgumentException(const std::string& argumentName, int value,
        const std::string& source);

    /**
     *  @brief      Exception with information about the error and its source.
     *  @details    This constructor initializes an exception with information about its source and the
     *              argument that is out of range. The argument type is double.
     *  @param[in]  argumentName  Argument name.
     *  @param[in]  value  Argument value.
     *  @param[in]  limit  Limit of valid values.
     *  @param[in]  relationalOperator  Limit operator relation. It's used to stablish the valid range of
     *              values.
     *  @param[in]  source  A string that identifies the source of the exception (member function, class,
     *              namespace, etc.).
     */
    ArgumentException(const std::string& argumentName, int value, int limit,
        RelationalOperator relationalOperator, const std::string& source);

    /**
     *  @brief      Exception with information about the error and its source.
     *  @details    This constructor initializes an exception with information about its source and the
     *              bad argument including the valid values. The argument type is double an it's limited
     *              by two bounds.
     *  @param[in]  argumentName  Argument name.
     *  @param[in]  value  Argument value.
     *  @param[in]  limit1  One of the limits of the valid range.
     *  @param[in]  limit2  One of the limits of the valid range.
     *  @param[in]  relationalOperator1  Limit operator relation for limit 1. It's used to stablish the
     *              valid range of values.
     *  @param[in]  relationalOperator2  Limit operator relation for limit 2. It's used to stablish the
     *              valid range of values.
     *  @param[in]  source  A string that identifies the source of the exception (member function, class,
     *              namespace, etc.).
     */
    ArgumentException(const std::string& argumentName, int value, int limit1,
        int limit2, RelationalOperator relationalOperator1,
        RelationalOperator relationalOperator2, const std::string& source);

    /**
     *  @brief      Exception with information about the error and its source.
     *  @details    This constructor initializes an exception with information about its source 
     *              and the bad argument. The argument type is int.
     *  @param[in]  argumentName  Argument name.
     *  @param[in]  value  Argument value.
     *  @param[in]  source  A string that identifies the source of the exception 
     *              (member function, class, namespace, etc.).
     */
    ArgumentException(const std::string& argumentName, unsigned int value,
        const std::string& source);

    /**
     *  @brief      Exception with information about the error and its source.
     *  @details    This constructor initializes an exception with information about its source and the
     *              argument that is out of range. The argument type is double.
     *  @param[in]  argumentName  Argument name.
     *  @param[in]  value  Argument value.
     *  @param[in]  limit  Limit of valid values.
     *  @param[in]  relationalOperator  Limit operator relation. It's used to stablish the valid range of
     *              values.
     *  @param[in]  source  A string that identifies the source of the exception (member function, class,
     *              namespace, etc.).
     */
    ArgumentException(const std::string& argumentName, unsigned int value, unsigned int limit,
        RelationalOperator relationalOperator, const std::string& source);

    /**
     *  @brief      Exception with information about the error and its source.
     *  @details    This constructor initializes an exception with information about its source and the
     *              bad argument including the valid values. The argument type is double an it's limited
     *              by two bounds.
     *  @param[in]  argumentName  Argument name.
     *  @param[in]  value  Argument value.
     *  @param[in]  limit1  One of the limits of the valid range.
     *  @param[in]  limit2  One of the limits of the valid range.
     *  @param[in]  relationalOperator1  Limit operator relation for limit 1. It's used to stablish the
     *              valid range of values.
     *  @param[in]  relationalOperator2  Limit operator relation for limit 2. It's used to stablish the
     *              valid range of values.
     *  @param[in]  source  A string that identifies the source of the exception (member function, class,
     *              namespace, etc.).
     */
    ArgumentException(const std::string& argumentName, unsigned int value, unsigned int limit1,
        unsigned int limit2, RelationalOperator relationalOperator1,
        RelationalOperator relationalOperator2, const std::string& source);

    /**
     *  @brief      Exception with information about the error and its source.
     *  @details    This constructor initializes an exception with information about its source 
     *              and the bad argument. The argument type is int.
     *  @param[in]  argumentName  Argument name.
     *  @param[in]  value  Argument value.
     *  @param[in]  source  A string that identifies the source of the exception 
     *              (member function, class, namespace, etc.).
     */
    ArgumentException(const std::string& argumentName, long long value,
        const std::string& source);

    /**
     *  @brief      Exception with information about the error and its source.
     *  @details    This constructor initializes an exception with information about its source and the
     *              argument that is out of range. The argument type is double.
     *  @param[in]  argumentName  Argument name.
     *  @param[in]  value  Argument value.
     *  @param[in]  limit  Limit of valid values.
     *  @param[in]  relationalOperator  Limit operator relation. It's used to stablish the valid range of
     *              values.
     *  @param[in]  source  A string that identifies the source of the exception (member function, class,
     *              namespace, etc.).
     */
    ArgumentException(const std::string& argumentName, long long value, long long limit,
        RelationalOperator relationalOperator, const std::string& source);

    /**
     *  @brief      Exception with information about the error and its source.
     *  @details    This constructor initializes an exception with information about its source and the
     *              bad argument including the valid values. The argument type is double an it's limited
     *              by two bounds.
     *  @param[in]  argumentName  Argument name.
     *  @param[in]  value  Argument value.
     *  @param[in]  limit1  One of the limits of the valid range.
     *  @param[in]  limit2  One of the limits of the valid range.
     *  @param[in]  relationalOperator1  Limit operator relation for limit 1. It's used to stablish the
     *              valid range of values.
     *  @param[in]  relationalOperator2  Limit operator relation for limit 2. It's used to stablish the
     *              valid range of values.
     *  @param[in]  source  A string that identifies the source of the exception (member function, class,
     *              namespace, etc.).
     */
    ArgumentException(const std::string& argumentName, long long value, long long limit1,
        long long limit2, RelationalOperator relationalOperator1,
        RelationalOperator relationalOperator2, const std::string& source);

    /**
     *  @brief      Exception with information about the error and its source.
     *  @details    This constructor initializes an exception with information about its source 
     *              and the bad argument. The argument type is int.
     *  @param[in]  argumentName  Argument name.
     *  @param[in]  value  Argument value.
     *  @param[in]  source  A string that identifies the source of the exception 
     *              (member function, class, namespace, etc.).
     */
    ArgumentException(const std::string& argumentName, unsigned long long value,
        const std::string& source);

    /**
     *  @brief      Exception with information about the error and its source.
     *  @details    This constructor initializes an exception with information about its source and the
     *              argument that is out of range. The argument type is double.
     *  @param[in]  argumentName  Argument name.
     *  @param[in]  value  Argument value.
     *  @param[in]  limit  Limit of valid values.
     *  @param[in]  relationalOperator  Limit operator relation. It's used to stablish the valid range of
     *              values.
     *  @param[in]  source  A string that identifies the source of the exception (member function, class,
     *              namespace, etc.).
     */
    ArgumentException(const std::string& argumentName, unsigned long long value,
        unsigned long long limit,
        RelationalOperator relationalOperator, const std::string& source);

    /**
     *  @brief      Exception with information about the error and its source.
     *  @details    This constructor initializes an exception with information about its source and the
     *              bad argument including the valid values. The argument type is double an it's limited
     *              by two bounds.
     *  @param[in]  argumentName  Argument name.
     *  @param[in]  value  Argument value.
     *  @param[in]  limit1  One of the limits of the valid range.
     *  @param[in]  limit2  One of the limits of the valid range.
     *  @param[in]  relationalOperator1  Limit operator relation for limit 1. It's used to stablish the
     *              valid range of values.
     *  @param[in]  relationalOperator2  Limit operator relation for limit 2. It's used to stablish the
     *              valid range of values.
     *  @param[in]  source  A string that identifies the source of the exception (member function, class,
     *              namespace, etc.).
     */
    ArgumentException(const std::string& argumentName, unsigned long long value,
        unsigned long long limit1,
        unsigned long long limit2, RelationalOperator relationalOperator1,
        RelationalOperator relationalOperator2, const std::string& source);

};

/**
 *  @brief      Index out of range exception.
 *  @details    This class is used to create exceptions related to bad indices.
 */
class NCT_EXPIMP IndexOutOfRangeException final : public nct_exception {

public:

    ////////// Constructors //////////

    /**
     *  @brief      Default constructor.
     *  @details    Initialization of an empty exception.
     */
    IndexOutOfRangeException();

    /**
     *  @brief      Exception with information about the error and its source.
     *  @details    This constructor initializes an exception with information about its source 
     *              and the wrong index.
     *  @param[in]  source  A string that identifies the source of the exception 
     *              (member function, class, namespace, etc.).
     */
    explicit IndexOutOfRangeException(const std::string& source);

    /**
     *  @brief      Exception with information about the error and its source.
     *  @details    This constructor initializes an exception with information about its source 
     *              and the wrong indexes.
     *  @param[in]  indexName  Index name(s).
     *  @param[in]  source  A string that identifies the source of the exception 
     *              (member function, class, namespace, etc.).
     */
    IndexOutOfRangeException(const std::string& indexName, const std::string& source);

    /**
     *  @brief      Exception with information about the error and its source.
     *  @details    This constructor initializes an exception with information about its source 
     *              and the wrong index.
     *  @param[in]  indexName  Index name.
     *  @param[in]  value  Index value.
     *  @param[in]  validValues  Range of valid values.
     *  @param[in]  source  A string that identifies the source of the exception 
     *              (member function, class, namespace, etc.).
     */
    IndexOutOfRangeException(const std::string& indexName, const std::string& value,
        const std::string& validValues, const std::string& source);

    /**
     *  @brief      Exception with information about the error and its source.
     *  @details    This constructor initializes an exception with information about its source 
     *              and the wrong index.
     *  @param[in]  indexName  Index name.
     *  @param[in]  value  Index value.
     *  @param[in]  source  A string that identifies the source of the exception 
     *              (member function, class, namespace, etc.).
     */
    IndexOutOfRangeException(const std::string& indexName, diff_t value,
        const std::string& source);

    /**
     *  @brief      Exception with information about the error and its source.
     *  @details    This constructor initializes an exception with information about its source and the
     *              index out of range. 
     *  @param[in]  indexName  Index name.
     *  @param[in]  value  Index value.
     *  @param[in]  limit  Limit of valid values.
     *  @param[in]  relationalOperator  Limit operator relation. It's used to stablish the valid range of
     *              values.
     *  @param[in]  source  A string that identifies the source of the exception (member function, class,
     *              namespace, etc.).
     */
    IndexOutOfRangeException(const std::string& indexName,
        diff_t value, diff_t limit,
        RelationalOperator relationalOperator, const std::string& source);
    
    /**
     *  @brief      Exception with information about the error and its source.
     *  @details    This constructor initializes an exception with information about its source and the
     *              wrong index including the valid values. 
     *  @param[in]  indexName  Index name.
     *  @param[in]  value  Index value.
     *  @param[in]  limit1  One of the limits of the valid range.
     *  @param[in]  limit2  One of the limits of the valid range.
     *  @param[in]  relationalOperator1  Limit operator relation for limit 1. It's used to stablish the
     *              valid range of values.
     *  @param[in]  relationalOperator2  Limit operator relation for limit 2. It's used to stablish the
     *              valid range of values.
     *  @param[in]  source  A string that identifies the source of the exception (member function, class,
     *              namespace, etc.).
     */
    IndexOutOfRangeException(const std::string& indexName, diff_t value,
        diff_t limit1, diff_t limit2,
        RelationalOperator relationalOperator1,
        RelationalOperator relationalOperator2, const std::string& source);

    /**
     *  @brief      Exception with information about the error and its source.
     *  @details    This constructor initializes an exception with information about its source 
     *              and the wrong index.
     *  @param[in]  indexName  Index name.
     *  @param[in]  value  Index value.
     *  @param[in]  source  A string that identifies the source of the exception 
     *              (member function, class, namespace, etc.).
     */
    IndexOutOfRangeException(const std::string& indexName, size_t value,
        const std::string& source);

    /**
     *  @brief      Exception with information about the error and its source.
     *  @details    This constructor initializes an exception with information about its source 
     *              and the index out of range. 
     *  @param[in]  indexName  Index name.
     *  @param[in]  value  Index value.
     *  @param[in]  limit  Limit of valid values.
     *  @param[in]  relationalOperator  Limit operator relation. It's used to stablish the valid range
     *              of values.
     *  @param[in]  source  A string that identifies the source of the exception 
     *              (member function, class, namespace, etc.).
     */
    IndexOutOfRangeException(const std::string& indexName,
        size_t value, size_t limit, RelationalOperator relationalOperator, const std::string& source);

    /**
     *  @brief      Exception with information about the error and its source.
     *  @details    This constructor initializes an exception with information about its source and the
     *              wrong index including the valid values. 
     *  @param[in]  indexName  Index name.
     *  @param[in]  value  Index value.
     *  @param[in]  limit1  One of the limits of the valid range.
     *  @param[in]  limit2  One of the limits of the valid range.
     *  @param[in]  relationalOperator1  Limit operator relation for limit 1. It's used to stablish the
     *              valid range of values.
     *  @param[in]  relationalOperator2  Limit operator relation for limit 2. It's used to stablish the
     *              valid range of values.
     *  @param[in]  source  A string that identifies the source of the exception (member function, class,
     *              namespace, etc.).
     */
    IndexOutOfRangeException(const std::string& indexName, size_t value,
        size_t limit1, size_t limit2, RelationalOperator relationalOperator1,
        RelationalOperator relationalOperator2, const std::string& source);

};

/**
 *  @brief      Iterator exception.
 *  @details    This class is used to create exceptions when an iterator is out of range
 *              or it can't be used in certain operation.
 */
class NCT_EXPIMP IteratorException final : public nct_exception {

public:

    ////////// Constructors //////////

    /**
     *  @brief      Default constructor.
     *  @details    Initialization of an empty exception.
     */
    IteratorException();

    /**
     *  @brief      Exception with information about its source.
     *  @details    This constructor initializes an exception with information about its source.
     *  @param[in]  source  A string that identifies the source of the exception 
     *              (member function, class, namespace, etc.).
     */
    explicit IteratorException(const std::string& source);

    /**
     *  @brief      Exception with information about its source.
     *  @details    This constructor initializes an exception with information about its source.
     *  @param[in]  iteratorName  Iterator name.
     *  @param[in]  source  A string that identifies the source of the exception 
     *              (member function, class, namespace, etc.).
     */
    IteratorException(const std::string& iteratorName, const std::string& source);
};

/**
 *  @brief      Null pointer exception.
 *  @details    Class to report errors related to the use of null pointers.
 */
class NCT_EXPIMP NullPointerException final : public nct_exception {

public:

    ////////// Constructors //////////

    /**
     *  @brief      Default constructor.
     *  @details    Initialization of an empty exception.
     */
    NullPointerException();

    /**
     *  @brief      Exception with information about its source.
     *  @details    This constructor initializes an exception with information about its source.
     *  @param[in]  source  A string that identifies the source of the exception
     *              (member function, class, namespace, etc.).
     */
    explicit NullPointerException(const std::string& source);

    /**
     *  @brief      Exception with information about the error and its source.
     *  @details    This constructor initializes an exception with information about its source 
     *              and the error characteristics.
     *  @param[in]  pointerName  Name of the pointer that is null.
     *  @param[in]  source  A string that identifies the source of the exception
     *              (member function, class, namespace, etc.).
     */
    NullPointerException(const std::string& pointerName, const std::string& source);

};

/**
 *  @brief      Iterator exception.
 *  @details    This class is used to create exceptions when a an invalid
 *              address is being dereferenced.
 */
class NCT_EXPIMP NullIteratorException final : public nct_exception {

public:

    ////////// Constructors //////////

    /**
     *  @brief      Default constructor.
     *  @details    Initialization of an empty exception.
     */
    NullIteratorException();

    /**
     *  @brief      Exception with information about its source.
     *  @details    This constructor initializes an exception with information about its source.
     *  @param[in]  source  A string that identifies the source of the exception 
     *              (member function, class, namespace, etc.).
     */
    explicit NullIteratorException(const std::string& source);

    /**
     *  @brief      Exception with information about its source.
     *  @details    This constructor initializes an exception with information about its source.
     *  @param[in]  iteratorName  Iterator name.
     *  @param[in]  source  A string that identifies the source of the exception 
     *              (member function, class, namespace, etc.).
     */
    NullIteratorException(const std::string& iteratorName, const std::string& source);

};

/**
 *  @brief      Range exception.
 *  @details    This class is used to create exceptions when one specified
 *              range is not valid. In this library, the word range has two meanings: \n
 *              * The upper and lower bounds of an array (or sub-array). In this case,
 *                a range is not valid if two specified indices cannot be used to address 
 *                valid elements whithin an array or a list to complete an operation, 
 *                either because the new sub-array only contains few elements, or
 *                the indices are out of bounds. \n
 *              * A pair of begin/end iterators packed together. In this case, a range is
 *                not valid if two iterators cannot be used to access the necessary elements
 *                of a sequence to complete one task.
 */
class NCT_EXPIMP RangeException final : public nct_exception {

public:

    ////////// Constructors //////////

    /**
     *  @brief      Default constructor.
     *  @details    Initialization of an empty exception.
     */
    RangeException();

    /**
     *  @brief      Exception with information about its source.
     *  @details    This constructor initializes an exception with information about its source.
     *  @param[in]  source  A string that identifies the source of the exception 
     *              (member function, class, namespace, etc.).
     */
    explicit RangeException(const std::string& source);

    /**
     *  @brief      Exception with information about its source.
     *  @details    This constructor initializes an exception with information about its source.
     *  @param[in]  range  Range name or description.
     *  @param[in]  source  A string that identifies the source of the exception 
     *              (member function, class, namespace, etc.).
     */
    RangeException(const std::string& range, const std::string& source);

    /**
     *  @brief      Exception with information about its source.
     *  @details    This constructor initializes an exception with information about its source
     *              and the error characteristics.
     *  @param[in]  range  Range name or description.
     *  @param[in]  details  Error description.
     *  @param[in]  source  A string that identifies the source of the exception
     *              (member function, class, namespace, etc.).
     */
    RangeException(const std::string& range, const std::string& details, const std::string& source);

};

/**
 *  @brief      Inicialization exception.
 *  @details    This class is used to report exceptions when an error occurs in an object
 *              initialization.
 */
class NCT_EXPIMP InitializationException final : public nct_exception {

public:

    ////////// Constructors //////////

    /**
     *  @brief      Default constructor.
     *  @details    Initialization of an empty exception.
     *  @param[in]  father  Exception that was produced previously. The data
     *              is copied to the class instance and is not released.
     */
    explicit InitializationException(const std::exception_ptr& father = nullptr);

    /**
     *  @brief      Exception with information about its source.
     *  @details    This constructor initializes an exception with information about its source.
     *  @param[in]  source  A string that identifies the source of the exception 
     *              (member function, class, namespace, etc.).
     *  @param[in]  father  Exception that was produced previously. The data
     *              is copied to the class instance and is not released.
     */
    explicit InitializationException(const std::string& source, const std::exception_ptr& father = nullptr);
};

/**
 *  @brief      Member exception.
 *  @details    This class is used to report errors when a class member is not implemented.
 */
class NCT_EXPIMP MemberException final : public nct_exception {

public:

    ////////// Constructors //////////

    /**
     *  @brief      Default constructor.
     *  @details    Initialization of an empty exception.
     *  @param[in]  father  Exception that was produced previously. The data
     *              is copied to the class instance and is not released.
     */
    explicit MemberException(const std::exception_ptr& father = nullptr);

    /**
     *  @brief      Exception with information about its source.
     *  @details    This constructor initializes an exception with information about its source.
     *  @param[in]  source  A string that identifies the source of the exception 
     *              (member function, class, namespace, etc.).
     *  @param[in]  father  Exception that was produced previously. The data
     *              is copied to the class instance and is not released.
     */
    explicit MemberException(const std::string& source, const std::exception_ptr& father = nullptr);
    
    /**
     *  @brief      Exception with information about the error and its source.
     *  @details    This constructor initializes an exception with information about its source
     *              and the error characteristics.
     *  @param[in]  details  Error description.
     *  @param[in]  source  A string that identifies the source of the exception
     *              (member function, class, namespace, etc.).
     *  @param[in]  father  Exception that was produced previously. The data
     *              is copied to the class instance and is not released.
     */
    MemberException(const std::string& details, const std::string& source,
        const std::exception_ptr& father = nullptr);
};

/**
 *  @brief      Arithmetic exception.
 *  @details    This class is used to report errors in arithmetic operations.
 */
class NCT_EXPIMP ArithmeticException final : public nct_exception {

public:

    ////////// Constructors //////////

    /**
     *  @brief      Default constructor.
     *  @details    Initialization of an empty exception.
     *  @param[in]  father  Exception that was produced previously. The data
     *              is copied to the class instance and is not released.
     */
    explicit ArithmeticException(const std::exception_ptr& father = nullptr);

    /**
     *  @brief      Exception with information about the error and its source.
     *  @details    This constructor initializes an exception with information about its source 
     *              and the error characteristics.
     *  @param[in]  details  Error description.
     *  @param[in]  source  A string that identifies the source of the exception 
     *              (member function, class, namespace, etc.).
     *  @param[in]  father  Exception that was produced previously. The data
     *              is copied to the class instance and is not released.
     */
    ArithmeticException(const std::string& details, const std::string& source,
        const std::exception_ptr& father = nullptr);
};

/**
 *  @brief      Bad configuration exception.
 *  @details    This class is used to report errors related to an object configuration.
 */
class NCT_EXPIMP ConfigurationException final : public nct_exception {

public:

    ////////// Constructors //////////

    /**
     *  @brief      Default constructor.
     *  @details    Initialization of an empty exception.
     *  @param[in]  father  Exception that was produced previously. The data
     *              is copied to the class instance and is not released.
     */
    explicit ConfigurationException(const std::exception_ptr& father = nullptr);

    /**
     *  @brief      Exception with information about the error and its source.
     *  @details    This constructor initializes an exception with information about its source 
     *              and the error characteristics.
     *  @param[in]  source  A string that identifies the source of the exception
     *              (member function, class, namespace, etc.).
     *  @param[in]  father  Exception that was produced previously. The data
     *              is copied to the class instance and is not released.
     */
    ConfigurationException(const std::string& source,
        const std::exception_ptr& father = nullptr);

    /**
     *  @brief      Exception with information about the error and its source.
     *  @details    This constructor initializes an exception with information about its source 
     *              and the error characteristics.
     *  @param[in]  details  Error description.
     *  @param[in]  source  A string that identifies the source of the exception 
     *              (member function, class, namespace, etc.).
     *  @param[in]  father  Exception that was produced previously. The data
     *              is copied to the class instance and is not released.
     */
    ConfigurationException(const std::string& details, const std::string& source,
        const std::exception_ptr& father = nullptr);

};

/**
 *  @brief      IO exception.
 *  @details    Class to report errors in input-output operations.
 */
class NCT_EXPIMP IOException final : public nct_exception {

public:

    ////////// Constructors //////////

    /**
     *  @brief      Default constructor.
     *  @details    Initialization of an empty exception.
     *  @param[in]  father  Exception that was produced previously. The data
     *              is copied to the class instance and is not released.
     */
    explicit IOException(const std::exception_ptr& father = nullptr);

    /**
     *  @brief      Exception with information about the error and its source.
     *  @details    This constructor initializes an exception with information about its source 
     *              and the error characteristics.
     *  @param[in]  details  Error description.
     *  @param[in]  source  A string that identifies the source of the exception 
     *              (member function, class, namespace, etc.).
     *  @param[in]  father  Exception that was produced previously. The data
     *              is copied to the class instance and is not released.
     */
    IOException(const std::string& details, const std::string& source,
        const std::exception_ptr& father = nullptr);

    /**
     *  @brief      Exception with information about the error and its source.
     *  @details    This constructor initializes an exception with information about its source 
     *              and the error characteristics.
     *  @param[in]  file  File that was intended to read or write.
     *  @param[in]  details  Error description.
     *  @param[in]  source  A string that identifies the source of the exception 
     *              (member function, class, namespace, etc.).
     *  @param[in]  father  Exception that was produced previously. The data
     *              is copied to the class instance and is not released.
     */
    IOException(const std::string& file, const std::string& details,
        const std::string& source, const std::exception_ptr& father = nullptr);
};

/**
 *  @brief      Operation exception.
 *  @details    Class for errors related to an operation or calculation.
 */
class NCT_EXPIMP OperationException final : public nct_exception {

public:

    ////////// Constructors //////////

    /**
     *  @brief      Default constructor.
     *  @details    Initialization of an empty exception.
     *  @param[in]  father  Exception that was produced previously. The data
     *              is copied to the class instance and is not released.
     */
    explicit OperationException(const std::exception_ptr& father = nullptr);

    /**
     *  @brief      Exception with information about the error and its source.
     *  @details    This constructor initializes an exception with information about its source 
     *              and the error characteristics.
     *  @param[in]  details  Error description.
     *  @param[in]  source  A string that identifies the source of the exception 
     *              (member function, class, namespace, etc.).
     *  @param[in]  father  Exception that was produced previously. The data
     *              is copied to the class instance and is not released.
     */
    OperationException(const std::string& details, const std::string& source,
        const std::exception_ptr& father = nullptr);
    
    /**
     *  @brief      Exception with information about the error and its source.
     *  @details    This constructor initializes an exception with information about its source
     *              and the error characteristics. This costructor is used when the operation
     *              is separated in several steps, and the error was identified at one
     *              specific step.
     *  @param[in]  details  Error description.
     *  @param[in]  step  The name of the step that produced the error.
     *  @param[in]  source  A string that identifies the source of the exception
     *              (member function, class, namespace, etc.).
     *  @param[in]  father  Exception that was produced previously. The data
     *              is copied to the class instance and is not released.
     */
    OperationException(const std::string& details, const std::string& step,
        const std::string& source, const std::exception_ptr& father = nullptr);

    /**
     *  @brief      Exception with information about the error and its source.
     *  @details    This constructor initializes an exception with information about its source 
     *              and the error characteristics. This costructor is used when the operation
     *              is separated in several steps, and the error was identified at one
     *              specific index.
     *  @param[in]  details  Error description.
     *  @param[in]  step  The index of the step that produced the error.
     *  @param[in]  source  A string that identifies the source of the exception
     *              (member function, class, namespace, etc.).     
     *  @param[in]  father  Exception that was produced previously. The data
     *              is copied to the class instance and is not released.
     */
    OperationException(const std::string& details, size_t step, 
        const std::string& source, const std::exception_ptr& father = nullptr);    
};

/**
 *  @brief      Empty array exception.
 *  @details    Class used to report errors reletaed with the use of empty arrays.
 */
class NCT_EXPIMP EmptyArrayException final : public nct_exception {

public:

    ////////// Constructors //////////

    /**
     *  @brief      Default constructor.
     *  @details    Initialization of an empty exception.
     */
    EmptyArrayException();

    /**
     *  @brief      Exception with information about its source.
     *  @details    This constructor initializes an exception with information about its source.
     *  @param[in]  source  A string that identifies the source of the exception
     *              (member function, class, namespace, etc.).
     */
    explicit EmptyArrayException(const std::string& source);

    /**
     *  @brief      Exception with information about the error and its source.
     *  @details    This constructor initializes an exception with information about its source 
     *              and the error characteristics.
     *  @param[in]  arrayName  Name of the empty array.
     *  @param[in]  source  A string that identifies the source of the exception
     *              (member function, class, namespace, etc.).
     */
    EmptyArrayException(const std::string& arrayName, const std::string& source);
};

}

#endif
//=================================================================================================================
//        END OF FILE
//=================================================================================================================
