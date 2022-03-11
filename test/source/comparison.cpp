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

TEST_CASE("equality comparison models equality", "[comparison]")
{
    using namespace ::frequencypp;

    // Same representation and period
    REQUIRE(1_nHz == 1_nHz);
    REQUIRE(!(1_nHz == 2_nHz));
    REQUIRE(1_uHz == 1_uHz);
    REQUIRE(!(1_uHz == 2_uHz));
    REQUIRE(1_mHz == 1_mHz);
    REQUIRE(!(1_mHz == 2_mHz));
    REQUIRE(1_Hz == 1_Hz);
    REQUIRE(!(1_Hz == 2_Hz));
    REQUIRE(1_KHz == 1_KHz);
    REQUIRE(!(1_KHz == 2_KHz));
    REQUIRE(1_MHz == 1_MHz);
    REQUIRE(!(1_MHz == 2_MHz));
    REQUIRE(1_GHz == 1_GHz);
    REQUIRE(!(1_GHz == 2_GHz));
    REQUIRE(1_THz == 1_THz);
    REQUIRE(!(1_THz == 2_THz));
    REQUIRE(1_PHz == 1_PHz);
    REQUIRE(!(1_PHz == 2_PHz));

    // Different representation, same period
    REQUIRE(1.0_nHz == 1_nHz);
    REQUIRE(!(1.0_nHz == 2_nHz));
    REQUIRE(1.0_uHz == 1_uHz);
    REQUIRE(!(1.0_uHz == 2_uHz));
    REQUIRE(1.0_mHz == 1_mHz);
    REQUIRE(!(1.0_mHz == 2_mHz));
    REQUIRE(1.0_Hz == 1_Hz);
    REQUIRE(!(1.0_Hz == 2_Hz));
    REQUIRE(1.0_KHz == 1_KHz);
    REQUIRE(!(1.0_KHz == 2_KHz));
    REQUIRE(1.0_MHz == 1_MHz);
    REQUIRE(!(1.0_MHz == 2_MHz));
    REQUIRE(1.0_GHz == 1_GHz);
    REQUIRE(!(1.0_GHz == 2_GHz));
    REQUIRE(1.0_THz == 1_THz);
    REQUIRE(!(1.0_THz == 2_THz));
    REQUIRE(1.0_PHz == 1_PHz);
    REQUIRE(!(1.0_PHz == 2_PHz));

    // Same representation, different period
    REQUIRE(1250.0_nHz == 1.250_uHz);
    REQUIRE(!(1250.0_nHz == 1_uHz));
    REQUIRE(1250.0_uHz == 1.250_mHz);
    REQUIRE(!(1250.0_uHz == 1_mHz));
    REQUIRE(1250.0_mHz == 1.250_Hz);
    REQUIRE(!(1250.0_mHz == 1_Hz));
    REQUIRE(1250.0_Hz == 1.250_KHz);
    REQUIRE(!(1250.0_Hz == 1_KHz));
    REQUIRE(1250.0_KHz == 1.250_MHz);
    REQUIRE(!(1250.0_KHz == 1_MHz));
    REQUIRE(1250.0_MHz == 1.250_GHz);
    REQUIRE(!(1250.0_MHz == 1_GHz));
    REQUIRE(1250.0_GHz == 1.250_THz);
    REQUIRE(!(1250.0_GHz == 1_THz));
    REQUIRE(1250.0_THz == 1.250_PHz);
    REQUIRE(!(1250.0_THz == 1_PHz));
    REQUIRE(1250.0_PHz == 1250000.0_THz);
    REQUIRE(!(1250.0_PHz == 1000000.0_THz));

    // Different representation and period
    REQUIRE(1250_nHz == 1.250_uHz);
    REQUIRE(!(1250_nHz == 1_uHz));
    REQUIRE(1250_uHz == 1.250_mHz);
    REQUIRE(!(1250_uHz == 1_mHz));
    REQUIRE(1250_mHz == 1.250_Hz);
    REQUIRE(!(1250_mHz == 1_Hz));
    REQUIRE(1250_Hz == 1.250_KHz);
    REQUIRE(!(1250_Hz == 1_KHz));
    REQUIRE(1250_KHz == 1.250_MHz);
    REQUIRE(!(1250_KHz == 1_MHz));
    REQUIRE(1250_MHz == 1.250_GHz);
    REQUIRE(!(1250_MHz == 1_GHz));
    REQUIRE(1250_GHz == 1.250_THz);
    REQUIRE(!(1250_GHz == 1_THz));
    REQUIRE(1250_THz == 1.250_PHz);
    REQUIRE(!(1250_THz == 1_PHz));
    REQUIRE(1250_PHz == 1250000.0_THz);
    REQUIRE(!(1250_PHz == 1000000.0_THz));
}

