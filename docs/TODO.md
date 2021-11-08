# TODO

- Add a CONTEXT macro (maybe 'CTX' or 'FN' for brevity) into Result.hpp.
  See gfcpp/v0/errors.hpp for example.

  Add comment to CONTEXT macro:
  I'm REALLY looking forward to C++20 when we can change from the macro into some code inside our Result class!
  https://en.cppreference.com/w/cpp/utility/source_location/function_name

- Implement Unwrap function. https://pkg.go.dev/errors#Unwrap
  - Implement wrap/unwrap by adding std::vector<> to our gfcpp:error class!
    Also, I think the "Error()" function should automatically unwrap/print entire wrapped context-- yes?
