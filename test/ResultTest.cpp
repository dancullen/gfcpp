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
    return Result<int>::Err("some failure occurred");
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

TEST_CASE("Basic tests", "[gfcpp]")
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

/**
 * Data allows us to test our Result class with a more complex data type
 * than simple primitives like ints and bools and floats.
 */ 
struct Data
{
    std::string name = "dan";
    int age = 10;
};

TEST_CASE("Complex datatype", "[gfcpp]")
{
    Result<Data> good;
    CHECK("dan" == good.value.name);
    CHECK(10 == good.value.age);

    auto bad = Result<Data>::Err("failure");
    CHECK("failure" == bad.err);
}

TEST_CASE("Using a string as the data member")
{
    auto good = Result<std::string>("good");
    CHECK("" == good.err);
    CHECK("good" == good.value);

    auto ok = Result<std::string>::Ok("ok");
    CHECK("" == ok.err);
    CHECK("ok" == ok.value);

    auto bad = Result<std::string>::Err("bad");
    CHECK("bad" == bad.err);
    CHECK("" == bad.value);
}
