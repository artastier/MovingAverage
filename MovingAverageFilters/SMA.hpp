//
// Created by aastier on 09/09/23.
//

#pragma once

#include "TemporalSmoother.hpp"
#include "Traits.hpp"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <deque>
#include <type_traits>
#include <vector>

namespace Smoother
{

    /**
     * \class SimpleMovingAverage
     *
     * \brief Provides functionality to calculate the simple moving average of a sequence of numbers.
     *
     * This class implements the simple moving average (SMA) method to smooth data.
     * It uses a subset of the data and averages it to produce the smoothed output.
     *
     * \tparam Signal - The Signal type used for calculations.
     *                     Must be a floating-point type.
     */
    template<typename Signal, typename Alloc = std::allocator<Signal>>
    class SMA : public TemporalSmoother<Signal> {
        using SlidingWindow = std::deque<Signal, Alloc>;
        using Dur = std::chrono::duration<double>;

    public:
        /**
         * \brief Constructor for initializing the SimpleMovingAverage.
         *
         * Initializes the subset size based on the sampling frequency and the desired subset duration.
         *
         * \param samplingFrequency - The frequency at which data points are sampled.
         * \param subsetDuration    - The duration of the subset used for averaging.
         */
        SMA(const double samplingFrequency, Dur duration)
                : subsetSize(std::floor(duration.count() * samplingFrequency)){};

        /**
         * \brief Filters the last signal data and computes the smoothed value.
         *
         * Calculates the simple moving average of the given signal data and returns the smoothed value.
         *
         * \param data - The latest data point to be filtered.
         * \return The smoothed value after applying the simple moving average.
         */
        [[nodiscard]] Signal operator+(Signal data) override
        {
            // One of the improvement would be to switch of model and not always re-assessing the condition when we reached the subset size
            if (iteration >= subsetSize) {
                smoothed = smoothed + (data - subset.front()) / subsetSize;
                subset.pop_front();
            } else {
                smoothed = (iteration * smoothed + data) / (iteration + 1);
                ++iteration;
            }
            subset.emplace_back(data);
            return smoothed;
        }

        /**
         * \brief Default destructor.
         */
        virtual ~SMA() = default;

    private:
        const std::size_t subsetSize{};
        SlidingWindow subset{};
        Signal smoothed{};
        std::size_t iteration{0u};
    };
}// namespace Smoother