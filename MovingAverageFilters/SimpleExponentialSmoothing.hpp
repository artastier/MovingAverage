//
// Created by aastier on 09/09/23.
//

#pragma once

#include <deque>
#include <cmath>
#include <algorithm>
#include <cassert>
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
        explicit SimpleExponentialSmoothing(const double aAlpha) : alpha(aAlpha) {
            assert(alpha>0.0 && "Alphas must be strictly positive");
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