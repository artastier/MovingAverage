//
// Created by aastier on 09/09/23.
//

#pragma once

#include <type_traits>
#include <deque>
#include <cmath>
#include <vector>
#include <algorithm>
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
            // TODO: Add static assert if alpha not in [0,1]
            // TODO: Add static assert if beta not in [0,1]

        };

        /**
         *
         * @param data
         * @return
         */
        [[nodiscard]] Signal operator+(const Signal data) override {
            if (initMeasureFlags[0]) {
                initMeasureFlags[0] = false;
                smoothed = data;
            } else if (initMeasureFlags[1]) {
                initMeasureFlags[1] = false;
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
        std::vector<bool> initMeasureFlags{true, true};
        Signal smoothed{Signal{}};
        Signal trend{Signal{}};
    };
}