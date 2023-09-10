#include <iostream>
#include "NoisySinusoid.hpp"
#include "MovingAverageTest.hpp"
#include "gnuplot_i.hpp"
using numerical = double;
using NoisySinusoidType = NoisySinusoid<numerical>;
using MovingAverageTestType = MovingAverageTest<numerical>;
using Trajectory = NoisySinusoidType::Trajectory;
constexpr static numerical samplingFrequency{100.0};
constexpr static numerical signalDuration{10.0};
constexpr static numerical subsetDuration{0.50};
int main() {
    Trajectory sinusoid{(NoisySinusoidType{}).generateTrajectory(signalDuration, samplingFrequency)};
    MovingAverageTestType movingAverage{samplingFrequency,subsetDuration};
    Trajectory filteredSinusoid{movingAverage.filterTrajectory(sinusoid)};
    Gnuplot figure("");
    figure.plot_xy<numerical>(sinusoid, "Noisy Sinusoid");
    figure.plot_xy<numerical>(filteredSinusoid, "Moving Average Filtered Sinusoid");
    std::cout << std::endl << "Press ENTER to continue in the terminal:" << std::endl;
    std::cin.get();
    return EXIT_SUCCESS;
}
