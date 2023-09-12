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
    class SimpleExponentialSmoothing : public TemporalSmoother<Signal> {
    public:
        /**
         *
         * @param aAlpha
         */
        SimpleExponentialSmoothing(const double aAlpha) : alpha(aAlpha) {
            // TODO: Add static assert if alpha not in [0,1]
        };

        /**
         *
         * @param lastSignalData
         * @return
         */
        [[nodiscard]] Signal operator+(Signal data) override {
            if (firstMeasureFlag) {
                firstMeasureFlag = false;
                smoothed = data;
            } else {
                smoothed = alpha * data + (1 - alpha) * smoothed;
            }
            return smoothed;
        }

        virtual ~SimpleExponentialSmoothing() = default;

    private:
        const double alpha{};
        bool firstMeasureFlag{true};
        Signal smoothed{Signal{}};
    };
}