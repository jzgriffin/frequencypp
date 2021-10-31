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

// Arithmetic

// Addition

TEST_CASE("addition converts to the correct type", "[arithmetic]")
{
    using namespace ::frequencypp;

    // Same representation and period
    auto f1 = 15_Hz + 5_Hz;
    REQUIRE(std::is_same_v<hertz::rep, decltype(f1)::rep>);
    REQUIRE(std::ratio_equal_v<hertz::period, decltype(f1)::period>);
    auto f2 = 15.5_MHz + 4.5_MHz;
    REQUIRE(std::is_same_v<long double, decltype(f2)::rep>);
    REQUIRE(std::ratio_equal_v<megahertz::period, decltype(f2)::period>);

    // Different representation, same period
    auto f3 = 15_Hz + 5.0_Hz;
    REQUIRE(std::is_same_v<long double, decltype(f3)::rep>);
    REQUIRE(std::ratio_equal_v<hertz::period, decltype(f3)::period>);
    auto f4 = 15.5_MHz + 4_MHz;
    REQUIRE(std::is_same_v<long double, decltype(f4)::rep>);
    REQUIRE(std::ratio_equal_v<megahertz::period, decltype(f4)::period>);

    // Same representation, different period
    auto f5 = 15_Hz + 5_KHz;
    REQUIRE(std::is_same_v<hertz::rep, decltype(f5)::rep>);
    REQUIRE(std::ratio_equal_v<hertz::period, decltype(f5)::period>);
    auto f6 = 15.5_MHz + 4.5_GHz;
    REQUIRE(std::is_same_v<long double, decltype(f6)::rep>);
    REQUIRE(std::ratio_equal_v<megahertz::period, decltype(f6)::period>);

    // Different representation and period
    auto f7 = 15_Hz + 5.0_KHz;
    REQUIRE(std::is_same_v<long double, decltype(f7)::rep>);
    REQUIRE(std::ratio_equal_v<hertz::period, decltype(f7)::period>);
    auto f8 = 15.5_MHz + 4_GHz;
    REQUIRE(std::is_same_v<long double, decltype(f8)::rep>);
    REQUIRE(std::ratio_equal_v<megahertz::period, decltype(f8)::period>);
}

TEST_CASE("addition computes the correct tick count", "[arithmetic]")
{
    using namespace ::frequencypp;

    // Same representation and period
    REQUIRE(15_Hz + 5_Hz == 20_Hz);
    REQUIRE(15.5_MHz + 4.5_MHz == 20.0_MHz);

    // Different representation, same period
    REQUIRE(15_Hz + 5.0_Hz == 20.0_Hz);
    REQUIRE(15.5_MHz + 4_MHz == 19.5_MHz);

    // Same representation, different period
    REQUIRE(15_Hz + 5_KHz == 5015_Hz);
    REQUIRE(15.5_MHz + 4.5_GHz == 4.5155_GHz);

    // Different representation and period
    REQUIRE(15_Hz + 5.0_KHz == 5.015_KHz);
    REQUIRE(15.5_MHz + 4_GHz == 4.0155_GHz);
}

TEST_CASE("addition does not modify arguments", "[arithmetic]")
{
    using namespace ::frequencypp;

    auto f1 = 15_Hz;
    auto f2 = 5_Hz;
    auto f3 = f1 + f2;
    REQUIRE(f1 == 15_Hz);
    REQUIRE(f2 == 5_Hz);
    REQUIRE(f3 == 20_Hz);
}

// Subtraction

