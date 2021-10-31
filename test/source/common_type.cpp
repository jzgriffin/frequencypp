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

#include <iostream>
#include <ratio>
#include <type_traits>

TEST_CASE("common_type finds the correct representation", "[common_type]")
{
    using namespace ::frequencypp;

    // Identical case
    REQUIRE(std::is_same_v<std::common_type_t<frequency<int>, frequency<int>>::rep, int>);
    REQUIRE(std::is_same_v<std::common_type_t<frequency<float>, frequency<float>>::rep, float>);

    REQUIRE(std::is_same_v<std::common_type_t<frequency<int>, frequency<float>>::rep, float>);
    REQUIRE(std::is_same_v<std::common_type_t<frequency<float>, frequency<int>>::rep, float>);

    REQUIRE(std::is_same_v<std::common_type_t<frequency<float>, frequency<double>>::rep, double>);
}

TEST_CASE("common_type finds the correct period", "[common_type]")
{
    using namespace ::frequencypp;

    // Identical case
    REQUIRE(std::ratio_equal_v<std::common_type_t<frequency<int>, frequency<int>>::period,
        std::ratio<1>>);
    REQUIRE(std::ratio_equal_v<std::common_type_t<frequency<int, std::ratio<10, 1>>,
                                   frequency<int, std::ratio<10, 1>>>::period,
        std::ratio<10, 1>>);

    REQUIRE(std::ratio_equal_v<std::common_type_t<frequency<int, std::ratio<10, 1>>,
                                   frequency<int, std::ratio<20, 2>>>::period,
        std::ratio<10, 1>>);
    REQUIRE(std::ratio_equal_v<std::common_type_t<frequency<int, std::ratio<20, 2>>,
                                   frequency<int, std::ratio<10, 1>>>::period,
        std::ratio<10, 1>>);

    REQUIRE(std::ratio_equal_v<std::common_type_t<frequency<float, std::ratio<1, 52>>,
                                   frequency<float, std::ratio<1, 442>>>::period,
        std::ratio<1, 884>>);
    REQUIRE(std::ratio_equal_v<std::common_type_t<frequency<float, std::ratio<378, 52>>,
                                   frequency<float, std::ratio<525, 442>>>::period,
        std::ratio<21, 442>>);
}
