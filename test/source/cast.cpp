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

TEST_CASE("frequency_cast casts count", "[cast]")
{
    using namespace ::frequencypp;

    // Same representation, different period
    REQUIRE(frequency_cast<frequency<std::int64_t>>(0_mHz).count() == 0);
    REQUIRE(frequency_cast<frequency<std::int64_t>>(1000_mHz).count() == 1);
    REQUIRE(frequency_cast<frequency<std::int64_t, std::milli>>(1_Hz).count() == 1000);
    REQUIRE(frequency_cast<frequency<std::int64_t, std::nano>>(2_Hz).count() == 2000000000);
    REQUIRE(frequency_cast<frequency<double, std::mega>>(5.0_GHz).count() == 5000.0);
    REQUIRE(frequency_cast<frequency<double, std::peta>>(1250.0_THz).count() == 1.250);

    // Different representation, same period
    REQUIRE(frequency_cast<frequency<std::int64_t>>(0.0_Hz).count() == 0);
    REQUIRE(frequency_cast<frequency<std::int64_t>>(1.0_Hz).count() == 1);
    REQUIRE(frequency_cast<frequency<float, std::tera>>(125_THz).count() == 125.0F);

    // Different represent<frequencyation and period
    REQUIRE(frequency_cast<frequency<std::int64_t, std::milli>>(0.0_Hz).count() == 0);
    REQUIRE(frequency_cast<frequency<std::int64_t, std::milli>>(1.0_Hz).count() == 1000);
    REQUIRE(frequency_cast<frequency<float, std::milli>>(1_Hz).count() == 1000.0F);
    REQUIRE(frequency_cast<frequency<float, std::kilo>>(125_Hz).count() == 0.125F);
}

TEST_CASE("frequency_cast from duration casts count", "[cast]")
{
    using namespace ::frequencypp;
    using namespace std::chrono;

    // Same representation
    REQUIRE(frequency_cast<hertz>(0ms) == 0_Hz);
    REQUIRE(frequency_cast<hertz>(1000ms) == 1_Hz);
    REQUIRE(frequency_cast<hertz>(16ms) == 62_Hz);
    REQUIRE(frequency_cast<kilohertz>(50us) == 20_KHz);
    REQUIRE(frequency_cast<frequency<long double>>(1000.0ms).count() == Approx(1.0));
    REQUIRE(frequency_cast<frequency<long double>>(16.6667ms).count() == Approx(60.0));
    REQUIRE(frequency_cast<frequency<long double, std::kilo>>(50.0us).count() == Approx(20.0));

    // Different representation
    REQUIRE(frequency_cast<hertz>(0.0ms) == 0_Hz);
    REQUIRE(frequency_cast<hertz>(1000.0ms) == 1_Hz);
    REQUIRE(frequency_cast<hertz>(16.0ms) == 62_Hz);
    REQUIRE(frequency_cast<kilohertz>(50.0us) == 20_KHz);
    REQUIRE(frequency_cast<frequency<long double>>(1000ms).count() == Approx(1.0));
    REQUIRE(frequency_cast<frequency<long double>>(16ms).count() == Approx(62.5));
    REQUIRE(frequency_cast<frequency<long double, std::kilo>>(50us).count() == Approx(20.0));
}

TEST_CASE("duration_cast casts count", "[cast]")
{
    using namespace ::frequencypp;
    using namespace std::chrono;

    // Same representation
    REQUIRE(duration_cast<milliseconds>(0_Hz) == 0ms);
    REQUIRE(duration_cast<milliseconds>(1_Hz) == 1000ms);
    REQUIRE(duration_cast<milliseconds>(60_Hz) == 16ms);
    REQUIRE(duration_cast<microseconds>(20_KHz) == 50us);
    REQUIRE(duration_cast<duration<long double, std::milli>>(1.0_Hz).count() == Approx(1000.0));
    REQUIRE(duration_cast<duration<long double, std::milli>>(60.0_Hz).count() == Approx(16.6667));
    REQUIRE(duration_cast<duration<long double, std::micro>>(20.0_KHz).count() == Approx(50.0));

    // Different representation
    REQUIRE(duration_cast<milliseconds>(0.0_Hz) == 0ms);
    REQUIRE(duration_cast<milliseconds>(1.0_Hz) == 1000ms);
    REQUIRE(duration_cast<milliseconds>(60.0_Hz) == 16ms);
    REQUIRE(duration_cast<microseconds>(20.0_KHz) == 50us);
    REQUIRE(duration_cast<duration<long double, std::milli>>(1_Hz).count() == Approx(1000.0));
    REQUIRE(duration_cast<duration<long double, std::milli>>(60_Hz).count() == Approx(16.6667));
    REQUIRE(duration_cast<duration<long double, std::micro>>(20_KHz).count() == Approx(50.0));
}
