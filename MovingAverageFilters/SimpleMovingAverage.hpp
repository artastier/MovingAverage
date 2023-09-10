//
// Created by aastier on 09/09/23.
//

#pragma once

#include <type_traits>
#include <deque>
#include <cmath>
#include <vector>
#include <algorithm>

/**
 *
 * @tparam numerical
 */
template<typename numerical, typename =std::enable_if_t<std::is_floating_point_v<numerical>>>
class SimpleMovingAverage {
public:
    /**
     *
     * @param samplingFrequency
     * @param subsetDuration
     */
    SimpleMovingAverage(const numerical samplingFrequency, const numerical subsetDuration) : subsetSize(
            std::floor(subsetDuration * samplingFrequency)) {
        // TODO: Add static assert if subset size is null
    };

    /**
     *
     * @param lastSignalData
     * @return
     */
    [[nodiscard]] numerical filter(const numerical lastSignalData) {
        // One of the improvement would be to switch of model and not always re-assessing the condition when we reached the subset size
        if (std::size(subset) == subsetSize) {
            smoothed = smoothed + (lastSignalData - subset.front()) / subsetSize;
            subset.pop_front();
        } else {
            smoothed = (iteration * smoothed + lastSignalData) / (iteration + 1);
            ++iteration;
        }
        subset.emplace_back(lastSignalData);
        return smoothed;
    }


    /**
     *
     */
    void clear() {
        subset.clear();
        iteration = 0u;
        smoothed = 0.0;
    }

    virtual ~SimpleMovingAverage() = default;

private:
    const std::size_t subsetSize{};
    std::deque<numerical> subset{};
    numerical smoothed{numerical{}};
    std::size_t iteration{0u};
};