TEST_CASE("subtraction converts to the correct type", "[arithmetic]")
{
    using namespace ::frequencypp;

    // Same representation and period
    auto f1 = 15_Hz - 5_Hz;
    REQUIRE(std::is_same_v<hertz::rep, decltype(f1)::rep>);
    REQUIRE(std::ratio_equal_v<hertz::period, decltype(f1)::period>);
    auto f2 = 15.5_MHz - 4.5_MHz;
    REQUIRE(std::is_same_v<long double, decltype(f2)::rep>);
    REQUIRE(std::ratio_equal_v<megahertz::period, decltype(f2)::period>);

    // Different representation, same period
    auto f3 = 15_Hz - 5.0_Hz;
    REQUIRE(std::is_same_v<long double, decltype(f3)::rep>);
    REQUIRE(std::ratio_equal_v<hertz::period, decltype(f3)::period>);
    auto f4 = 15.5_MHz - 4_MHz;
    REQUIRE(std::is_same_v<long double, decltype(f4)::rep>);
    REQUIRE(std::ratio_equal_v<megahertz::period, decltype(f4)::period>);

    // Same representation, different period
    auto f5 = 15_Hz - 5_KHz;
    REQUIRE(std::is_same_v<hertz::rep, decltype(f5)::rep>);
    REQUIRE(std::ratio_equal_v<hertz::period, decltype(f5)::period>);
    auto f6 = 15.5_MHz - 4.5_GHz;
    REQUIRE(std::is_same_v<long double, decltype(f6)::rep>);
    REQUIRE(std::ratio_equal_v<megahertz::period, decltype(f6)::period>);

    // Different representation and period
    auto f7 = 15_Hz - 5.0_KHz;
    REQUIRE(std::is_same_v<long double, decltype(f7)::rep>);
    REQUIRE(std::ratio_equal_v<hertz::period, decltype(f7)::period>);
    auto f8 = 15.5_MHz - 4_GHz;
    REQUIRE(std::is_same_v<long double, decltype(f8)::rep>);
    REQUIRE(std::ratio_equal_v<megahertz::period, decltype(f8)::period>);
}

TEST_CASE("subtraction computes the correct tick count", "[arithmetic]")
{
    using namespace ::frequencypp;

    // Same representation and period
    REQUIRE(15_Hz - 5_Hz == 10_Hz);
    REQUIRE(15.5_MHz - 4.5_MHz == 11.0_MHz);

    // Different representation, same period
    REQUIRE(15_Hz - 5.0_Hz == 10.0_Hz);
    REQUIRE(15.5_MHz - 4_MHz == 11.5_MHz);

    // Same representation, different period
    REQUIRE(15_Hz - 5_KHz == -4985_Hz);
    REQUIRE(15.5_MHz - 4.5_GHz == -4.4845_GHz);

    // Different representation and period
    REQUIRE(15_Hz - 5.0_KHz == -4.985_KHz);
    REQUIRE(15.5_MHz - 4_GHz == -3.9845_GHz);
}

TEST_CASE("subtraction does not modify arguments", "[arithmetic]")
{
    using namespace ::frequencypp;

    auto f1 = 15_Hz;
    auto f2 = 5_Hz;
    auto f3 = f1 - f2;
    REQUIRE(f1 == 15_Hz);
    REQUIRE(f2 == 5_Hz);
    REQUIRE(f3 == 10_Hz);
}

// Multiplication

TEST_CASE("multiplication converts to the correct type", "[arithmetic]")
{
    using namespace ::frequencypp;

    // Same representation
    auto f1 = 15_Hz * 5;
    REQUIRE(std::is_same_v<hertz::rep, decltype(f1)::rep>);
    REQUIRE(std::ratio_equal_v<hertz::period, decltype(f1)::period>);
    auto f2 = 5 * 15_Hz;
    REQUIRE(std::is_same_v<hertz::rep, decltype(f2)::rep>);
    REQUIRE(std::ratio_equal_v<hertz::period, decltype(f2)::period>);
    auto f3 = 15.5_MHz * 4.5;
    REQUIRE(std::is_same_v<long double, decltype(f3)::rep>);
    REQUIRE(std::ratio_equal_v<megahertz::period, decltype(f3)::period>);
    auto f4 = 4.5 * 15.5_MHz;
    REQUIRE(std::is_same_v<long double, decltype(f4)::rep>);
    REQUIRE(std::ratio_equal_v<megahertz::period, decltype(f4)::period>);

    // Different representation
    auto f5 = 15_Hz * 2.5;
    REQUIRE(std::is_same_v<double, decltype(f5)::rep>);
    REQUIRE(std::ratio_equal_v<hertz::period, decltype(f5)::period>);
    auto f6 = 2.5F * 15_Hz;
    REQUIRE(std::is_same_v<float, decltype(f6)::rep>);
    REQUIRE(std::ratio_equal_v<hertz::period, decltype(f6)::period>);
    auto f7 = 15.5_MHz * 4;
    REQUIRE(std::is_same_v<long double, decltype(f7)::rep>);
    REQUIRE(std::ratio_equal_v<megahertz::period, decltype(f7)::period>);
    auto f8 = 4 * 15.5_MHz;
    REQUIRE(std::is_same_v<long double, decltype(f8)::rep>);
    REQUIRE(std::ratio_equal_v<megahertz::period, decltype(f8)::period>);
}