TEST_CASE("inequality comparison models inequality", "[comparison]")
{
    using namespace ::frequencypp;

    // Same representation and period
    REQUIRE(!(1_nHz != 1_nHz));
    REQUIRE(1_nHz != 2_nHz);
    REQUIRE(!(1_uHz != 1_uHz));
    REQUIRE(1_uHz != 2_uHz);
    REQUIRE(!(1_mHz != 1_mHz));
    REQUIRE(1_mHz != 2_mHz);
    REQUIRE(!(1_Hz != 1_Hz));
    REQUIRE(1_Hz != 2_Hz);
    REQUIRE(!(1_KHz != 1_KHz));
    REQUIRE(1_KHz != 2_KHz);
    REQUIRE(!(1_MHz != 1_MHz));
    REQUIRE(1_MHz != 2_MHz);
    REQUIRE(!(1_GHz != 1_GHz));
    REQUIRE(1_GHz != 2_GHz);
    REQUIRE(!(1_THz != 1_THz));
    REQUIRE(1_THz != 2_THz);
    REQUIRE(!(1_PHz != 1_PHz));
    REQUIRE(1_PHz != 2_PHz);

    // Different representation, same period
    REQUIRE(!(1.0_nHz != 1_nHz));
    REQUIRE(1.0_nHz != 2_nHz);
    REQUIRE(!(1.0_uHz != 1_uHz));
    REQUIRE(1.0_uHz != 2_uHz);
    REQUIRE(!(1.0_mHz != 1_mHz));
    REQUIRE(1.0_mHz != 2_mHz);
    REQUIRE(!(1.0_Hz != 1_Hz));
    REQUIRE(1.0_Hz != 2_Hz);
    REQUIRE(!(1.0_KHz != 1_KHz));
    REQUIRE(1.0_KHz != 2_KHz);
    REQUIRE(!(1.0_MHz != 1_MHz));
    REQUIRE(1.0_MHz != 2_MHz);
    REQUIRE(!(1.0_GHz != 1_GHz));
    REQUIRE(1.0_GHz != 2_GHz);
    REQUIRE(!(1.0_THz != 1_THz));
    REQUIRE(1.0_THz != 2_THz);
    REQUIRE(!(1.0_PHz != 1_PHz));
    REQUIRE(1.0_PHz != 2_PHz);

    // Same representation, different period
    REQUIRE(!(1250.0_nHz != 1.250_uHz));
    REQUIRE(1250.0_nHz != 1_uHz);
    REQUIRE(!(1250.0_uHz != 1.250_mHz));
    REQUIRE(1250.0_uHz != 1_mHz);
    REQUIRE(1250.0_mHz == 1.250_Hz);
    REQUIRE(!(1250.0_mHz == 1_Hz));
    REQUIRE(!(1250.0_Hz != 1.250_KHz));
    REQUIRE(1250.0_Hz != 1_KHz);
    REQUIRE(!(1250.0_KHz != 1.250_MHz));
    REQUIRE(1250.0_KHz != 1_MHz);
    REQUIRE(!(1250.0_MHz != 1.250_GHz));
    REQUIRE(1250.0_MHz != 1_GHz);
    REQUIRE(!(1250.0_GHz != 1.250_THz));
    REQUIRE(1250.0_GHz != 1_THz);
    REQUIRE(!(1250.0_THz != 1.250_PHz));
    REQUIRE(1250.0_THz != 1_PHz);
    REQUIRE(!(1250.0_PHz != 1250000.0_THz));
    REQUIRE(1250.0_PHz != 1000000.0_THz);

    // Different representation and period
    REQUIRE(!(1250_nHz != 1.250_uHz));
    REQUIRE(1250_nHz != 1.0_uHz);
    REQUIRE(!(1250_uHz != 1.250_mHz));
    REQUIRE(1250_uHz != 1.0_mHz);
    REQUIRE(!(1250_mHz != 1.250_Hz));
    REQUIRE(1250_mHz != 1.0_Hz);
    REQUIRE(!(1250_Hz != 1.250_KHz));
    REQUIRE(1250_Hz != 1.0_KHz);
    REQUIRE(!(1250_KHz != 1.250_MHz));
    REQUIRE(1250_KHz != 1.0_MHz);
    REQUIRE(!(1250_MHz != 1.250_GHz));
    REQUIRE(1250_MHz != 1.0_GHz);
    REQUIRE(!(1250_GHz != 1.250_THz));
    REQUIRE(1250_GHz != 1.0_THz);
    REQUIRE(!(1250_THz != 1.250_PHz));
    REQUIRE(1250_THz != 1.0_PHz);
    REQUIRE(!(1250_PHz != 1250000.0_THz));
    REQUIRE(1250_PHz != 1000000.0_THz);
}

