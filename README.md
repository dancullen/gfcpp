# Golang-Flavored C++ (GFCPP)

This C++ library helps you to write your C++ code in Go style by providing:

- Go-inspired error handling classes, functions, and macros.

- A `Result` class to emulate Go's convention of returning
  the error (or nil) as one of the multiple return values.

- **UPDATE 2021-10-20**: The code in `error.hpp` and `result.hpp` seems a bit bloated.
  Consider instead using the newly-added `Maybe` class, which is a bit simpler,
  easier-to-learn, and lighter on the cognitive load.

This a header-only, C++11-compatible library with no additional dependencies,
which makes it trivial to include in your own projects.

## Getting Started

To use this framework in your own project, simply `#include` the relevant header files.
See the unit tests in the `test` folder for example usage. The script `run.sh` demonstrates
how to build the code with CMake and run the tests.
