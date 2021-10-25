// Copyright 2021 Jeremiah Griffin
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
// WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
// ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
// ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
// OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

#include <frequencypp/frequency.hpp>

#include <catch2/catch.hpp>

#include <climits>

TEST_CASE("SI unit types specify correct representations", "[constructor]")
{
    using namespace ::frequencypp;

    REQUIRE(sizeof(nanohertz::rep) * CHAR_BIT >= 64);
    REQUIRE(sizeof(microhertz::rep) * CHAR_BIT >= 64);
    REQUIRE(sizeof(millihertz::rep) * CHAR_BIT >= 64);
    REQUIRE(sizeof(hertz::rep) * CHAR_BIT >= 64);
    REQUIRE(sizeof(kilohertz::rep) * CHAR_BIT >= 55);
    REQUIRE(sizeof(megahertz::rep) * CHAR_BIT >= 45);
    REQUIRE(sizeof(gigahertz::rep) * CHAR_BIT >= 32);
    REQUIRE(sizeof(terahertz::rep) * CHAR_BIT >= 25);
    REQUIRE(sizeof(petahertz::rep) * CHAR_BIT >= 15);
}

TEST_CASE("SI unit types specify correct periods", "[constructor]")
{
    using namespace ::frequencypp;

    REQUIRE(std::ratio_equal_v<nanohertz::period, std::nano>);
    REQUIRE(std::ratio_equal_v<microhertz::period, std::micro>);
    REQUIRE(std::ratio_equal_v<millihertz::period, std::milli>);
    REQUIRE(std::ratio_equal_v<hertz::period, std::ratio<1>>);
    REQUIRE(std::ratio_equal_v<kilohertz::period, std::kilo>);
    REQUIRE(std::ratio_equal_v<megahertz::period, std::mega>);
    REQUIRE(std::ratio_equal_v<gigahertz::period, std::giga>);
    REQUIRE(std::ratio_equal_v<terahertz::period, std::tera>);
    REQUIRE(std::ratio_equal_v<petahertz::period, std::peta>);
}
