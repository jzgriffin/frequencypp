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

TEST_CASE("default construct default-constructs count", "[constructor]")
{
    using namespace ::frequencypp;

    REQUIRE(frequency<int>{}.count() == int{});
    REQUIRE(frequency<float>{}.count() == float{});
}

TEST_CASE("copy construct copies count", "[constructor]")
{
    using namespace ::frequencypp;

    auto f1 = frequency<int>{32};
    REQUIRE(frequency<int>{f1}.count() == f1.count());

    auto f2 = frequency<float>{-16.25F};
    REQUIRE(frequency<float>{f2}.count() == f2.count());
}

TEST_CASE("copy assign copies count", "[constructor]")
{
    using namespace ::frequencypp;

    auto f1 = frequency<int>{32};
    auto f1_copy = frequency<int>{};
    f1_copy = f1;
    REQUIRE(f1_copy.count() == f1.count());

    auto f2 = frequency<float>{-16.25F};
    auto f2_copy = frequency<float>{};
    f2_copy = f2;
    REQUIRE(f2_copy.count() == f2.count());
}

TEST_CASE("tick construct stores count", "[constructor]")
{
    using namespace ::frequencypp;

    // int from int
    REQUIRE(frequency<int>{-1}.count() == -1);
    REQUIRE(frequency<int>{1}.count() == 1);

    // float from float
    REQUIRE(frequency<float>{-1.5F}.count() == -1.5F);
    REQUIRE(frequency<float>{0.5F}.count() == 0.5F);

    // int from float
    // Should not compile due to truncation:
    // frequency<int>{-1.5F};

    // float from int
    REQUIRE(frequency<float>{1}.count() == 1.0F);
    REQUIRE(frequency<float>{-1}.count() == -1.0F);

    // double from float
    REQUIRE(frequency<double>{-1.5F}.count() == -1.5F);
    REQUIRE(frequency<double>{0.5F}.count() == 0.5);

    // float from double
    REQUIRE(frequency<float>{0.5}.count() == 0.5F);
}

TEST_CASE("cast construct casts count", "[constructor][cast]")
{
    using namespace ::frequencypp;

    // Should not compile due to truncation:
    // REQUIRE(frequency<int>{1000_mHz}.count() == 1);
    // REQUIRE(frequency<int, std::milli>{1.0_Hz}.count() == 1000);
    // REQUIRE(frequency<int>{1.0_Hz}.count() == 1);

    // Same representation, different period
    REQUIRE(frequency<std::int64_t, std::milli>{1_Hz}.count() == 1000);
    REQUIRE(frequency<std::int64_t, std::nano>{2_Hz}.count() == 2000000000);
    REQUIRE(frequency<long double, std::mega>{5.0_GHz}.count() == 5000.0);
    REQUIRE(frequency<long double, std::peta>{1250.0_THz}.count() == 1.250);

    // Different representation, same period
    REQUIRE(frequency<float, std::tera>{125_THz}.count() == 125.0F);

    // Different representation and period
    REQUIRE(frequency<float, std::milli>{1_Hz}.count() == 1000.0F);
    REQUIRE(frequency<float, std::kilo>{125_Hz}.count() == 0.125F);
}
