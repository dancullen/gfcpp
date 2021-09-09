/**
 * result.hpp contains code for returning results from a function. C++ does not support
 * multiple return values, unlike Golang, nor does it have syntactic sugar for returning
 * tuples as in Python.
 *
 * TODO Put everything into a namespace 'gfc'.
 */

#pragma once

#include "errors.hpp"

#include <string>

namespace gfc {

/**
 * Result allows a function to return a data value and/or an error message.
 * This is essentially our own simple implementation of a Maybe/Either/Optional class.
 *
 * If the 'err' member is nil, the user should assume that the 'value' member is undefined.
 * Technically it will have been initialized with its default constructor, but semantics
 * advice against its use. Note that we're storing an instance of T, not a pointer to T,
 * (although the user could decide to make T itself a pointer) because we want to eliminate
 * the possibility against crashes/exceptions due to null pointers. The data value may remain
 * uninitialized but at least it will not be null.
 *
 * Note that the members are public for convenient access.
 */
template<typename T>
class Result
{
public:
    Result(const T &value_=T(), error err_=nil) :
        value(value_),
        err(err_) { }
public:
    T value;    ///< The data value.
    error err;  ///< The error message or nil.
};


/**
 * Success is a syntactic sugar factory method for initializing a successful Result<T>.
 */
template<typename T>
inline Result<T> Success(const T &value)
{
    return Result<T>(value, nil);
}


/**
 * Failure is a syntactic sugar factory method for initializing an error Result<T>.
 *
 * Note that you must provide the type when you invoke it because it cannot be
 * inferred from the arguments. e.g., Failure<MyCoolType>("something bad happened").
 */
template<typename T>
inline Result<T> Failure(const std::string &message)
{
    return Result<T>(T(), error(false, message));
}

} // namespace gfc
