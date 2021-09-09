/**
 * errors.hpp contains functions for manipulating errors. It is similar to Golang's `errors` package.
 *
 * TODO Implement Unwrap function. https://pkg.go.dev/errors#Unwrap
 * TODO Put everything into a namespace 'gfc'. (Golang-Flavored C++)
 */

#pragma once

#include <string>

namespace gfc {

/**
 * error allows errors to be handled in C++ with Golang-like syntax and idioms. In other words,
 * this class encapsulates a boolean success/failure result (i.e., error != nil) along with
 * a string containing the error message.
 */
class error
{
public:
    /**
     * Constructor initializes a new error object. It's basically like calling Golang's `errors.New` function.
     */
    error(const bool isNil, const std::string &message = "") : isNil_(isNil), message_(message) {}

    /**
     * operator bool allows the construct "if (err)".
     */
    explicit operator bool(void) const
    {
        return !isNil_;
    }

    /**
     * Error returns the error message.
     */
    std::string Error(void) const
    {
        return message_;
    }

private:
    /**
     * isNil_ keeps track of whether or not an error actually exists. We cannot just store std::string
     * as a raw pointer because that would leak memory. Wrapping it with a smart pointer seems wasteful.
     * And using an empty string as a sentinel value for no error would be a hack and would not be able
     * to distinguish between no error and an error that simply doesn't provide any detailed information
     * about the error.
     */
    bool isNil_;

    /**
     * message_ stores the details about the error. Note that you must check isNil_ for whether an error
     * occurred; an empty string does NOT indicate no error occurred-- it may simply indicate that no
     * details about the error are available. (No details would be poor practice but we support it anyway.)
     */
    std::string message_;
};


/**
 * nil is syntactic sugar for indicating a nil error, or in other words, a successful result.
 * It allows you to do comparisons such as `if (err != nil)`.
 */
static const error nil(true, "");


/**
 * CONTEXT wraps the given string with context info such as the current function's name.
 *
 * This MUST be implemented as a preprocessor macro in order for __func__ to be valid.
 * https://stackoverflow.com/questions/733056/is-there-a-way-to-get-function-name-inside-a-c-function
 */
#define CONTEXT(message) \
    (std::string(__func__) + std::string(": ") + std::string(message))


/**
 * NewError returns a new error, annotated with context. Takes either a 'std::string' or 'const char *' for message.
 * Inspired by https://pkg.go.dev/errors#New
 *
 * This MUST be implemented as a preprocessor macro in order for __func__ (see CONTEXT) to be valid.
 * https://stackoverflow.com/questions/733056/is-there-a-way-to-get-function-name-inside-a-c-function
 */
#define NewError(message) \
    error(false, CONTEXT(message))


/**
 * Errorf is used to wrap an existing error with details before it gets returned up the call stack.
 * Takes either 'std::string' or 'const char *' for 'message' and an 'error' for 'err'. Returns an
 * object of type 'error'. This is basically a poor man's version of fmt.Errorf() from Golang--
 * it simply concatenate the strings without supporting any printf-like formatting features.
 *
 * Inspired by https://pkg.go.dev/fmt#Errorf
 *
 * This MUST be implemented as a preprocessor macro in order for __func__ to be valid.
 * https://stackoverflow.com/questions/733056/is-there-a-way-to-get-function-name-inside-a-c-function
 */
#define Errorf(message, err) \
    error(false, std::string(__func__) + std::string(": ") + std::string(message) + err.Error())

} // namespace gfc
