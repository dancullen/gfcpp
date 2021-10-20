#include "gfcpp/Maybe.hpp"

#include "catch2/catch.hpp"

#include <string>

static Maybe<int> doSomething(const bool shouldFail)
{
    if (shouldFail)
    {
        return Maybe<int>("some failure occurred");
    }
    return 42;
}

std::string doSomethingElse(void)
{
    Maybe<int> result = doSomething(false);
    if (result.err != "")
    {
        return "Error: something faled. Details: " + result.err;
    }
    return "";
}

TEST_CASE("Test the Maybe class", "[experiment]")
{
    Maybe<int> data = doSomething(true);
    CHECK(data.err != "");

    data = doSomething(false);
    CHECK("" == data.err);
    CHECK(42 == data.value);

    CHECK("" == doSomethingElse());
}
