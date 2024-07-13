
/**
 * @file tiny_type_traits.hpp
 * 
 * Type traits for TinySO3.
 * 
 * @author timetravelCat <timetraveler930@gmail.com>
 */

#pragma once

namespace tinyso3 {
/**
 * @brief enable_if
 */
template<bool, typename T = void>
struct enable_if {};
template<typename T>
struct enable_if<true, T> {
    using type = T;
};
template<bool B, typename T = void>
using enable_if_t = typename enable_if<B, T>::type;

template<bool B, class T, class F>
struct conditional { using type = T; };
template<class T, class F>
struct conditional<false, T, F> { using type = F; };
template<bool B, class T, class F>
using conditional_t = typename conditional<B, T, F>::type;

/**
 * @brief integral_constant
 */
template<class T, T v>
struct integral_constant {
    static constexpr T value = v;
    using value_type = T;
    using type = integral_constant; // using injected-class-name
    constexpr operator value_type() const noexcept { return value; }
    constexpr value_type operator()() const noexcept { return value; }
};

using true_type = integral_constant<bool, true>;
using false_type = integral_constant<bool, false>;

/**
 * @brief is_same
 */
template<class T, class U>
struct is_same : false_type {};
template<class T>
struct is_same<T, T> : true_type {};

/**
 * @brief is_floating_point
 */
template<typename T>
struct is_floating_point : false_type {};
template<>
struct is_floating_point<float> : true_type {};
template<>
struct is_floating_point<double> : true_type {};
template<>
struct is_floating_point<long double> : true_type {};
}; // namespace tinyso3