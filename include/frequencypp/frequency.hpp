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
#include <ostream>
#include <ratio>
#include <sstream>
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

/// Convert a \ref frequency::frequency to a frequency of different type \p ToFrequency
///
/// No implicit conversions are used.  Computations are done in the widest type available and
/// converted, as if by \c static_cast, to the result type only when finished.
///
/// \tparam ToFrequency \ref frequency::frequency type to convert to
/// \tparam Rep arithmetic type representing the number of ticks for \p f
/// \tparam Period ratio representing the tick period for \p f
/// \param f frequency to convert
/// \return \p f converted to a frequency of type \p ToFrequency
template<typename ToFrequency, typename Rep, typename Period>
constexpr auto frequency_cast(const frequency<Rep, Period>& f)
    -> std::enable_if_t<detail::is_frequency_v<ToFrequency>, ToFrequency>
{
    using to_rep = typename ToFrequency::rep;
    using to_period = typename ToFrequency::period;
    using common_rep = std::common_type_t<Rep, to_rep, std::intmax_t>;
    using common_period = std::ratio_divide<Period, to_period>;
    return ToFrequency{static_cast<to_rep>(static_cast<common_rep>(f.count())
        * static_cast<common_rep>(common_period::num)
        / static_cast<common_rep>(common_period::den))};
}

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

    /// Construct the frequency by converting \p f to an appropriate period and tick count, as if by
    /// \p frequencypp::frequency_cast<frequency>(f).count()
    ///
    /// \tparam Rep2 arithmetic type representing the number of ticks
    /// \tparam Period2 ratio representing the tick period
    template<typename Rep2,
        typename Period2,
        typename = std::enable_if_t<
            std::chrono::treat_as_floating_point_v<
                rep> || (std::ratio_divide<Period2, period>::den == 1 && !std::chrono::treat_as_floating_point_v<Rep2>)>>
    constexpr frequency(const frequency<Rep2, Period2>& f)
        : count_(frequency_cast<frequency>(f).count())
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

    /// Get the reinforcement of the frequency
    ///
    /// \return reinforcement of the frequency
    constexpr auto operator+() const -> std::common_type_t<frequency>
    {
        return std::common_type_t<frequency>{*this};
    }

    /// Get the negation of the frequency
    ///
    /// \return negation of the frequency
    constexpr auto operator-() const -> std::common_type_t<frequency>
    {
        return std::common_type_t<frequency>{-count_};
    }

    /// Increment the number of ticks for this frequency
    ///
    /// \return reference to this frequency after modification
    constexpr auto operator++() -> frequency&
    {
        ++count_;
        return *this;
    }

    /// Increment the number of ticks for this frequency
    ///
    /// \return copy of this frequency before modification
    constexpr auto operator++(int) -> frequency
    {
        return frequency{count_++};
    }

    /// Decrement the number of ticks for this frequency
    ///
    /// \return reference to this frequency after modification
    constexpr auto operator--() -> frequency&
    {
        --count_;
        return *this;
    }

    /// Decrement the number of ticks for this frequency
    ///
    /// \return copy of this frequency before modification
    constexpr auto operator--(int) -> frequency
    {
        return frequency{count_--};
    }

    /// Add the frequency \p rhs to this frequency
    ///
    /// \param rhs right-hand frequency to add
    /// \return reference to this frequency after modification
    constexpr auto operator+=(const frequency& rhs) -> frequency&
    {
        count_ += rhs.count();
        return *this;
    }

    /// Subtract the frequency \p rhs from this frequency
    ///
    /// \param rhs right-hand frequency to subtract
    /// \return reference to this frequency after modification
    constexpr auto operator-=(const frequency& rhs) -> frequency&
    {
        count_ -= rhs.count();
        return *this;
    }

    /// Multiply this frequency by factor \p rhs
    ///
    /// \param rhs right-hand factor to multiply by
    /// \return reference to this frequency after modification
    constexpr auto operator*=(const rep& rhs) -> frequency&
    {
        count_ *= rhs;
        return *this;
    }

    /// Divide this frequency by factor \p rhs
    ///
    /// \param rhs right-hand factor to divide by
    /// \return reference to this frequency after modification
    constexpr auto operator/=(const rep& rhs) -> frequency&
    {
        count_ /= rhs;
        return *this;
    }

    /// Reduce this frequency by modulus \p rhs
    ///
    /// \param rhs right-hand modulus
    /// \return reference to this frequency after modification
    template<typename Rep2 = rep>
    constexpr auto operator%=(const rep& rhs)
        -> std::enable_if_t<!std::chrono::treat_as_floating_point_v<Rep2>, frequency&>
    {
        count_ %= rhs;
        return *this;
    }

    /// Reduce this frequency by modulus \p rhs
    ///
    /// \param rhs right-hand modulus
    /// \return reference to this frequency after modification
    template<typename Rep2 = rep>
    constexpr auto operator%=(const frequency& rhs)
        -> std::enable_if_t<!std::chrono::treat_as_floating_point_v<Rep2>, frequency&>
    {
        count_ %= rhs.count();
        return *this;
    }
};

