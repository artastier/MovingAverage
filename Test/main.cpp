#include <iostream>
#include "NoisySinusoid.hpp"
#include "TemporalSmootherTest.hpp"
#include "../MovingAverageFilters/SMA.hpp"
#include "../MovingAverageFilters/SimpleExponentialSmoothing.hpp"
#include "../MovingAverageFilters/DoubleExponentialSmoothing.hpp"
#include "gnuplot_i.hpp"
using numerical = double;
using Dur = std::chrono::duration<numerical>;
using NoisySinusoidType = NoisySinusoid<numerical>;

using SMAType = Smoother::SMA<numerical>;
using SESType = Smoother::SimpleExponentialSmoothing<numerical>;
using DESType = Smoother::DoubleExponentialSmoothing<numerical>;

using SMATestType = Test::TemporalSmootherTest<SMAType,numerical>;
using SESTestType = Test::TemporalSmootherTest<SESType,numerical>;
using DESTestType = Test::TemporalSmootherTest<DESType,numerical>;

using Trajectory = NoisySinusoidType::Trajectory;

constexpr static numerical samplingFrequency{100.0};
constexpr static Dur subsetDuration{0.50};
constexpr static numerical signalDuration{10.0};
constexpr static double alpha{0.08};
constexpr static double beta{0.0084};


int main() {
    Trajectory sinusoid{(NoisySinusoidType{}).generateTrajectory(signalDuration, samplingFrequency)};

    SMAType sma{samplingFrequency,subsetDuration};
    SESType ses{alpha};
    DESType des{alpha, beta};

    SMATestType smaTest{sma};
    SESTestType sesTest{ses};
    DESTestType desTest{des};

    Trajectory smaSinusoid{smaTest.filterTrajectory(sinusoid)};
    Trajectory sesSinusoid{sesTest.filterTrajectory(sinusoid)};
    Trajectory desSinusoid{desTest.filterTrajectory(sinusoid)};

    Gnuplot figure("");
    figure.plot_xy<numerical>(sinusoid, "Noisy Sinusoid");

    figure.plot_xy<numerical>(smaSinusoid, " Simple Moving Average");
    figure.plot_xy<numerical>(sesSinusoid, " Simple Exponential Smoothing");
    figure.plot_xy<numerical>(desSinusoid, " Double Exponential Smoothing");

    std::cout << std::endl << "Press ENTER to continue in the terminal:" << std::endl;
    std::cin.get();

    return EXIT_SUCCESS;
}
