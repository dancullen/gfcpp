#pragma once

#include <string>

namespace gfcpp {

/**
 * @brief Result allows functions to return either a value
 * or an error message explaining the failure.
 *
 *
 * Inspired by [Rust's std::result::Result](https://doc.rust-lang.org/std/result/enum.Result.html).
 */
template<typename T>
struct Result
{
    Result(void) : value(0), err("") { }
    Result(const T &v) : value(v), err("") { }
    Result(const std::string &e) : value(0), err(e) { }
    bool isErr(void) const { return err != ""; }
    bool isOk(void) const { return err == ""; }
    T value;
    std::string err;
};

} // namespace gfcpp