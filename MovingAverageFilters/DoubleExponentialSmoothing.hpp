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
class DoubleExponentialSmoothing {
public:
    /**
     *
     * @param aAlpha
     * @param aBeta
     */
    DoubleExponentialSmoothing(const numerical aAlpha, const numerical aBeta) : alpha(aAlpha), beta(aBeta) {
        // TODO: Add static assert if alpha not in [0,1]
        // TODO: Add static assert if beta not in [0,1]

    };

    /**
     *
     * @param lastSignalData
     * @return
     */
    [[nodiscard]] numerical filter(const numerical lastSignalData) {
        if (initMeasureFlags[0]) {
            initMeasureFlags[0] = false;
            smoothed = lastSignalData;
        } else if (initMeasureFlags[1]){
            initMeasureFlags[1] = false;
            trend = lastSignalData - smoothed;
            smoothed = alpha * lastSignalData + (1- alpha) * (smoothed + trend);
        }
        else{
            const auto previousSmoothed{smoothed};
            smoothed = alpha * lastSignalData + (1 - alpha) * (previousSmoothed + trend);
            trend = beta * (smoothed - previousSmoothed) + (1 - beta) * trend;
        }
        return smoothed;
    }

    /**
     *
     */
    void clear() {
        initMeasureFlags[0] = true;
        initMeasureFlags[1] = true;
    }

    virtual ~DoubleExponentialSmoothing() = default;

private:
    const numerical alpha{};
    const numerical beta{};
    std::vector<bool> initMeasureFlags{true, true};
    numerical smoothed{numerical{}};
    numerical trend{numerical{}};
};
