//
// Created by aastier on 09/09/23.
//

#pragma once

#include <random>
#include <algorithm>

template<typename numerical, typename=std::enable_if_t<std::is_floating_point_v<numerical>>>
class NoisySinusoid {
public:
    using Trajectory = std::vector<std::pair<numerical, numerical>>;
public:
    NoisySinusoid() = default;

    [[nodiscard]] Trajectory
    generateTrajectory(const numerical duration, const numerical samplingFrequency) {
        const auto step{1/samplingFrequency};
        const auto nbPoints{std::floor(duration * samplingFrequency)};
        Trajectory sinusoid{};
        sinusoid.reserve(nbPoints);
        std::generate_n(std::back_inserter(sinusoid), nbPoints,[&,idx=0u]() mutable {
            const auto t{idx*step};
            ++idx;
            return std::make_pair(t, std::sin(t)+distribution(generator));});
        return sinusoid;
    }

private:
    std::mt19937_64 generator{std::random_device{}()};
    std::uniform_real_distribution<numerical> distribution{-0.02, 0.02};


};
