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
class SimpleExponentialSmoothing {
public:
    /**
     *
     * @param aAlpha
     */
    SimpleExponentialSmoothing(const numerical aAlpha) : alpha(aAlpha) {
        // TODO: Add static assert if alpha not in [0,1]
    };

    /**
     *
     * @param lastSignalData
     * @return
     */
    [[nodiscard]] numerical filter(const numerical lastSignalData) {
        if (firstMeasureFlag){
            firstMeasureFlag = false;
            smoothed = lastSignalData;
        }else{
            smoothed = alpha * lastSignalData + (1-alpha) * smoothed;
        }
        return smoothed;
    }

    /**
     *
     */
    void clear() {
        firstMeasureFlag = true;
    }

    virtual ~SimpleExponentialSmoothing() = default;

private:
    const numerical alpha{};
    bool firstMeasureFlag{true};
    numerical smoothed{numerical{}};
};
