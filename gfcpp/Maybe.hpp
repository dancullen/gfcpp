#pragma once

#include <string>

/**
 * @brief Maybe allows functions to return either a value
 * or an error message explaining why it could not be retrieved.
 */
template<typename T>
struct Maybe
{
    Maybe(void) : value(0), err("") { }
    Maybe(const T &v) : value(v), err("") { }
    Maybe(const std::string &e) : value(0), err(e) { }
    T value;
    std::string err;
};