// Comparison

/// Determine whether the left-hand frequency \p lhs is equal to the right-hand frequency \p rhs
///
/// The comparison is made using the common type of \p lhs and \p rhs.
///
/// \tparam Rep1 arithmetic type representing the number of ticks for \p lhs
/// \tparam Period1 ratio representing the tick period for \p lhs
/// \tparam Rep2 arithmetic type representing the number of ticks for \p rhs
/// \tparam Period2 ratio representing the tick period for \p rhs
/// \param lhs left-hand frequency to compare
/// \param rhs right-hand frequency to compare
/// \retval true if \p lhs and \p rhs represent the same frequency
/// \retval false if \p lhs and \p rhs represent different frequencies
template<typename Rep1, typename Period1, typename Rep2, typename Period2>
constexpr auto operator==(const frequency<Rep1, Period1>& lhs, const frequency<Rep2, Period2>& rhs)
    -> bool
{
    using ct = std::common_type_t<std::decay_t<decltype(lhs)>, std::decay_t<decltype(rhs)>>;
    return ct{lhs}.count() == ct{rhs}.count();
}

/// Determine whether the left-hand frequency \p lhs is unequal to the right-hand frequency \p rhs
///
/// The comparison is made using the common type of \p lhs and \p rhs.
///
/// \tparam Rep1 arithmetic type representing the number of ticks for \p lhs
/// \tparam Period1 ratio representing the tick period for \p lhs
/// \tparam Rep2 arithmetic type representing the number of ticks for \p rhs
/// \tparam Period2 ratio representing the tick period for \p rhs
/// \param lhs left-hand frequency to compare
/// \param rhs right-hand frequency to compare
/// \retval true if \p lhs and \p rhs represent different frequencies
/// \retval false if \p lhs and \p rhs represent the same frequency
template<typename Rep1, typename Period1, typename Rep2, typename Period2>
constexpr auto operator!=(const frequency<Rep1, Period1>& lhs, const frequency<Rep2, Period2>& rhs)
    -> bool
{
    return !(lhs == rhs);
}

/// Determine whether the left-hand frequency \p lhs is less frequent than the right-hand frequency
/// \p rhs
///
/// The comparison is made using the common type of \p lhs and \p rhs.
///
/// \tparam Rep1 arithmetic type representing the number of ticks for \p lhs
/// \tparam Period1 ratio representing the tick period for \p lhs
/// \tparam Rep2 arithmetic type representing the number of ticks for \p rhs
/// \tparam Period2 ratio representing the tick period for \p rhs
/// \param lhs left-hand frequency to compare
/// \param rhs right-hand frequency to compare
/// \retval true if \p lhs is less frequent than \p rhs
/// \retval false if \p lhs is more frequent than or as frequent as \p rhs
template<typename Rep1, typename Period1, typename Rep2, typename Period2>
constexpr auto operator<(const frequency<Rep1, Period1>& lhs, const frequency<Rep2, Period2>& rhs)
    -> bool
{
    using ct = std::common_type_t<std::decay_t<decltype(lhs)>, std::decay_t<decltype(rhs)>>;
    return ct{lhs}.count() < ct{rhs}.count();
}

/// Determine whether the left-hand frequency \p lhs is less frequent than or as frequent as the
/// right-hand frequency \p rhs
///
/// The comparison is made using the common type of \p lhs and \p rhs.
///
/// \tparam Rep1 arithmetic type representing the number of ticks for \p lhs
/// \tparam Period1 ratio representing the tick period for \p lhs
/// \tparam Rep2 arithmetic type representing the number of ticks for \p rhs
/// \tparam Period2 ratio representing the tick period for \p rhs
/// \param lhs left-hand frequency to compare
/// \param rhs right-hand frequency to compare
/// \retval true if \p lhs is less frequent than or as frequent as \p rhs
/// \retval false if \p lhs is more frequent than \p rhs
template<typename Rep1, typename Period1, typename Rep2, typename Period2>
constexpr auto operator<=(const frequency<Rep1, Period1>& lhs, const frequency<Rep2, Period2>& rhs)
    -> bool
{
    return !(rhs < lhs);
}

