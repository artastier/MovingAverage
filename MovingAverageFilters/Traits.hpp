//
// Created by aastier on 09/09/23.
//
#pragma once

#include <type_traits>
namespace Smoother::traits
{
    /**
     * @brief Meta-function to check if a type `T` has an addition operator (`operator+`)
     *        that returns a type `T`.
     *
     * @tparam T The type to check for the presence of the `operator+`.
     * @tparam _ (unnamed) Used for SFINAE purposes.
     */
    template<typename T, typename = void>
    struct has_plus_operator_and_returns_T : public std::false_type {};

    /**
     * @brief Specialization of the `has_plus_operator_and_returns_T` meta-function.
     *        This is activated if a type `T` has an `operator+` that returns a type `T`.
     */
    template<typename T>
    struct has_plus_operator_and_returns_T<T, std::enable_if_t<std::is_same_v<
            decltype(std::declval<T>() + std::declval<T>()),
            T>>>: public std::true_type {};

    template<typename T>
    constexpr static auto has_plus_operator_and_returns_T_v = has_plus_operator_and_returns_T<T>::value;

    /**
     * @brief Meta-function to check if a type `T` has the subtraction operator (`operator-`)
     *        that returns a type `T`.
     *
     * @tparam T The type to check for the presence of the `operator-`.
     * @tparam _ (unnamed) Used for SFINAE purposes.
     */
    template<typename T, typename = void>
    struct has_minus_operator_and_returns_T : public std::false_type {};

    /**
     * @brief Specialization of the `has_minus_operator_and_returns_T` meta-function.
     *        This is activated if a type `T` has an `operator-` that returns a type `T`.
     */
    template<typename T>
    struct has_minus_operator_and_returns_T<T, std::enable_if_t<std::is_same_v<
            decltype(std::declval<T>() - std::declval<T>()),
            T>>> : public std::true_type {};

    template<typename T>
    constexpr static auto has_minus_operator_and_returns_T_v = has_minus_operator_and_returns_T<T>::value;


    /**
     * @brief Meta-function to check if a type `Tp` is divisible by an integer operator (`operator-`)
     *        that returns a type `Tp`.
     *
     * @tparam Tp The type to check for the presence of the `operator-`.
     * @tparam _ (unnamed) Used for SFINAE purposes.
     */
    template<typename Tp, typename Up, bool = std::is_integral_v<Up>, typename = void>
    struct is_integral_divisible_and_returns_T : public std::false_type {};

    /**
     * @brief Specialization of the `is_integral_divisible_and_returns_T` meta-function.
     *        This is activated if a type `Tp` has an `operator-/(Up)` that returns a type `Tp`.
     */
    template<typename Tp, typename Up>
    struct is_integral_divisible_and_returns_T<Tp, Up, true, std::enable_if_t<std::is_same_v<decltype(std::declval<Tp>() / std::declval<Up>()), Tp>>> : public std::true_type {};

    template<typename Tp, typename Up>
    constexpr static auto is_integral_divisible_and_returns_T_v = is_integral_divisible_and_returns_T<Tp, Up>::value;

    /**
     * @brief Meta-function to check if a type `Tp` can be multiplied by an integer operator (`operator*`)
     *        that returns a type `Tp`.
     *
     * @tparam Tp The type to check for the presence of the `operator-`.
     * @tparam _ (unnamed) Used for SFINAE purposes.
     */
    template<typename Tp, typename Up, bool = std::is_integral_v<Up>, typename = void>
    struct is_integral_multiplicative_and_returns_T : public std::false_type {};

    /**
     * @brief Specialization of the `is_integral_multiplicative_and_returns_T` meta-function.
     *        This is activated if a type `Tp` has an `operator*(Up)` that returns a type `Tp`.
     */
    template<typename Tp, typename Up>
    struct is_integral_multiplicative_and_returns_T<Tp, Up, true, std::enable_if_t<std::is_same_v<decltype(std::declval<Up>() * std::declval<Tp>()), Tp>>> : public std::true_type {};

    template<typename Tp, typename Up>
    constexpr static auto is_integral_multiplicative_and_returns_T_v = is_integral_multiplicative_and_returns_T<Tp, Up>::value;

    //TODO: Change doxygen

    /**
     * @brief Meta-function to check if a type `Tp` can be multiplied by an integer operator (`operator*`)
     *        that returns a type `Tp`.
     *
     * @tparam Tp The type to check for the presence of the `operator-`.
     * @tparam _ (unnamed) Used for SFINAE purposes.
     */
    template<typename Tp, typename Up, bool = std::is_floating_point_v<Up>, typename = void>
    struct is_floating_multiplicative_and_returns_T : public std::false_type {};

    /**
     * @brief Specialization of the `is_integral_multiplicative_and_returns_T` meta-function.
     *        This is activated if a type `Tp` has an `operator*(Up)` that returns a type `Tp`.
     */
    template<typename Tp, typename Up>
    struct is_floating_multiplicative_and_returns_T<Tp, Up, true, std::enable_if_t<std::is_same_v<decltype(std::declval<Up>() * std::declval<Tp>()), Tp>>> : public std::true_type {};

    template<typename Tp, typename Up>
    constexpr static auto is_floating_multiplicative_and_returns_T_v = is_floating_multiplicative_and_returns_T<Tp, Up>::value;

}// namespace Smoother::traits