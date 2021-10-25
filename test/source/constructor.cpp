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
