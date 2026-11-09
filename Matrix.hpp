#pragma once

#include "Vector.hpp"

#include <cstddef>
#include <initializer_list>

class Matrix;

Matrix sq_matrix_full(const int& dimension, const float& value);
Matrix transpose(const Matrix& matrix);
Matrix identity(const int& dimension);
Vector operator*(const Matrix& matrix, const Vector& v);
Vector operator*(const Vector& v, const Matrix& matrix);
Matrix operator*(const Matrix& matrix1, const Matrix& matrix2);
Matrix operator+(const Matrix& m1, const Matrix& m2);
Matrix operator*(float scalar, const Matrix& matrix);

class Matrix {
private:
    Vector data;
    std::size_t rows = 0;
    std::size_t cols = 0;

public:
    Matrix(std::size_t row, std::size_t col);
    Matrix(std::initializer_list<std::initializer_list<float>> list);

    std::size_t rowsize() const;
    std::size_t colsize() const;

    const float& operator()(std::size_t row, std::size_t col) const;
    float& operator()(std::size_t row, std::size_t col);

    Matrix outer_product(const Vector& v1, const Vector& v2) const;

    friend Matrix sq_matrix_full(const int& dimension, const float& value);
    friend Matrix transpose(const Matrix& matrix);
    friend Matrix identity(const int& dimension);

    friend Vector operator*(const Matrix& matrix, const Vector& v);
    friend Vector operator*(const Vector& v, const Matrix& matrix);
    friend Matrix operator*(const Matrix& matrix1, const Matrix& matrix2);
    friend Matrix operator+(const Matrix& m1, const Matrix& m2);
    friend Matrix operator*(float scalar, const Matrix& matrix);
};




