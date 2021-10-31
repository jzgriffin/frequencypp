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
