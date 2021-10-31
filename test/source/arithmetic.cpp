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

TEST_CASE("reinforcement returns the same frequency", "[arithmetic]")
{
    using namespace ::frequencypp;

    REQUIRE(+frequency<int>{} == frequency<int>{});
    REQUIRE(+frequency<float>{} == frequency<float>{});

    REQUIRE(+(-1_Hz) == -1_Hz);
    REQUIRE(+(1_Hz) == 1_Hz);

    REQUIRE(+(-1.5_Hz) == -1.5_Hz);
    REQUIRE(+(1.5_Hz) == 1.5_Hz);
}

TEST_CASE("negation returns the opposite frequency", "[arithmetic]")
{
    using namespace ::frequencypp;

    REQUIRE(-(-1_Hz) == 1_Hz);
    REQUIRE(-(1_Hz) == -1_Hz);

    REQUIRE(-(-1.5_Hz) == 1.5_Hz);
    REQUIRE(-(1.5_Hz) == -1.5_Hz);
}

TEST_CASE("increment changes tick count", "[arithmetic]")
{
    using namespace ::frequencypp;

    auto f1 = frequency<int>{-1};
    REQUIRE((f1++).count() == -1);
    REQUIRE(f1.count() == 0);
    REQUIRE((++f1).count() == 1);
    REQUIRE(f1.count() == 1);

    auto f2 = frequency<float>{-0.5F};
    REQUIRE((f2++).count() == -0.5F);
    REQUIRE(f2.count() == 0.5F);
    REQUIRE((++f2).count() == 1.5F);
    REQUIRE(f2.count() == 1.5F);
}

TEST_CASE("decrement changes tick count", "[arithmetic]")
{
    using namespace ::frequencypp;

    auto f1 = frequency<int>{1};
    REQUIRE((f1--).count() == 1);
    REQUIRE(f1.count() == 0);
    REQUIRE((--f1).count() == -1);
    REQUIRE(f1.count() == -1);

    auto f2 = frequency<float>{1.5F};
    REQUIRE((f2--).count() == 1.5F);
    REQUIRE(f2.count() == 0.5F);
    REQUIRE((--f2).count() == -0.5F);
    REQUIRE(f2.count() == -0.5F);
}

// Compound assignment

TEST_CASE("compound addition changes tick count", "[arithmetic]")
{
    using namespace ::frequencypp;

    auto f1 = -1_Hz;
    REQUIRE((f1 += 1_Hz).count() == 0);
    REQUIRE((f1 += 4_Hz).count() == 4);
    REQUIRE((f1 += 2_KHz).count() == 2004);

    auto f2 = -1.5_uHz;
    REQUIRE((f2 += 1.0_uHz).count() == Approx(-0.5));
    REQUIRE((f2 += 4.75_uHz).count() == Approx(4.25));
    REQUIRE((f2 += 2.0_mHz).count() == Approx(2004.25));
}

TEST_CASE("compound subtraction changes tick count", "[arithmetic]")
{
    using namespace ::frequencypp;

    auto f1 = 1_Hz;
    REQUIRE((f1 -= 1_Hz).count() == 0);
    REQUIRE((f1 -= 4_Hz).count() == -4);
    REQUIRE((f1 -= 2_KHz).count() == -2004);

    auto f2 = 1.5_uHz;
    REQUIRE((f2 -= 1.0_uHz).count() == Approx(0.5));
    REQUIRE((f2 -= 4.75_uHz).count() == Approx(-4.25));
    REQUIRE((f2 -= 2.0_mHz).count() == Approx(-2004.25));
}

TEST_CASE("compound multiplication changes tick count", "[arithmetic]")
{
    using namespace ::frequencypp;

    auto f1 = 1_Hz;
    REQUIRE((f1 *= -1).count() == -1);
    REQUIRE((f1 *= -4).count() == 4);
    REQUIRE((f1 *= 2).count() == 8);

    auto f2 = 1.5_uHz;
    REQUIRE((f2 *= -1.0).count() == Approx(-1.5));
    REQUIRE((f2 *= -4.75).count() == Approx(7.125));
    REQUIRE((f2 *= 2.0).count() == Approx(14.25));
}

TEST_CASE("compound division changes tick count", "[arithmetic]")
{
    using namespace ::frequencypp;

    auto f1 = 15_Hz;
    REQUIRE((f1 /= -1).count() == -15);
    REQUIRE((f1 /= -4).count() == 3);
    REQUIRE((f1 /= 2).count() == 1);

    auto f2 = 1.5_uHz;
    REQUIRE((f2 /= -1.0).count() == Approx(-1.5));
    REQUIRE((f2 /= -3.0).count() == Approx(0.5));
    REQUIRE((f2 /= 2.5).count() == Approx(0.2));
}

TEST_CASE("compound modulo changes tick count", "[arithmetic]")
{
    using namespace ::frequencypp;

    auto f1 = 15_Hz;
    REQUIRE((f1 %= 4).count() == 3);
    REQUIRE((f1 %= 2).count() == 1);

    auto f2 = 2500_KHz;
    REQUIRE((f2 %= 2_MHz).count() == 500);

    // Should not compile due to operator% being undefined for floating-point numbers:
    // auto f3 = 1.5_uHz;
    // f3 %= 0.5;
}
