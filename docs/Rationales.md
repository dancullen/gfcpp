# Design Decisions and Rationales

- Don't use std::optional because it's simple enough just to implement our own boolean flag.

- Rather than using std::pair for multiple return values, we use our own Result class,
  because 'ret.err' and 'ret.value' is bit more readabile than 'ret.first' and 'ret.second'
  (where 'ret' is the returned variable name).