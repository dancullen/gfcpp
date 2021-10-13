/**
 * result.hpp contains code for returning results from a function. C++ does not support
 * multiple return values, unlike Golang, nor does it have syntactic sugar for returning
 * tuples as in Python. This code strives to be more readable and idiomatic than using std::pair.
 * It also is more flexible than std::optional because you can return an error message,
 * not just an empty result.
 */

#pragma once

#include "errors.hpp"

#include <string>

namespace gfcpp {

/**
 * Result allows a function to return a data value and/or an error message.
 *
 * Other libraries and languages may refer to this sort of class by various names:
 * Maybe, Either, Optional, Sometimes, Expected, Result, etc.
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

} // namespace gfcpp

/**
 * NewFailure returns a new Failure annotated with context.
 * It's basically a bit of syntactic sugar around invoking
 * Failure constructor with the CONTEXT macro.
 */
#define NewFailure(T, message) \
  gfcpp::Failure<T>(CONTEXT(message))
