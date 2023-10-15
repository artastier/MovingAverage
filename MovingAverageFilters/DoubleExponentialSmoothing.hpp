//
// Created by aastier on 09/09/23.
//

#pragma once

#include <type_traits>
#include <deque>
#include <cmath>
#include <bitset>
#include <algorithm>
#include <cassert>
#include "TemporalSmoother.hpp"
namespace Smoother {
/**
 *
 * @tparam numerical
 */
    template<typename Signal>
    class DoubleExponentialSmoothing: public TemporalSmoother<Signal> {
    public:
        /**
         *
         * @param aAlpha
         * @param aBeta
         */
        DoubleExponentialSmoothing(const double aAlpha, const double aBeta) : alpha(aAlpha), beta(aBeta) {
            assert(alpha>0.0 && "Alphas must be strictly positive");
            assert(beta>0.0 && "Betas must be strictly positive");

        };

        /**
         *
         * @param data
         * @return
         */
        [[nodiscard]] Signal operator+(const Signal data) override {
            if (initMeasureFlags.none()) {
                initMeasureFlags[0] = true;
                smoothed = data;
            } else if (not initMeasureFlags.all()) {
                initMeasureFlags[1] = true;
                trend = data - smoothed;
                smoothed = alpha * data + (1 - alpha) * (smoothed + trend);
            } else {
                const auto previousSmoothed{smoothed};
                smoothed = alpha * data + (1 - alpha) * (previousSmoothed + trend);
                trend = beta * (smoothed - previousSmoothed) + (1 - beta) * trend;
            }
            return smoothed;
        }

        virtual ~DoubleExponentialSmoothing() = default;

    private:
        const double alpha{};
        const double beta{};
        std::bitset<2> initMeasureFlags{};
        Signal smoothed{Signal{}};
        Signal trend{Signal{}};
    };
}