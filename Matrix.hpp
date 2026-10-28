#pragma once
#include "Vector.hpp"
#include <cstddef>
#include <cstdint>
#include <stdexcept>


//static generator functions go here(because i suck at programming)
class Matrix;
Matrix sq_matrix_full(const int &dimension, const float &value);
Matrix outer_product(const Vector &v1, const Vector &v2);

class Matrix{
    private:
        Vector data;
        std::size_t rows = 0;
        std::size_t cols = 0;

    public:


        Matrix(std::size_t row, std::size_t col) : rows(row), cols(col), data () {
            data.resize(row*col, float{});
        }

        inline std::size_t rowsize() const{
            return rows;
        }
        inline std::size_t colsize() const{
            return cols;
        }
        //  access matrix via index read only
        //const goes at end
        const float& operator()(std::size_t row, std::size_t col) const{
            //return data(row*colsize() + col);
            return data[row*colsize() + col];
        }

        float& operator()(std::size_t row, std::size_t col) {
            //return data(row*colsize() + col);
            return data[row*colsize() + col];
        }



        Matrix(std::initializer_list<std::initializer_list<float>> list)
        : //rows(list.size()),
        //*cols(rows > 0 ? list.begin()->size() : 0),
        data()
        {   rows = list.size();
            cols = rows > 0 ? list.begin()->size() : 0;
            for (const auto& row : list) {
                if (row.size() != cols) {
                    throw std::invalid_argument(
                        "All matrix rows must have the same number of elements"
                    );
                }

                for (const auto& value : row) {
                    data.push_back(value);
                }
            }
        }




        //matrix * matrix

        friend Matrix operator*(const Matrix &matrix1, const Matrix &matrix2){

            Matrix temp(matrix1.rows, matrix2.cols) ;
            for (float i = 0;i < (float)matrix1.rows; ++i) {
                for (float j = 0; j < (float)matrix2.cols; ++j) {
                    float sum = float{}; //accumulated in temp var for speed
                    for (float k = 0; k < (float)matrix1.cols; ++k) {
                        sum  += matrix1(i, k) * matrix2(k, j);
                    }
                    temp(i, j) = sum;
                }
            }
            return temp;


        }

        //operation overloads
        //Matrix * Vector : traversing the matrix
        friend Vector operator*(const Matrix &matrix ,const Vector &v){
            if(matrix.cols != v.size()){
                throw std::invalid_argument("sizes do not match");
            }

            Vector result;
            result.resize(matrix.rows, 0);

            for (std::size_t i  = 0; i < matrix.rows; ++i) {
                for (std::size_t j = 0; j < matrix.cols; ++j) {
                    result[i] += matrix(i, j) * v[j] ;
                }

            }

            return result;
        }

        //Vector * matrix : traversing the vector
        friend Vector operator*(const Vector &v,const Matrix &matrix){
             if(v.size() != matrix.rows){
                 throw std::invalid_argument("sizes do not match");
            }

            Vector result;
            result.resize(matrix.cols,0);
            for (std::size_t i= 0; i < matrix.cols; ++i) {
                for (std::size_t j = 0; j < matrix.rows; ++j) {
                    result[j] += matrix(i, j) * v[i] ;
                }

            }
            return result;

        }

        //transpose
        friend Matrix transpose(const Matrix &matrix){
            Matrix temp(matrix.rows, matrix.cols);
            for (std::uint32_t i  = 0; i < matrix.cols; ++i) {
                for (std::size_t j = 0; j < matrix.rows; ++j) {
                    temp(i, j) = matrix(j, i);
                }

            }
            return temp;
        }

        //trial to see if this is correct and hope it doesnt crash this function

         friend Matrix operator+(const Matrix &m1, const Matrix &m2){
            if(m1.colsize()!= m2.colsize()){
                throw std::invalid_argument("cant do that with mismatched column sizes, mate");
            }
            if(m1.rowsize()!= m2.rowsize()){
                throw std::invalid_argument("cant do that with mismatched row sizes");
            }


            Matrix temp(m1.rows, m2.cols);
            const std::size_t total = m1.rows * m1.cols;

            float* __restrict dest = temp.data.get_raw_ptr();

            const float* __restrict source1 = m1.data.get_raw_ptr();
            const float* __restrict source2 = m2.data.get_raw_ptr();

            for(std::size_t i = 0; i < total; ++i){
                dest[i] = source1[i] + source2[i];
            }
            return temp;
        }

        //scalar * matrix
        friend Matrix operator*(const float& scalar, const Matrix &matrix){
            const std::size_t total = matrix.rows * matrix.cols;

            Matrix temp(matrix.rows, matrix.cols);
            float* __restrict dest = temp.data.get_raw_ptr();
            const float* __restrict source = matrix.data.get_raw_ptr();

            for(std::size_t i = 0; i < total; ++i){
                dest[i] = scalar*source[i];
            }
            return temp;
        }


        Matrix outer_product(const Vector &v1, const Vector &v2){

            if(v1.size() != v2.size()){
                std::invalid_argument("Vector Sizes do not match");
            }

            Matrix temp(v1.size(), v2.size());


            for(std::size_t i = 0; i < v1.size(); ++i){
                for(std::size_t j = 0; j < v1.size(); ++j){
                    temp(i, j) = v1[i]*v2[j];
                }
            } return temp;
        }

        /**
         * @brief Creates a square matrix populated with a single uniform value.
         * @param dimension The width and height of the square matrix.
         * @param value The float value to fill every cell with.
         * @return A new initialized Matrix object.
         */

        friend Matrix sq_matrix_full(const int &dimension, const float &value){
            Matrix temp(dimension, dimension);
            float* __restrict dest = temp.data.get_raw_ptr();
            std::size_t total = dimension*dimension;

            for(std::size_t i = 0; i < total; ++i){
                dest[i] = value;
            }
            return temp;
        }
        //TODO: fill these
        friend Matrix identity(const int &dimension){
            Matrix temp = sq_matrix_full(dimension, 0 );

            for(std::size_t i = 0; i < dimension; ++i){

            }
            return temp;
        }
        //TODO : complete it
        //get row into a vector
        /*friend Vector get_row(const Matrix &matrix,const int &selected_row){
            //matrix.get_row(2) should get you the third row
            //  *   *   *
            //  *   *   *
            //  *   *   *
            Vector temp;
            temp.resize(matrix.cols, 0);
            //selected_row  * cols + i
            const int* row_start_ptr = matrix.data.get_raw_ptr() +

            for(std::size_t i = 0; i < matrix.cols; ++i){
                ;
            }
        }*/




        friend std::ostream& operator<<(std::ostream& os, const Matrix &v) {
            for (std::size_t row = 0; row <  v.rowsize() ; row++) {
                os << "[";
                for (std::size_t col = 0; col <  v.colsize() ; col++){
                    os << v(row,col);
                    if (col != v.colsize() - 1) {
                        os << ", ";
                    }
                }
                os << ", ]\n";
            }
            return os; // Return the stream to allow chaining (e.g., cout << v << endl;)
        }







        ~Matrix(){};
};