/// Determine whether the left-hand frequency \p lhs is more frequent than the right-hand frequency
/// \p rhs
///
/// The comparison is made using the common type of \p lhs and \p rhs.
///
/// \tparam Rep1 arithmetic type representing the number of ticks for \p lhs
/// \tparam Period1 ratio representing the tick period for \p lhs
/// \tparam Rep2 arithmetic type representing the number of ticks for \p rhs
/// \tparam Period2 ratio representing the tick period for \p rhs
/// \param lhs left-hand frequency to compare
/// \param rhs right-hand frequency to compare
/// \retval true if \p lhs is more frequent than \p rhs
/// \retval false if \p lhs is less frequent than or as frequent as \p rhs
template<typename Rep1, typename Period1, typename Rep2, typename Period2>
constexpr auto operator>(const frequency<Rep1, Period1>& lhs, const frequency<Rep2, Period2>& rhs)
    -> bool
{
    return rhs < lhs;
}

/// Determine whether the left-hand frequency \p lhs is more frequent than or as frequent as the
/// right-hand frequency \p rhs
///
/// The comparison is made using the common type of \p lhs and \p rhs.
///
/// \tparam Rep1 arithmetic type representing the number of ticks for \p lhs
/// \tparam Period1 ratio representing the tick period for \p lhs
/// \tparam Rep2 arithmetic type representing the number of ticks for \p rhs
/// \tparam Period2 ratio representing the tick period for \p rhs
/// \param lhs left-hand frequency to compare
/// \param rhs right-hand frequency to compare
/// \retval true if \p lhs is more frequent than or as frequent as \p rhs
/// \retval false if \p lhs is less frequent than \p rhs
template<typename Rep1, typename Period1, typename Rep2, typename Period2>
constexpr auto operator>=(const frequency<Rep1, Period1>& lhs, const frequency<Rep2, Period2>& rhs)
    -> bool
{
    return !(lhs < rhs);
}

/// Inserts a textual representation of \p f into \p os
///
/// The frequency is inserted into \p os as a string after being formatted out-of-line in a stream
/// that matches the flags, locale, and precision of \p os.
///
/// \tparam CharT character type of the stream
/// \tparam Traits character traits for the stream
/// \tparam Rep arithmetic type representing the number of ticks
/// \tparam Period ratio representing the tick period
/// \param os stream to insert into
/// \param f frequency to insert
/// \return reference to \p os
template<typename CharT, typename Traits, typename Rep, typename Period>
auto operator<<(std::basic_ostream<CharT, Traits>& os, const frequency<Rep, Period>& f)
    -> std::basic_ostream<CharT, Traits>&
{
    std::basic_ostringstream<CharT, Traits> s;
    s.flags(os.flags());
    s.imbue(os.getloc());
    s.precision(os.precision());
    s << f.count();

    // Select the unit suffix at compile-time
    if constexpr (std::ratio_equal_v<Period, std::nano>) {
        s << "nHz";
    }
    else if constexpr (std::ratio_equal_v<Period, std::micro>) {
        s << "µHz";
    }
    else if constexpr (std::ratio_equal_v<Period, std::milli>) {
        s << "mHz";
    }
    else if constexpr (std::ratio_equal_v<Period, std::ratio<1>>) {
        s << "Hz";
    }
    else if constexpr (std::ratio_equal_v<Period, std::kilo>) {
        s << "KHz";
    }
    else if constexpr (std::ratio_equal_v<Period, std::mega>) {
        s << "MHz";
    }
    else if constexpr (std::ratio_equal_v<Period, std::giga>) {
        s << "GHz";
    }
    else if constexpr (std::ratio_equal_v<Period, std::tera>) {
        s << "THz";
    }
    else if constexpr (std::ratio_equal_v<Period, std::peta>) {
        s << "PHz";
    }
    else if constexpr (Period::type::den == 1) {
        s << '[' << Period::type::num << "]Hz";
    }
    else {
        s << '[' << Period::type::num << '/' << Period::type::den << "]Hz";
    }

    return os << s.str();
}

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

