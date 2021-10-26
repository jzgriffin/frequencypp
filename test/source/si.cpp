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
#include <type_traits>

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

TEST_CASE("SI unit literal suffixes specify correct representations")
{
    using namespace ::frequencypp;

    // Integer
    REQUIRE(sizeof(decltype(1_nHz)::rep) >= sizeof(nanohertz::rep));
    REQUIRE(sizeof(decltype(1_uHz)::rep) >= sizeof(microhertz::rep));
    REQUIRE(sizeof(decltype(1_mHz)::rep) >= sizeof(millihertz::rep));
    REQUIRE(sizeof(decltype(1_Hz)::rep) >= sizeof(hertz::rep));
    REQUIRE(sizeof(decltype(1_KHz)::rep) >= sizeof(kilohertz::rep));
    REQUIRE(sizeof(decltype(1_MHz)::rep) >= sizeof(megahertz::rep));
    REQUIRE(sizeof(decltype(1_GHz)::rep) >= sizeof(gigahertz::rep));
    REQUIRE(sizeof(decltype(1_THz)::rep) >= sizeof(terahertz::rep));
    REQUIRE(sizeof(decltype(1_PHz)::rep) >= sizeof(petahertz::rep));

    // Floating point
    REQUIRE(std::is_floating_point_v<decltype(1.5_nHz)::rep>);
    REQUIRE(std::is_floating_point_v<decltype(1.5_uHz)::rep>);
    REQUIRE(std::is_floating_point_v<decltype(1.5_mHz)::rep>);
    REQUIRE(std::is_floating_point_v<decltype(1.5_Hz)::rep>);
    REQUIRE(std::is_floating_point_v<decltype(1.5_KHz)::rep>);
    REQUIRE(std::is_floating_point_v<decltype(1.5_MHz)::rep>);
    REQUIRE(std::is_floating_point_v<decltype(1.5_GHz)::rep>);
    REQUIRE(std::is_floating_point_v<decltype(1.5_THz)::rep>);
    REQUIRE(std::is_floating_point_v<decltype(1.5_PHz)::rep>);
}

TEST_CASE("SI unit literal suffixes specify correct periods")
{
    using namespace ::frequencypp;

    // Integer
    REQUIRE(std::ratio_equal_v<decltype(1_nHz)::period, std::nano>);
    REQUIRE(std::ratio_equal_v<decltype(1_uHz)::period, std::micro>);
    REQUIRE(std::ratio_equal_v<decltype(1_mHz)::period, std::milli>);
    REQUIRE(std::ratio_equal_v<decltype(1_Hz)::period, std::ratio<1>>);
    REQUIRE(std::ratio_equal_v<decltype(1_KHz)::period, std::kilo>);
    REQUIRE(std::ratio_equal_v<decltype(1_MHz)::period, std::mega>);
    REQUIRE(std::ratio_equal_v<decltype(1_GHz)::period, std::giga>);
    REQUIRE(std::ratio_equal_v<decltype(1_THz)::period, std::tera>);
    REQUIRE(std::ratio_equal_v<decltype(1_PHz)::period, std::peta>);

    // Floating point
    REQUIRE(std::ratio_equal_v<decltype(1.5_nHz)::period, std::nano>);
    REQUIRE(std::ratio_equal_v<decltype(1.5_uHz)::period, std::micro>);
    REQUIRE(std::ratio_equal_v<decltype(1.5_mHz)::period, std::milli>);
    REQUIRE(std::ratio_equal_v<decltype(1.5_Hz)::period, std::ratio<1>>);
    REQUIRE(std::ratio_equal_v<decltype(1.5_KHz)::period, std::kilo>);
    REQUIRE(std::ratio_equal_v<decltype(1.5_MHz)::period, std::mega>);
    REQUIRE(std::ratio_equal_v<decltype(1.5_GHz)::period, std::giga>);
    REQUIRE(std::ratio_equal_v<decltype(1.5_THz)::period, std::tera>);
    REQUIRE(std::ratio_equal_v<decltype(1.5_PHz)::period, std::peta>);
}

TEST_CASE("SI unit literal suffixes store count")
{
    using namespace ::frequencypp;

    // Integer
    REQUIRE((1_nHz).count() == 1);
    REQUIRE((1_uHz).count() == 1);
    REQUIRE((1_mHz).count() == 1);
    REQUIRE((1_Hz).count() == 1);
    REQUIRE((1_KHz).count() == 1);
    REQUIRE((1_MHz).count() == 1);
    REQUIRE((1_GHz).count() == 1);
    REQUIRE((1_THz).count() == 1);
    REQUIRE((1_PHz).count() == 1);

    // Floating point
    REQUIRE((1.5_nHz).count() == 1.5);
    REQUIRE((1.5_uHz).count() == 1.5);
    REQUIRE((1.5_mHz).count() == 1.5);
    REQUIRE((1.5_Hz).count() == 1.5);
    REQUIRE((1.5_KHz).count() == 1.5);
    REQUIRE((1.5_MHz).count() == 1.5);
    REQUIRE((1.5_GHz).count() == 1.5);
    REQUIRE((1.5_THz).count() == 1.5);
    REQUIRE((1.5_PHz).count() == 1.5);
}
