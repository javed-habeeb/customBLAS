#include "Matrix.hpp"

#include <stdexcept>

Matrix::Matrix(std::size_t row, std::size_t col)
    : data(row * col, 0.0f), rows(row), cols(col) {}

Matrix::Matrix(std::initializer_list<std::initializer_list<float>> list)
    : data(), rows(list.size()), cols(list.size() == 0 ? 0 : list.begin()->size()) {
    for (const auto& row : list) {
        if (row.size() != cols) {
            throw std::invalid_argument(
                "All matrix rows must have the same number of elements"
            );
        }

        for (float value : row) {
            data.push_back(value);
        }
    }
}

std::size_t Matrix::rowsize() const {
    return rows;
}

std::size_t Matrix::colsize() const {
    return cols;
}

const float& Matrix::operator()(std::size_t row, std::size_t col) const {
    return data[row * cols + col];
}

float& Matrix::operator()(std::size_t row, std::size_t col) {
    return data[row * cols + col];
}

Matrix operator*(const Matrix& matrix1, const Matrix& matrix2) {
    if (matrix1.cols != matrix2.rows) {
        throw std::invalid_argument("matrix dimensions do not match for multiplication");
    }

    Matrix result(matrix1.rows, matrix2.cols);
    for (std::size_t i = 0; i < matrix1.rows; ++i) {
        for (std::size_t j = 0; j < matrix2.cols; ++j) {
            float sum = 0.0f;
            for (std::size_t k = 0; k < matrix1.cols; ++k) {
                sum += matrix1(i, k) * matrix2(k, j);
            }
            result(i, j) = sum;
        }
    }
    return result;
}

Vector operator*(const Matrix& matrix, const Vector& v) {
    if (matrix.cols != v.size()) {
        throw std::invalid_argument("sizes do not match");
    }

    Vector result(matrix.rows, 0.0f);
    for (std::size_t i = 0; i < matrix.rows; ++i) {
        for (std::size_t j = 0; j < matrix.cols; ++j) {
            result[i] += matrix(i, j) * v[j];
        }
    }
    return result;
}

Vector operator*(const Vector& v, const Matrix& matrix) {
    if (v.size() != matrix.rows) {
        throw std::invalid_argument("sizes do not match");
    }

    Vector result(matrix.cols, 0.0f);
    for (std::size_t j = 0; j < matrix.cols; ++j) {
        for (std::size_t i = 0; i < matrix.rows; ++i) {
            result[j] += v[i] * matrix(i, j);
        }
    }
    return result;
}

Matrix transpose(const Matrix& matrix) {
    Matrix result(matrix.cols, matrix.rows);
    for (std::size_t i = 0; i < matrix.rows; ++i) {
        for (std::size_t j = 0; j < matrix.cols; ++j) {
            result(j, i) = matrix(i, j);
        }
    }
    return result;
}

Matrix operator+(const Matrix& m1, const Matrix& m2) {
    if (m1.rows != m2.rows || m1.cols != m2.cols) {
        throw std::invalid_argument("matrix dimensions do not match for addition");
    }

    Matrix result(m1.rows, m1.cols);
    for (std::size_t i = 0; i < m1.rows; ++i) {
        for (std::size_t j = 0; j < m1.cols; ++j) {
            result(i, j) = m1(i, j) + m2(i, j);
        }
    }
    return result;
}

Matrix operator*(float scalar, const Matrix& matrix) {
    Matrix result(matrix.rows, matrix.cols);
    for (std::size_t i = 0; i < matrix.rows; ++i) {
        for (std::size_t j = 0; j < matrix.cols; ++j) {
            result(i, j) = scalar * matrix(i, j);
        }
    }
    return result;
}

Matrix Matrix::outer_product(const Vector& v1, const Vector& v2) const {
    Matrix result(v1.size(), v2.size());
    for (std::size_t i = 0; i < v1.size(); ++i) {
        for (std::size_t j = 0; j < v2.size(); ++j) {
            result(i, j) = v1[i] * v2[j];
        }
    }
    return result;
}

Matrix sq_matrix_full(const int& dimension, const float& value) {
    if (dimension < 0) {
        throw std::invalid_argument("dimension cannot be negative");
    }

    Matrix result(static_cast<std::size_t>(dimension),
                  static_cast<std::size_t>(dimension));
    for (std::size_t i = 0; i < result.rows; ++i) {
        for (std::size_t j = 0; j < result.cols; ++j) {
            result(i, j) = value;
        }
    }
    return result;
}

Matrix identity(const int& dimension) {
    if (dimension < 0) {
        throw std::invalid_argument("dimension cannot be negative");
    }

    Matrix result(static_cast<std::size_t>(dimension),
                  static_cast<std::size_t>(dimension));
    for (std::size_t i = 0; i < result.rows; ++i) {
        result(i, i) = 1.0f;
    }
    return result;
}