TEST_CASE("less-than comparison models less-than", "[comparison]")
{
    using namespace ::frequencypp;

    REQUIRE(1_nHz < 1_uHz);
    REQUIRE(1_uHz < 1_mHz);
    REQUIRE(1_mHz < 1_Hz);
    REQUIRE(1_Hz < 1_KHz);
    REQUIRE(1_KHz < 1_MHz);
    REQUIRE(1_MHz < 1_GHz);
    REQUIRE(1_GHz < 1_THz);
    REQUIRE(1_THz < 1_PHz);
    REQUIRE(1_nHz < 1.5_uHz);
    REQUIRE(1_uHz < 1.5_mHz);
    REQUIRE(1_mHz < 1.5_Hz);
    REQUIRE(1_Hz < 1.5_KHz);
    REQUIRE(1_KHz < 1.5_MHz);
    REQUIRE(1_MHz < 1.5_GHz);
    REQUIRE(1_GHz < 1.5_THz);
    REQUIRE(1_THz < 1.5_PHz);

    REQUIRE(!(1_PHz < 1_THz));
    REQUIRE(!(1_THz < 1_GHz));
    REQUIRE(!(1_GHz < 1_MHz));
    REQUIRE(!(1_MHz < 1_KHz));
    REQUIRE(!(1_KHz < 1_Hz));
    REQUIRE(!(1_Hz < 1_mHz));
    REQUIRE(!(1_mHz < 1_uHz));
    REQUIRE(!(1_uHz < 1_nHz));

    REQUIRE(!(1_Hz < 1_Hz));

    REQUIRE(1_PHz < 2000.0_THz);
}

TEST_CASE("less-than-or-equal-to comparison models less-than-or-equal-to", "[comparison]")
{
    using namespace ::frequencypp;

    REQUIRE(1_nHz <= 1_uHz);
    REQUIRE(1_uHz <= 1_mHz);
    REQUIRE(1_mHz <= 1_Hz);
    REQUIRE(1_Hz <= 1_KHz);
    REQUIRE(1_KHz <= 1_MHz);
    REQUIRE(1_MHz <= 1_GHz);
    REQUIRE(1_GHz <= 1_THz);
    REQUIRE(1_THz <= 1_PHz);
    REQUIRE(1_nHz <= 1.5_uHz);
    REQUIRE(1_uHz <= 1.5_mHz);
    REQUIRE(1_mHz <= 1.5_Hz);
    REQUIRE(1_Hz <= 1.5_KHz);
    REQUIRE(1_KHz <= 1.5_MHz);
    REQUIRE(1_MHz <= 1.5_GHz);
    REQUIRE(1_GHz <= 1.5_THz);
    REQUIRE(1_THz <= 1.5_PHz);

    REQUIRE(!(1_PHz <= 1_THz));
    REQUIRE(!(1_THz <= 1_GHz));
    REQUIRE(!(1_GHz <= 1_MHz));
    REQUIRE(!(1_MHz <= 1_KHz));
    REQUIRE(!(1_KHz <= 1_Hz));
    REQUIRE(!(1_Hz <= 1_mHz));
    REQUIRE(!(1_mHz <= 1_uHz));
    REQUIRE(!(1_uHz <= 1_nHz));

    REQUIRE(1_Hz <= 1_Hz);

    REQUIRE(1_PHz <= 2000.0_THz);
    REQUIRE(1_mHz <= 1000.0_uHz);
}

