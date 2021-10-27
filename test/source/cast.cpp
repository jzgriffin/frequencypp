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

TEST_CASE("frequency_cast casts count", "[cast]")
{
    using namespace ::frequencypp;

    // Same representation, different period
    REQUIRE(frequency_cast<frequency<std::int64_t>>(1000_mHz).count() == 1);
    REQUIRE(frequency_cast<frequency<std::int64_t, std::milli>>(1_Hz).count() == 1000);
    REQUIRE(frequency_cast<frequency<std::int64_t, std::nano>>(2_Hz).count() == 2000000000);
    REQUIRE(frequency_cast<frequency<double, std::mega>>(5.0_GHz).count() == 5000.0);
    REQUIRE(frequency_cast<frequency<double, std::peta>>(1250.0_THz).count() == 1.250);

    // Different representation, same period
    REQUIRE(frequency_cast<frequency<std::int64_t>>(1.0_Hz).count() == 1);
    REQUIRE(frequency_cast<frequency<float, std::tera>>(125_THz).count() == 125.0F);

    // Different represent<frequencyation and period
    REQUIRE(frequency_cast<frequency<std::int64_t, std::milli>>(1.0_Hz).count() == 1000);
    REQUIRE(frequency_cast<frequency<float, std::milli>>(1_Hz).count() == 1000.0F);
    REQUIRE(frequency_cast<frequency<float, std::kilo>>(125_Hz).count() == 0.125F);
}