TEST_CASE("multiplication computes the correct tick count", "[arithmetic]")
{
    using namespace ::frequencypp;

    // Same representation
    REQUIRE(15_Hz * 5 == 75_Hz);

    // Different representation
    REQUIRE((15_Hz * 2.5).count() == Approx(37.5));
}

TEST_CASE("multiplication is commutative", "[arithmetic]")
{
    using namespace ::frequencypp;

    REQUIRE(15_Hz * 5 == 5 * 15_Hz);
}

TEST_CASE("multiplication is associative", "[arithmetic]")
{
    using namespace ::frequencypp;

    REQUIRE((2_Hz * 3) * 4 == 2_Hz * (3 * 4));
}

TEST_CASE("multiplication is distributive", "[arithmetic]")
{
    using namespace ::frequencypp;

    REQUIRE(2.5 * (1_Hz + 3_Hz) == 2.5 * 1_Hz + 2.5 * 3_Hz);
}

TEST_CASE("multiplication implements the identity property", "[arithnetic]")
{
    using namespace ::frequencypp;

    REQUIRE(4_Hz * 1 == 4_Hz);
}

TEST_CASE("multiplication implements the zero property", "[arithmetic]")
{
    using namespace ::frequencypp;

    REQUIRE(2000_Hz * 0 == 0_Hz);
}

TEST_CASE("multiplication implements the negative property", "[arithmetic]")
{
    using namespace ::frequencypp;

    REQUIRE(-1 * 1234_Hz == -1234_Hz);
    REQUIRE(-1 * -1234_Hz == 1234_Hz);
}

TEST_CASE("multiplication does not modify arguments", "[arithmetic]")
{
    using namespace ::frequencypp;

    auto f1 = 15_Hz;
    auto x = 5;
    auto f2 = f1 * x;
    REQUIRE(f1 == 15_Hz);
    REQUIRE(x == 5);
    REQUIRE(f2 == 75_Hz);
}

// Division

TEST_CASE("division converts to the correct type", "[arithmetic]")
{
    using namespace ::frequencypp;

    // Same representation
    auto f1 = 15_Hz / 5;
    REQUIRE(std::is_same_v<hertz::rep, decltype(f1)::rep>);
    REQUIRE(std::ratio_equal_v<hertz::period, decltype(f1)::period>);
    auto f2 = 15_Hz / 5_Hz;
    REQUIRE(std::is_same_v<hertz::rep, decltype(f2)>);
    auto f3 = 15.5_MHz / 4.5;
    REQUIRE(std::is_same_v<long double, decltype(f3)::rep>);
    REQUIRE(std::ratio_equal_v<megahertz::period, decltype(f3)::period>);
    auto f4 = 15.5_MHz / 4.5_MHz;
    REQUIRE(std::is_same_v<long double, decltype(f4)>);

    // Different representation
    auto f5 = 15_Hz / 2.5;
    REQUIRE(std::is_same_v<double, decltype(f5)::rep>);
    REQUIRE(std::ratio_equal_v<hertz::period, decltype(f5)::period>);
    auto f6 = 15_Hz / 2.5_Hz;
    REQUIRE(std::is_same_v<long double, decltype(f6)>);
    auto f7 = 15.5_MHz / 4;
    REQUIRE(std::is_same_v<long double, decltype(f7)::rep>);
    REQUIRE(std::ratio_equal_v<megahertz::period, decltype(f7)::period>);
    auto f8 = 15.5_MHz / 4_MHz;
    REQUIRE(std::is_same_v<long double, decltype(f8)>);
}

