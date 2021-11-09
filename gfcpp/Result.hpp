#pragma once

#include <string>

namespace gfcpp {

/**
 * @brief Result allows functions to return either a value
 * or an error message explaining the failure.
 *
 * The value T can be any type that has a default constructor and a copy constructor.
 *
 * Inspired by [Rust's std::result::Result](https://doc.rust-lang.org/std/result/enum.Result.html).
 */
template<typename T>
struct Result
{
    Result(const T &v=T(), const std::string &e=std::string()) : value(v), err(e) { }
    static Result<T> Err(const std::string &e) { return Result<T>(T(), e); }
    static Result<T> Ok(const T &v) { return Result<T>(v); }

    bool isErr(void) const { return err.size() != 0; }
    bool isOk(void) const { return err.size() == 0; }

    T value;
    std::string err;
};

} // namespace gfcpp
