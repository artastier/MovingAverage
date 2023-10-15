//
// Created by aastier on 09/09/23.
//

#pragma once
#include "Traits.hpp"
namespace Smoother{
    /**
     * \class TemporalSmoother
     *
     * \brief Provides an interface for temporal smoothing algorithms.
     *
     * This class establishes an interface for temporal smoothing algorithms.
     * It ensures that the Signal type meets the necessary requirements for the arithmetic operations
     * utilized in the derived smoother implementations.
     *
     * \tparam Signal - The data type used for signal values.
     *                  It must provide arithmetic operations (+, -, /, *) and return the same type (Signal).
     *                  The Signal type also needs to be compatible with integral types for division and multiplication.
     *
     * \note Derived classes must implement the operator+ to provide the smoothing functionality.
     */
    template<typename Signal>
    class TemporalSmoother {
        // Compile-time checks to ensure Signal type compatibility
        static_assert(traits::has_plus_operator_and_returns_T_v<Signal>,
                      "The Signal type must define the operator+(Signal,Signal) -> Signal");
        static_assert(traits::has_minus_operator_and_returns_T_v<Signal>,
                      "The Signal type must define the operator-(Signal,Signal) -> Signal");
        // Double multiplication used in Simple and Double exponential smoothing
        static_assert(traits::has_multiplicative_operator_and_returns_T_v<Signal>,
                      "The Signal type must define the operator*(Signal, std::size_t) -> Signal");
        static_assert(traits::has_scalar_subtraction_operator_and_returns_T_v<Signal, int>,
                      "The Signal type must define the operator-(Signal, int) -> Signal");
        static_assert(traits::is_integral_divisible_and_returns_T_v<Signal, std::size_t>,
                      "The Signal type must define the operator/(Signal,std::size_t) -> Signal");
        static_assert(traits::is_integral_multiplicative_and_returns_T_v<Signal, std::size_t>,
                      "The Signal type must define the operator*(Signal, std::size_t) -> Signal");


    public:
        /**
         * \brief Virtual function to apply the smoothing algorithm on the provided data.
         *
         * Derived classes must provide an implementation for this function.
         *
         * \param data - The latest data point to be smoothed.
         * \return The smoothed signal value.
         */
        [[nodiscard]] virtual Signal operator+(Signal data) = 0;

        /**
         * \brief Default virtual destructor.
         */
        virtual ~TemporalSmoother() = default;
    };
}
