#pragma once

#include <cstddef>
#include <initializer_list>
#include <vector>

class Vector {
private:
    std::vector<float> data;

public:
    Vector() = default;
    Vector(std::initializer_list<float> list);
    explicit Vector(std::size_t n, const float& value = float{});

    std::size_t size() const;
    void resize(std::size_t n, const float& value = float{});

    float* get_raw_ptr();
    const float* get_raw_ptr() const;

    void insert(
        std::vector<float>::const_iterator pos,
        std::vector<float>::const_iterator first,
        std::vector<float>::const_iterator last
    );

    float& operator[](std::size_t index);
    const float& operator[](std::size_t index) const;

    void push_back(const float& value);

    Vector operator+(const Vector& addedVector) const;

    friend Vector operator*(const Vector& vec, float scalar);
    friend Vector operator*(float scalar, const Vector& vec);

    Vector hadamard(const Vector& addedVector) const;
    float Sum() const;
    float dot(const Vector& v1) const;
    float Ln_norm(int n) const;

    friend float dist_euclidean(const Vector& v1, const Vector& v2);
    friend float dist_manhattan(const Vector& v1, const Vector& v2);

    Vector normalize() const;
    float max() const;
    float min() const;
    int argmax() const;
    float mean() const;
};
