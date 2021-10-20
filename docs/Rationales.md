# Design Decisions and Rationales

- Don't use std::optional because it's simple enough just to implement our own boolean flag.
  Moreover, we often wish to return a value and/or an error message, whereas std::optional
  is better suited for returning a value and/or null.

- Rather than using std::pair for multiple return values, we use our own Result class,
  because 'ret.err' and 'ret.value' is bit more readabile than 'ret.first' and 'ret.second'
  (where 'ret' is the returned variable name). Also, a function signature that returns a
  Result<SomeType> is much more intuitive than a function signature that returns a std::pair.
