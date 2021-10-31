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

/// \file
/// Contains the temporal frequency type \ref frequencypp::frequency and its associated types and
/// specializations

#ifndef FREQUENCYPP_FREQUENCY_HPP
#define FREQUENCYPP_FREQUENCY_HPP

#include <numeric>
#include <ratio>
#include <type_traits>

// Forward declaration of the frequencypp::frequency type

namespace frequencypp {

template<typename Rep, typename Period = std::ratio<1>>
struct frequency;

} // namespace frequencypp

// Types needed to implement frequency, which may refer to the above forward declaration

/// Specialization of std::common_type for \ref frequencypp::frequency
template<typename Rep1, typename Period1, typename Rep2, typename Period2>
struct std::common_type<frequencypp::frequency<Rep1, Period1>,
    frequencypp::frequency<Rep2, Period2>>
{
private:
    static constexpr auto gcd_num = std::gcd(Period1::num, Period2::num);
    static constexpr auto gcd_den = std::gcd(Period1::den, Period2::den);
    using period = std::ratio<gcd_num, Period1::den / gcd_den * Period2::den>;

public:
    /// Common type of two \ref frequencypp::frequency types, whose period is the greatest common
    /// divisor of \p Period1 and \p Period2
    using type = frequencypp::frequency<std::common_type_t<Rep1, Rep2>, typename period::type>;
};

/// Specialization of std::common_type for two identical \ref frequencypp::frequency types
template<typename Rep, typename Period>
struct std::common_type<frequencypp::frequency<Rep, Period>>
{
    /// Common type of two identical \ref frequencypp::frequency types
    using type = frequencypp::frequency<std::common_type_t<Rep>, typename Period::type>;
};

namespace frequencypp {

/// Represents a temporal frequency
///
/// A frequency consists of a count of ticks of type \p Rep and a tick period \p Period, where the
/// tick period is a compile-time rational fraction representing the frequency in hertz from one
/// tick to the next.
///
/// The only data stored in a \ref frequencypp::frequency is a tick count of type \p Rep.  If \p Rep
/// is floating point, then the \ref frequencypp::frequency can represent fractions of ticks.
/// \p Period is included as part of the type and is only used when converting between different
/// frequencies.
///
/// \tparam Rep arithmetic type representing the number of ticks
/// \tparam Period ratio representing the tick period
template<typename Rep, typename Period>
struct frequency
{
public:
    /// Arithmetic type representing the number of ticks
    using rep = Rep;
    /// Ratio representing the tick period (i.e. the number of hertz fractions per tick)
    using period = typename Period::type;
};

} // namespace frequencypp

#endif // FREQUENCYPP_FREQUENCY_HPP
