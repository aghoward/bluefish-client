#pragma once

#include <utility>

template <bool Bool, typename T, T TrueValue, T FalseValue>
struct conditional_value
{
    static constexpr T value = TrueValue;
};

template <typename T, T TrueValue,T FalseValue>
struct conditional_value<false, T, TrueValue, FalseValue>
{
    static constexpr T value = FalseValue;
};

template <bool Bool, typename T, T TrueValue, T FalseValue>
static constexpr T conditional_value_v = conditional_value<Bool, T, TrueValue, FalseValue>::value;


template <typename TFirst, typename TSecond>
class either;

namespace detail
{
    template <typename TFirst, typename TSecond>
    TFirst get_first(either<TFirst, TSecond>);

    template <typename TFirst, typename TSecond>
    TSecond get_second(either<TFirst, TSecond>);
}

template <typename TEither>
struct either_traits
{
    typedef decltype(detail::get_first(std::declval<TEither>())) First;
    typedef decltype(detail::get_second(std::declval<TEither>())) Second;
};
