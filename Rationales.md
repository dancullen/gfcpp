# Design Decisions and Rationales

- Don't use std::optional because it's simple enough just to implement our own boolean flag.

- We want to be able to handle multiple return values. Could use std::pair, but then you have to keep
  the order of the arguments straight (first, second,  etc.).
  Instead, you design your own type T and use Result<T> to handle some of the boilerplate,
  then you can simply do r.something or r.somethingElse rather than r.first and r.second.
  Granted, this means you're always creating your own types for every function, but at least
  the code is very easy to read, and readability is of utmost importance.
