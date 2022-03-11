// Copyright 2021-2022 Jeremiah Griffin
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

template<>
struct frequencypp::frequency_values<double>
{
    static constexpr auto zero() noexcept -> double
    {
        return -1.0;
    }

    static constexpr auto min() noexcept -> double
    {
        return -2.0;
    }

    static constexpr auto max() noexcept -> double
    {
        return 2.0;
    }
};

TEST_CASE("special values are returned", "[constructor]")
{
    using namespace ::frequencypp;

    REQUIRE(frequency<int>::zero().count() == frequency_values<int>::zero());
    REQUIRE(frequency<int>::min().count() == frequency_values<int>::min());
    REQUIRE(frequency<int>::max().count() == frequency_values<int>::max());
    REQUIRE(frequency<int>::zero().count() == 0);
    REQUIRE(frequency<int>::min().count() == std::numeric_limits<int>::lowest());
    REQUIRE(frequency<int>::max().count() == std::numeric_limits<int>::max());

    REQUIRE(frequency<float>::zero().count() == frequency_values<float>::zero());
    REQUIRE(frequency<float>::min().count() == frequency_values<float>::min());
    REQUIRE(frequency<float>::max().count() == frequency_values<float>::max());
    REQUIRE(frequency<float>::zero().count() == 0.0F);
    REQUIRE(frequency<float>::min().count() == std::numeric_limits<float>::lowest());
    REQUIRE(frequency<float>::max().count() == std::numeric_limits<float>::max());

    // Tests the above specialization
    REQUIRE(frequency<double>::zero().count() == -1.0);
    REQUIRE(frequency<double>::min().count() == -2.0);
    REQUIRE(frequency<double>::max().count() == 2.0);
}
