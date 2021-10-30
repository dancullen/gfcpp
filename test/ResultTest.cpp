#include "gfcpp/Result.hpp"

#include "catch2/catch.hpp"

#include <string>

using gfcpp::Result;

static Result<int> shouldSucceed(void)
{
    return 42;
}

static Result<int> shouldFail(void)
{
    return Result<int>("some failure occurred");
}

static std::string alsoShouldSucceed(void)
{
    auto result = shouldSucceed();
    if (result.err != "")
    {
        return "Error: something faled. Details: " + result.err;
    }
    return "";
}

TEST_CASE("Test the Maybe class", "[experiment]")
{
    auto data = shouldSucceed();
    CHECK("" == data.err);
    CHECK(42 == data.value);
    CHECK(!data.isErr());
    CHECK(data.isOk());

    data = shouldFail();
    CHECK(data.err != "");
    CHECK(data.isErr());
    CHECK(!data.isOk());

    CHECK("" == alsoShouldSucceed());
}