TEST_CASE("greater-than comparison models greater-than", "[comparison]")
{
    using namespace ::frequencypp;

    REQUIRE(1_PHz > 1_THz);
    REQUIRE(1_THz > 1_GHz);
    REQUIRE(1_GHz > 1_MHz);
    REQUIRE(1_MHz > 1_KHz);
    REQUIRE(1_KHz > 1_Hz);
    REQUIRE(1_Hz > 1_mHz);
    REQUIRE(1_mHz > 1_uHz);
    REQUIRE(1_uHz > 1_nHz);
    REQUIRE(1_PHz > 1.5_THz);
    REQUIRE(1_THz > 1.5_GHz);
    REQUIRE(1_GHz > 1.5_MHz);
    REQUIRE(1_MHz > 1.5_KHz);
    REQUIRE(1_KHz > 1.5_Hz);
    REQUIRE(1_Hz > 1.5_mHz);
    REQUIRE(1_mHz > 1.5_uHz);
    REQUIRE(1_uHz > 1.5_nHz);

    REQUIRE(!(1_nHz > 1_uHz));
    REQUIRE(!(1_uHz > 1_mHz));
    REQUIRE(!(1_mHz > 1_Hz));
    REQUIRE(!(1_Hz > 1_KHz));
    REQUIRE(!(1_KHz > 1_MHz));
    REQUIRE(!(1_MHz > 1_GHz));
    REQUIRE(!(1_GHz > 1_THz));
    REQUIRE(!(1_THz > 1_PHz));

    REQUIRE(!(1_Hz > 1_Hz));

    REQUIRE(2000.0_THz > 1_PHz);
}

TEST_CASE("greater-than-or-equal-to comparison models greater-than-or-equal-to", "[comparison]")
{
    using namespace ::frequencypp;

    REQUIRE(1_PHz >= 1_THz);
    REQUIRE(1_THz >= 1_GHz);
    REQUIRE(1_GHz >= 1_MHz);
    REQUIRE(1_MHz >= 1_KHz);
    REQUIRE(1_KHz >= 1_Hz);
    REQUIRE(1_Hz >= 1_mHz);
    REQUIRE(1_mHz >= 1_uHz);
    REQUIRE(1_uHz >= 1_nHz);
    REQUIRE(1_PHz >= 1.5_THz);
    REQUIRE(1_THz >= 1.5_GHz);
    REQUIRE(1_GHz >= 1.5_MHz);
    REQUIRE(1_MHz >= 1.5_KHz);
    REQUIRE(1_KHz >= 1.5_Hz);
    REQUIRE(1_Hz >= 1.5_mHz);
    REQUIRE(1_mHz >= 1.5_uHz);
    REQUIRE(1_uHz >= 1.5_nHz);

    REQUIRE(!(1_nHz >= 1_uHz));
    REQUIRE(!(1_uHz >= 1_mHz));
    REQUIRE(!(1_mHz >= 1_Hz));
    REQUIRE(!(1_Hz >= 1_KHz));
    REQUIRE(!(1_KHz >= 1_MHz));
    REQUIRE(!(1_MHz >= 1_GHz));
    REQUIRE(!(1_GHz >= 1_THz));
    REQUIRE(!(1_THz >= 1_PHz));

    REQUIRE(1_Hz >= 1_Hz);

    REQUIRE(2000.0_THz >= 1_PHz);
    REQUIRE(1000.0_uHz >= 1_mHz);
}