TEST_CASE("division computes the correct tick count", "[arithmetic]")
{
    using namespace ::frequencypp;

    // Same representation
    REQUIRE(15_Hz / 5 == 3_Hz);
    REQUIRE(15_Hz / 3_Hz == 5);
    REQUIRE((10_MHz / 2.5).count() == Approx(4.0));
    REQUIRE(10_MHz / 4.0_MHz == Approx(2.5));

    // Different representation
    REQUIRE((15_Hz / 2.5).count() == Approx(6.0));
    REQUIRE(15_Hz / 7.5_Hz == Approx(2.0));
    REQUIRE((15.0_Hz / 2).count() == Approx(7.5));
    REQUIRE(15.0_Hz / 6_Hz == Approx(2.5));
}

TEST_CASE("division implements the identity property", "[arithnetic]")
{
    using namespace ::frequencypp;

    REQUIRE(4_Hz / 1 == 4_Hz);

    REQUIRE(4_Hz / 1_Hz == 4);
}

TEST_CASE("division implements the negative property", "[arithmetic]")
{
    using namespace ::frequencypp;

    REQUIRE(1234_Hz / -1 == -1234_Hz);
    REQUIRE(-1234_Hz / -1 == 1234_Hz);

    REQUIRE(50_MHz / -1_MHz == -50);
    REQUIRE(-50_MHz / -1_MHz == 50);
}

TEST_CASE("division does not modify arguments", "[arithmetic]")
{
    using namespace ::frequencypp;

    auto f1 = 15_Hz;
    auto x = 5;
    auto f2 = f1 / x;
    REQUIRE(f1 == 15_Hz);
    REQUIRE(x == 5);
    REQUIRE(f2 == 3_Hz);

    auto y = f1 / f2;
    REQUIRE(f1 == 15_Hz);
    REQUIRE(f2 == 3_Hz);
    REQUIRE(y == 5);
}

// Modulo

TEST_CASE("modulo converts to the correct type", "[arithmetic]")
{
    using namespace ::frequencypp;

    auto f1 = 15_Hz % 5;
    REQUIRE(std::is_same_v<hertz::rep, decltype(f1)::rep>);
    REQUIRE(std::ratio_equal_v<hertz::period, decltype(f1)::period>);
    auto f2 = 15_Hz % 5_Hz;
    REQUIRE(std::is_same_v<hertz::rep, decltype(f2)>);
    auto f3 = 15_MHz % 5_Hz;
    REQUIRE(std::is_same_v<megahertz::rep, decltype(f3)>);
}

TEST_CASE("modulo computes the correct tick count", "[arithmetic]")
{
    using namespace ::frequencypp;

    REQUIRE(15_Hz % 4 == 3_Hz);
    REQUIRE(15_Hz % 7_Hz == 1);
}

TEST_CASE("modulo implements the identity property", "[arithnetic]")
{
    using namespace ::frequencypp;

    REQUIRE(4_Hz % 1 == 0_Hz);

    REQUIRE(4_Hz % 1_Hz == 0);
}

TEST_CASE("modulo does not modify arguments", "[arithmetic]")
{
    using namespace ::frequencypp;

    auto f1 = 15_Hz;
    auto x = 4;
    auto f2 = f1 % x;
    REQUIRE(f1 == 15_Hz);
    REQUIRE(x == 4);
    REQUIRE(f2 == 3_Hz);

    auto y = f1 % f2;
    REQUIRE(f1 == 15_Hz);
    REQUIRE(f2 == 3_Hz);
    REQUIRE(y == 0);
}
