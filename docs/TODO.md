# TODO

- Implement Unwrap function. https://pkg.go.dev/errors#Unwrap
  - Implement wrap/unwrap by adding std::vector<> to our gfcpp:error class! Also add some Catch2 unit tests to test this. And a simple 'run.sh' script.
    Also, I think the "Error()" function should automatically unwrap/print entire wrapped context-- yes?

- When you use `gfcpp::Failure<T>("some message")`, it doesn't provide any context.
  So add a macro to Result.hpp to wrap the message with CONTEXT. For example:

  ```cpp
  #define NewFailure(TemplateType, message) \
  gfcpp::Failure<TempalteTypeType>(CONTEXT(message))
  ```
