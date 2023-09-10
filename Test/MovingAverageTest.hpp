//
// Created by aastier on 09/09/23.
//

#pragma once

#include <type_traits>
#include <deque>
#include <cmath>
#include "../MovingAverageFilters/MovingAverage.hpp"

/**
 *
 * @tparam numerical
 */
template<typename numerical, typename =std::enable_if_t<std::is_floating_point_v<numerical>>>
class MovingAverageTest: public MovingAverage<numerical>{
    using MovingAverageType = MovingAverage<numerical>;
    using Trajectory = std::vector<std::pair<numerical, numerical>>;
public:
    /**
     *
     * @param samplingFrequency
     * @param subsetDuration
     */
    MovingAverageTest(const numerical samplingFrequency, const numerical subsetDuration) : MovingAverageType(
            samplingFrequency, subsetDuration) {}


    [[nodiscard]] Trajectory filterTrajectory(Trajectory &inputTrajectory) {
        Trajectory filteredTrajectory{};
        filteredTrajectory.reserve(std::size(inputTrajectory));
        std::transform(std::begin(inputTrajectory), std::end(inputTrajectory), std::back_inserter(filteredTrajectory),
                       [this](const auto &point) {
                           const auto filteredSignal{MovingAverageType::filter(point.second)};
                           return std::make_pair(point.first, filteredSignal);
                       });
        return filteredTrajectory;
    }

    virtual ~MovingAverageTest() = default;

};
