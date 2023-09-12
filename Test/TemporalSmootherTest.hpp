//
// Created by aastier on 09/09/23.
//

#pragma once

#include <type_traits>
#include <deque>
#include <cmath>
namespace Test {
/**
 *
 * @tparam numerical
 */
// I could have the signal from filter but declaring a type Signal in the filters isn't useful at all in practice
    template<typename Filter, typename Signal>
    class TemporalSmootherTest {
        using Trajectory = std::vector<std::pair<double, Signal>>;
    public:
    public:
        explicit TemporalSmootherTest(Filter &aFilter) : filter(aFilter) {}


        [[nodiscard]] Trajectory filterTrajectory(Trajectory &inputTrajectory) {
            Trajectory filteredTrajectory{};
            filteredTrajectory.reserve(std::size(inputTrajectory));
            std::transform(std::begin(inputTrajectory), std::end(inputTrajectory),
                           std::back_inserter(filteredTrajectory),
                           [this](const auto &point) {
                               const auto filteredSignal{filter + point.second};
                               return std::make_pair(point.first, filteredSignal);
                           });
            return filteredTrajectory;
        }

        virtual ~TemporalSmootherTest() = default;

    private:
        Filter filter{};
    };
}