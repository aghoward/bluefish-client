#pragma once

#include <type_traits>
#include <utility>

#include "either/custom_traits.h"

enum class MemberIndex
{
    None,
    First,
    Second
};

template <typename TFirst, typename TSecond, typename T>
struct get_member_index
{
    static constexpr MemberIndex value = conditional_value_v<
        std::is_convertible_v<T, TFirst>,
        MemberIndex,
        MemberIndex::First,
        conditional_value_v<
            std::is_convertible_v<T, TSecond>,
            MemberIndex,
            MemberIndex::Second,
            MemberIndex::None>>;
};

template <typename TFirst, typename TSecond, typename T>
static constexpr MemberIndex get_member_index_v = get_member_index<TFirst, TSecond, T>::value;

template <typename TFirst, typename TSecond>
class either
{
    private:
        MemberIndex index;
        union member_t
        {
            char _c;

            TFirst first;
            TSecond second;

            member_t(TFirst&& f) : first(std::move(f)) {}
            member_t(TSecond&& s) : second(std::move(s)) {}
            ~member_t() {}
            member_t() : _c(0) {}
        };

        member_t member;

    public:
        template <typename T, MemberIndex Index = get_member_index_v<TFirst, TSecond, T>,
            typename = std::enable_if_t<std::disjunction_v<std::is_convertible<T, TFirst>, std::is_convertible<T, TSecond>>>>
        either(T&& value)
            : index(Index),
              member(std::move(value))
        {}

        ~either() {
            if (index == MemberIndex::First)
                member.first.~TFirst();
            else if (index == MemberIndex::Second)
                member.second.~TSecond();
        }

        either(either&& other)
        {
            index = other.index;
            if (index == MemberIndex::First)
                member.first = std::move(other.member.first);
            else if (index == MemberIndex::Second)
                member.second = std::move(other.member.second);
        }

        either& operator=(either&& other)
        {
            index = other.index;
            if (index == MemberIndex::First)
                member.first = std::move(other.member.first);
            else if (index == MemberIndex::Second)
                member.second = std::move(other.member.second);
            return *this;
        }
        
        template <typename TFirstFunc, typename TSecondFunc,
            typename TNewFirst = std::invoke_result_t<TFirstFunc, TFirst>,
            typename TNewSecond = std::invoke_result_t<TSecondFunc, TSecond>>
        either<TNewFirst, TNewSecond> map(TFirstFunc&& mapFirstFunc, TSecondFunc&& mapSecondFunc)
        {
            if (index == MemberIndex::First)
                return mapFirstFunc(std::move(member.first));
            return mapSecondFunc(std::move(member.second));
        }

        template <typename TFirstFunc, typename TNewFirst = std::invoke_result_t<TFirstFunc, TFirst>>
        either<TNewFirst, TSecond> mapFirst(TFirstFunc&& mapFirstFunc)
        {
            return map(std::forward<TFirstFunc>(mapFirstFunc), [] (auto&& second) -> TSecond { return second; });
        }

        template <typename TSecondFunc, typename TNewSecond>
        either<TFirst, TNewSecond> mapSecond(TSecondFunc&& mapSecondFunc)
        {
            return map([] (auto&& first) -> TFirst { return first; }, mapSecondFunc);
        }

        template <typename TFirstFunc, typename TSecondFunc,
                    typename TOutput = std::invoke_result_t<TFirstFunc, TFirst>,
                    typename = std::enable_if_t<std::is_same_v<std::invoke_result_t<TFirstFunc, TFirst>, std::invoke_result_t<TSecondFunc, TSecond>>>>
        TOutput match(TFirstFunc&& matchFirst, TSecondFunc&& matchSecond)
        {
            if (index == MemberIndex::First)
                return matchFirst(std::move(member.first));
            return matchSecond(std::move(member.second));
        }

        template <typename TFirstFunc, typename TNewResult = std::invoke_result_t<TFirstFunc, TFirst>,
                 typename TNewFirst = typename either_traits<TNewResult>::First>
        either<TNewFirst, TSecond> foldFirst(TFirstFunc&& mapFirst)
        {
            return match(mapFirst, [] (auto&& second) -> either<TNewFirst, TSecond> { return second; });
        }

        template <typename TSecondFunc, typename TNewResult = std::invoke_result_t<TSecondFunc, TSecond>,
                 typename TNewSecond = typename either_traits<TNewResult>::Second>
        either<TFirst, TNewSecond> foldSecond(TSecondFunc&& mapSecond)
        {
            return match([] (auto&& first) -> either<TFirst, TNewSecond> { return first; }, mapSecond);
        }
};
