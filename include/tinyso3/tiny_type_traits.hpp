
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

}; // namespace tinyso3