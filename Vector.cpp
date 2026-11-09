#include "Vector.hpp"

#include <stdexcept>
#include <cmath>

Vector::Vector(std::initializer_list<float> list)
: data(list) {}

Vector::Vector(std::size_t n, const float& value)
: data(n, value) {}

std::size_t Vector::size() const {
    return data.size();
}

void Vector::resize(std::size_t n, const float& value) {
    data.resize(n, value);
}

float* Vector::get_raw_ptr() {
    return data.data();
}

const float* Vector::get_raw_ptr() const {
    return data.data();
}

void Vector::insert(
    std::vector<float>::const_iterator pos,
    std::vector<float>::const_iterator first,
    std::vector<float>::const_iterator last
) {
    data.insert(pos, first, last);
}

float& Vector::operator[](std::size_t index) {
    return data[index];
}

const float& Vector::operator[](std::size_t index) const {
    return data[index];
}

void Vector::push_back(const float& value) {
    data.push_back(value);
}

Vector Vector::operator+(const Vector& addedVector) const {
    if (size() != addedVector.size()) {
        throw std::invalid_argument("sizes do not match");
    }

    Vector result(*this);
    for (std::size_t i = 0; i < size(); ++i) {
        result.data[i] += addedVector.data[i];
    }
    return result;
}

Vector operator*(const Vector& vec, float scalar) {
    Vector result(vec);
    for (std::size_t i = 0; i < vec.size(); ++i) {
        result.data[i] *= scalar;
    }
    return result;
}

Vector operator*(float scalar, const Vector& vec) {
    return vec * scalar;
}

Vector Vector::hadamard(const Vector& addedVector) const {
    if (size() != addedVector.size()) {
        throw std::invalid_argument("sizes do not match");
    }

    Vector result(*this);
    for (std::size_t i = 0; i < size(); ++i) {
        result.data[i] *= addedVector.data[i];
    }
    return result;
}

float Vector::Sum() const {
    float value = 0.0f;
    for (std::size_t i = 0; i < size(); ++i) {
        value += data[i];
    }
    return value;
}

float Vector::dot(const Vector& v1) const {
    if (v1.size() != size()) {
        throw std::invalid_argument("sizes do not match");
    }

    float sum = 0.0f;
    for (std::size_t i = 0; i < size(); ++i) {
        sum += v1[i] * (*this)[i];
    }
    return sum;
}

float Vector::Ln_norm(int n) const {
    if (n <= 0) {
        throw std::invalid_argument("norm order must be positive");
    }

    float total_sum = 0.0f;
    for (float val : data) {
        total_sum += std::pow(std::abs(val), n);
    }
    return std::pow(total_sum, 1.0f / n);
}

float dist_euclidean(const Vector& v1, const Vector& v2) {
    if (v1.size() != v2.size()) {
        throw std::invalid_argument("sizes do not match");
    }

    Vector diff = v1 + (-1.0f * v2);
    return std::sqrt(diff.hadamard(diff).Sum());
}

float dist_manhattan(const Vector& v1, const Vector& v2) {
    if (v1.size() != v2.size()) {
        throw std::invalid_argument("sizes do not match");
    }

    float total_sum = 0.0f;
    Vector diff = v1 + (-1.0f * v2);
    for (std::size_t i = 0; i < diff.size(); ++i) {
        total_sum += std::abs(diff[i]);
    }
    return total_sum;
}

Vector Vector::normalize() const {
    const float norm = Ln_norm(2);
    if (norm == 0.0f) {
        throw std::domain_error("cannot normalize a zero vector");
    }
    return (*this) * (1.0f / norm);
}

float Vector::max() const {
    if (data.empty()) {
        throw std::domain_error("max of an empty vector");
    }

    float result = data[0];
    for (std::size_t i = 1; i < size(); ++i) {
        if (data[i] > result) result = data[i];
    }
    return result;
}

float Vector::min() const {
    if (data.empty()) {
        throw std::domain_error("min of an empty vector");
    }

    float result = data[0];
    for (std::size_t i = 1; i < size(); ++i) {
        if (data[i] < result) result = data[i];
    }
    return result;
}

int Vector::argmax() const {
    if (data.empty()) {
        throw std::domain_error("argmax of an empty vector");
    }

    const float max_value = max();
    for (std::size_t i = 0; i < size(); ++i) {
        if (data[i] == max_value) {
            return static_cast<int>(i);
        }
    }
    return 0;
}

float Vector::mean() const {
    if (data.empty()) {
        throw std::domain_error("mean of an empty vector");
    }
    return Sum() / static_cast<float>(size());
}

