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
class SimpleMovingMedian {
    using Subset = std::deque<numerical>;
public:
    /**
     *
     * @param samplingFrequency
     * @param subsetDuration
     */
    SimpleMovingMedian(const numerical samplingFrequency, const numerical subsetDuration) : subsetSize(
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
        subset.emplace_back(lastSignalData);
        if (std::size(subset) == subsetSize) {
            Subset subsetCopy{};
            std::copy(std::begin(subset), std::end(subset), std::back_inserter(subsetCopy));
            subset.pop_front();
            return computeMedian(std::begin(subsetCopy), std::end(subsetCopy));

        } else {
            mean = (iteration * mean + lastSignalData) / (iteration + 1);
            ++iteration;
            return mean;
        }
    }

    /**
     *
     */
    void clear() {
        subset.clear();
        iteration = 0u;
        mean = 0.0;
    }

private:
    /**
     *
     * @tparam InputIterator
     * @param begin
     * @param end
     * @return
     */

    template<typename InputIterator>
    [[nodiscard]] static numerical
    computeMedian(InputIterator begin, InputIterator end) {
        const auto size{std::distance(begin, end)};
        std::sort(begin, end);
        auto it{begin};
        if ((size % 2) == 0.0) {
            const auto middle{size / 2};
            std::advance(it, middle - 1);
            const auto lhs{*it};
            std::advance(it, 1);
            const auto rhs{*it};
            return (lhs + rhs) / 2;

        } else {
            // Because we already start at 0, we don't have to add 1
            std::advance(it, (size - 1) / 2);
            return *it;
        }
    }

public:
    virtual ~SimpleMovingMedian() = default;

private:
    const std::size_t subsetSize{};
    Subset subset{};
    numerical mean{numerical{}};
    std::size_t iteration{0u};
};
