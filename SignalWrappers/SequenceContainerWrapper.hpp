//
// Created by aastier on 14/10/23.
//

#pragma once

#include <cstddef>
#include <algorithm>

template<typename SequenceContainer>
class SequenceContainerWrapper {
public:
    using ValueType = typename SequenceContainer::value_type;

public:
    // Constructor
    explicit SequenceContainerWrapper(SequenceContainer &aSequenceContainer) : data(aSequenceContainer) {}

    // Add an element to the end of the vector
    void push_back(const ValueType &value) {
        data.push_back(value);
    }

    // Emplace back an element
    void emplace_back(const ValueType &value) {
        data.emplace_back(value);
    }

    // Get the size of the vector
    [[nodiscard]] std::size_t size() const {
        return std::size(data);
    }

    // Access elements by index
    [[nodiscard]] ValueType &operator[](std::size_t index) {
        return data[index];
    }

    // Const version to access elements by index
    [[nodiscard]] const ValueType &operator[](std::size_t index) const {
        return data[index];
    }

    // Iterate over the elements
    [[nodiscard]] typename SequenceContainer::iterator begin() {
        return std::begin(data);
    }

    [[nodiscard]] typename SequenceContainer::iterator end() {
        return std::end(data);
    }

    // Const versions for iteration
    [[nodiscard]] typename SequenceContainer::const_iterator begin() const {
        return std::cbegin(data);
    }

    [[nodiscard]] typename SequenceContainer::const_iterator end() const {
        return std::cend(data);
    }

    [[nodiscard]] SequenceContainerWrapper operator+(const SequenceContainerWrapper &other) {
        std::for_each(this->begin(), this->end(), [it = std::begin(other)](auto &value) mutable {
            value = value + *it;
            std::advance(it, 1);
        });
        return SequenceContainerWrapper(this->data);
    }

    [[nodiscard]] SequenceContainerWrapper operator-(const SequenceContainerWrapper &other) {
        std::for_each(this->begin(), this->end(), [it = std::begin(other)](auto &value) mutable {
            value = value - *it;
            std::advance(it, 1);
        });
        return SequenceContainerWrapper(this->data);
    }

    [[nodiscard]] SequenceContainerWrapper operator*(const SequenceContainerWrapper &other) {
        std::for_each(this->begin(), this->end(), [it = std::begin(other)](auto &value) mutable {
            value = value * (*it);
            std::advance(it, 1);
        });
        return SequenceContainerWrapper(this->data);
    }

    [[nodiscard]] SequenceContainer unwrap() {
        return data;
    }

private:
    SequenceContainer &data;

};

template<typename Sequence>
[[nodiscard]] SequenceContainerWrapper<Sequence>
operator/(SequenceContainerWrapper<Sequence> &sequenceWrapper, const std::size_t integral) {
    std::for_each(std::begin(sequenceWrapper), std::end(sequenceWrapper), [integral](auto &value) {
        value = value / integral;
    });
    return sequenceWrapper;
}

template<typename Sequence>
[[nodiscard]] SequenceContainerWrapper<Sequence>
operator*(const std::size_t integral, SequenceContainerWrapper<Sequence> &sequenceWrapper) {
    std::for_each(std::begin(sequenceWrapper), std::end(sequenceWrapper), [integral](auto &value) {
        value = integral * value;
    });
    return sequenceWrapper;
}

template<typename Sequence>
[[nodiscard]] SequenceContainerWrapper<Sequence>
operator-(const typename SequenceContainerWrapper<Sequence>::ValueType scalar,
          SequenceContainerWrapper<Sequence> &sequenceWrapper) {
    std::for_each(std::begin(sequenceWrapper), std::end(sequenceWrapper), [scalar](auto &value) {
        value = scalar - value;
    });
    return SequenceContainerWrapper<Sequence>(sequenceWrapper);
}