inline namespace literals {

/// Literal suffix for frequencies of type \ref frequencypp::nanohertz
///
/// \param r tick count
/// \return nanohertz with tick count \p r
constexpr auto operator"" _nHz(unsigned long long r) -> nanohertz
{
    return nanohertz{r};
}

/// Literal suffix for frequencies representing non-integer nanohertz
///
/// \param r tick count
/// \return nanohertz with tick count \p r
constexpr auto operator"" _nHz(long double r) -> frequency<long double, std::nano>
{
    return frequency<long double, std::nano>{r};
}

/// Literal suffix for frequencies of type \ref frequencypp::microhertz
///
/// \param r tick count
/// \return microhertz with tick count \p r
constexpr auto operator"" _uHz(unsigned long long r) -> microhertz
{
    return microhertz{r};
}

/// Literal suffix for frequencies representing non-integer microhertz
///
/// \param r tick count
/// \return microhertz with tick count \p r
constexpr auto operator"" _uHz(long double r) -> frequency<long double, std::micro>
{
    return frequency<long double, std::micro>{r};
}

/// Literal suffix for frequencies of type \ref frequencypp::millihertz
///
/// \param r tick count
/// \return millihertz with tick count \p r
constexpr auto operator"" _mHz(unsigned long long r) -> millihertz
{
    return millihertz{r};
}

/// Literal suffix for frequencies representing non-integer millihertz
///
/// \param r tick count
/// \return millihertz with tick count \p r
constexpr auto operator"" _mHz(long double r) -> frequency<long double, std::milli>
{
    return frequency<long double, std::milli>{r};
}

/// Literal suffix for frequencies of type \ref frequencypp::hertz
///
/// \param r tick count
/// \return millihertz with tick count \p r
constexpr auto operator"" _Hz(unsigned long long r) -> hertz
{
    return hertz{r};
}

/// Literal suffix for frequencies representing non-integer hertz
///
/// \param r tick count
/// \return millihertz with tick count \p r
constexpr auto operator"" _Hz(long double r) -> frequency<long double>
{
    return frequency<long double>{r};
}

/// Literal suffix for frequencies of type \ref frequencypp::kilohertz
///
/// \param r tick count
/// \return kilohertz with tick count \p r
constexpr auto operator"" _KHz(unsigned long long r) -> kilohertz
{
    return kilohertz{r};
}

/// Literal suffix for frequencies representing non-integer kilohertz
///
/// \param r tick count
/// \return kilohertz with tick count \p r
constexpr auto operator"" _KHz(long double r) -> frequency<long double, std::kilo>
{
    return frequency<long double, std::kilo>{r};
}

/// Literal suffix for frequencies of type \ref frequencypp::megahertz
///
/// \param r tick count
/// \return megahertz with tick count \p r
constexpr auto operator"" _MHz(unsigned long long r) -> megahertz
{
    return megahertz{r};
}

/// Literal suffix for frequencies representing non-integer megahertz
///
/// \param r tick count
/// \return megahertz with tick count \p r
constexpr auto operator"" _MHz(long double r) -> frequency<long double, std::mega>
{
    return frequency<long double, std::mega>{r};
}

/// Literal suffix for frequencies of type \ref frequencypp::gigahertz
///
/// \param r tick count
/// \return gigahertz with tick count \p r
constexpr auto operator"" _GHz(unsigned long long r) -> gigahertz
{
    return gigahertz{r};
}

/// Literal suffix for frequencies representing non-integer gigahertz
///
/// \param r tick count
/// \return gigahertz with tick count \p r
constexpr auto operator"" _GHz(long double r) -> frequency<long double, std::giga>
{
    return frequency<long double, std::giga>{r};
}

/// Literal suffix for frequencies of type \ref frequencypp::terahertz
///
/// \param r tick count
/// \return terahertz with tick count \p r
constexpr auto operator"" _THz(unsigned long long r) -> terahertz
{
    return terahertz{r};
}

/// Literal suffix for frequencies representing non-integer terahertz
///
/// \param r tick count
/// \return terahertz with tick count \p r
constexpr auto operator"" _THz(long double r) -> frequency<long double, std::tera>
{
    return frequency<long double, std::tera>{r};
}

/// Literal suffix for frequencies of type \ref frequencypp::petahertz
///
/// \param r tick count
/// \return petahertz with tick count \p r
constexpr auto operator"" _PHz(unsigned long long r) -> petahertz
{
    return petahertz{r};
}

/// Literal suffix for frequencies representing non-integer petahertz
///
/// \param r tick count
/// \return petahertz with tick count \p r
constexpr auto operator"" _PHz(long double r) -> frequency<long double, std::peta>
{
    return frequency<long double, std::peta>{r};
}

} // namespace literals

} // namespace frequencypp

#endif // FREQUENCYPP_FREQUENCY_HPP
