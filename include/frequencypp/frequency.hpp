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

#include <chrono>
#include <cstdint>
#include <limits>
#include <numeric>
#include <ratio>
#include <type_traits>

// Forward declaration of the frequencypp::frequency type

namespace frequencypp {

template<typename Rep, typename Period = std::ratio<1>>
struct frequency;

} // namespace frequencypp

// Types needed to implement frequency, which may refer to the above forward declaration

namespace frequencypp {
namespace detail {

template<typename T>
struct is_frequency : std::false_type
{};

template<typename Rep, typename Period>
struct is_frequency<frequency<Rep, Period>> : std::true_type
{};

template<typename T>
constexpr bool is_frequency_v = is_frequency<T>::value;

template<typename T>
struct is_ratio : std::false_type
{};

template<std::intmax_t Num, std::intmax_t Den>
struct is_ratio<std::ratio<Num, Den>> : std::true_type
{};

template<typename T>
constexpr bool is_ratio_v = is_ratio<T>::value;

} // namespace detail
} // namespace frequencypp

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

/// Defines three common frequencies that can be specialized for a given \p Rep if the
/// representation requires specific values
///
/// The \ref frequencypp::frequency::zero, \ref frequencypp::frequency::min, and
/// \ref frequencypp::frequency::max methods forward their work to these methods.
///
/// \tparam Rep arithmetic type representing the number of ticks
template<typename Rep>
struct frequency_values
{
    /// Gets the zero-length representation
    ///
    /// \return zero-length representation
    static constexpr auto zero() noexcept -> Rep
    {
        return Rep{0};
    }

    /// Gets the smallest possible representation
    ///
    /// \return smallest possible representation
    static constexpr auto min() noexcept -> Rep
    {
        return std::numeric_limits<Rep>::lowest();
    }

    /// Gets the largest possible representation
    ///
    /// \return largest possible representation
    static constexpr auto max() noexcept -> Rep
    {
        return std::numeric_limits<Rep>::max();
    }
};

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
    using rep_values = frequency_values<Rep>;

    Rep count_;

public:
    /// Arithmetic type representing the number of ticks
    using rep = Rep;
    /// Ratio representing the tick period (i.e. the number of hertz fractions per tick)
    using period = typename Period::type;

    static_assert(!detail::is_frequency_v<rep>, "rep cannot be a frequency");
    static_assert(detail::is_ratio_v<period>, "period must be a ratio");
    static_assert(period::num > 0, "period must be positive");

    /// Default-construct the frequency
    constexpr frequency() = default;

    /// Copy-construct the frequency
    frequency(const frequency&) = default;

    /// Construct the frequency with \p r ticks
    ///
    /// \tparam Rep2 arithmetic type representing the number of ticks
    /// \param r tick count
    template<typename Rep2,
        typename = std::enable_if_t<
            std::is_convertible_v<const Rep2&,
                rep> && (std::chrono::treat_as_floating_point_v<rep> || !std::chrono::treat_as_floating_point_v<Rep2>)>>
    constexpr explicit frequency(const Rep2& r)
        : count_(static_cast<rep>(r))
    {}

    /// Destruct the frequency
    ~frequency() = default;

    /// Copy-assign the frequency
    auto operator=(const frequency&) -> frequency& = default;

    /// Gets the zero-length frequency
    ///
    /// If the representation \p Rep of the frequency requires some other implementation to return a
    /// zero-length frequency, \ref frequencypp::frequency_values can be specialized to return the
    /// desired value.
    ///
    /// \return zero-length frequency
    static constexpr auto zero() noexcept -> frequency
    {
        return frequency{rep_values::zero()};
    }

    /// Gets the smallest possible frequency
    ///
    /// If the representation \p Rep of the frequency requires some other implementation to return a
    /// smallest possible frequency, \ref frequencypp::frequency_values can be specialized to return
    /// the desired value.
    ///
    /// \return smallest possible frequency
    static constexpr auto min() noexcept -> frequency
    {
        return frequency{rep_values::min()};
    }

    /// Gets the largest possible frequency
    ///
    /// If the representation \p Rep of the frequency requires some other implementation to return a
    /// largest possible frequency, \ref frequencypp::frequency_values can be specialized to return
    /// the desired value.
    ///
    /// \return largest possible frequency
    static constexpr auto max() noexcept -> frequency
    {
        return frequency{rep_values::max()};
    }

    /// Get the number of ticks
    ///
    /// \return number of ticks
    constexpr auto count() const -> rep
    {
        return count_;
    }
};

// SI units

using nanohertz = frequency<std::int64_t, std::nano>; ///< Frequency specified in nanohertz (nHz)
using microhertz = frequency<std::int64_t, std::micro>; ///< Frequency specified in microhertz (uHz)
using millihertz = frequency<std::int64_t, std::milli>; ///< Frequency specified in millihertz (mHz)
using hertz = frequency<std::int64_t>; ///< Frequency specified in hertz (Hz)
using kilohertz = frequency<std::int64_t, std::kilo>; ///< Frequency specified in kilohertz (KHz)
using megahertz = frequency<std::int64_t, std::mega>; ///< Frequency specified in megahertz (MHz)
using gigahertz = frequency<std::int32_t, std::giga>; ///< Frequency specified in gigahertz (GHz)
using terahertz = frequency<std::int32_t, std::tera>; ///< Frequency specified in terahertz (THz)
using petahertz = frequency<std::int16_t, std::peta>; ///< Frequency specified in petahertz (PHz)

} // namespace frequencypp

#endif // FREQUENCYPP_FREQUENCY_HPP
