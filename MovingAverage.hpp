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
class MovingAverage {
public:
    /**
     *
     * @param samplingFrequency
     * @param subsetDuration
     */
    MovingAverage(const numerical samplingFrequency, const numerical subsetDuration) : subsetSize(
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
            mean = mean + (lastSignalData - subset.front()) / subsetSize;
            subset.pop_front();
        } else {
            mean = (iteration * mean + lastSignalData) / (iteration + 1);
            ++iteration;
        }
        subset.emplace_back(lastSignalData);
        return mean;
    }


    /**
     *
     */
    void clear() {
        subset.clear();
        iteration = 0u;
        mean = 0.0;
    }

    virtual ~MovingAverage() = default;

private:
    const std::size_t subsetSize{};
    std::deque<numerical> subset{};
    numerical mean{numerical{}};
    std::size_t iteration{0u};
};
