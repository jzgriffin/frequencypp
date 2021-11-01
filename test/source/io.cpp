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

#include <sstream>

namespace {

auto take_string(std::ostringstream& os) -> std::string
{
    auto s = os.str();
    os.str({});
    return s;
}

} // namespace

TEST_CASE("operator<< inserts the correct unit suffix", "[io]")
{
    using namespace ::frequencypp;

    std::ostringstream os;
    auto take_string = [&os] { return ::take_string(os); };

    os << 1_nHz;
    REQUIRE(take_string() == "1nHz");

    os << 1_uHz;
    REQUIRE(take_string() == "1µHz");

    os << 1_mHz;
    REQUIRE(take_string() == "1mHz");

    os << 1_Hz;
    REQUIRE(take_string() == "1Hz");

    os << 1_KHz;
    REQUIRE(take_string() == "1KHz");

    os << 1_MHz;
    REQUIRE(take_string() == "1MHz");

    os << 1_GHz;
    REQUIRE(take_string() == "1GHz");

    os << 1_THz;
    REQUIRE(take_string() == "1THz");

    os << 1_PHz;
    REQUIRE(take_string() == "1PHz");

    os << frequency<int, std::ratio<2>>{1};
    REQUIRE(take_string() == "1[2]Hz");

    os << frequency<int, std::ratio<5, 2>>{1};
    REQUIRE(take_string() == "1[5/2]Hz");
}

TEST_CASE("operator<< respects stream flags", "[io]")
{
    using namespace ::frequencypp;

    std::ostringstream os;
    auto take_string = [&os] { return ::take_string(os); };

    os.flags(std::ios::showpos);
    os << 1_Hz;
    REQUIRE(take_string() == "+1Hz");

    os.flags(std::ios::hex | std::ios::uppercase);
    os << 10_mHz;
    REQUIRE(take_string() == "AmHz");
}

TEST_CASE("operator<< respects stream precision", "[io]")
{
    using namespace ::frequencypp;

    std::ostringstream os;
    auto take_string = [&os] { return ::take_string(os); };

    os.precision(2);
    os << 1.24_PHz;
    REQUIRE(take_string() == "1.2PHz");

    os.precision(3);
    os << 2.124_GHz;
    REQUIRE(take_string() == "2.12GHz");
}
