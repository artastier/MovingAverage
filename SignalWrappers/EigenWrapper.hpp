//
// Created by aastier on 08/10/23.
//

#pragma once

#include<Eigen/Eigen>
template<typename EigenDense>
class EigenWrapper{
public:
    using Scalar = typename EigenDense::Scalar;
public:
    explicit EigenWrapper(const EigenDense& inputArray) : data(inputArray) {}

    [[nodiscard]] EigenDense array(){
        return data.array();
    }

    [[nodiscard]] EigenWrapper operator+(const EigenWrapper& other){
        return EigenWrapper(this->data + other.unwrap());
    }

    [[nodiscard]] EigenWrapper operator-(const EigenWrapper& other){
        return EigenWrapper(this->data - other.unwrap());
    }

    [[nodiscard]] EigenWrapper operator*(const EigenWrapper& other){
        return EigenWrapper(this->array() * other.array());
    }

    [[nodiscard]] EigenDense unwrap(){
        return data;
    }
private:
    EigenDense& data;
};

template<typename Dense>
[[nodiscard]] EigenWrapper<Dense> operator-(const typename EigenWrapper<Dense>::Scalar scalar, EigenWrapper<Dense>& wrapper)
{
    return EigenWrapper<Dense>{Dense::Constant(scalar) - wrapper.unwrap()};
}

template<typename Dense>
[[nodiscard]] EigenWrapper<Dense> operator*(const std::size_t integral, EigenWrapper<Dense>& wrapper)
{
    return EigenWrapper<Dense>{Dense::Constant(integral).array() * wrapper.array()};
}

template<typename Dense>
[[nodiscard]] EigenWrapper<Dense> operator/(EigenWrapper<Dense>& wrapper, const std::size_t integral)
{
    return EigenWrapper<Dense>{wrapper.array() / Dense::Constant(integral).array()};
}
