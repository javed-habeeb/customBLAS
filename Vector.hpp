#pragma once

//#include <cfloat>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <sys/types.h>
#include <vector>
#include <initializer_list>
#include <cmath>



class Vector {
private:
    std::vector<float> data ;
    //std::size_t Size;
    // std::size_t size() const {
    //     return data.size();
    // }

    // Only child classes can invoke this to grab the raw hardware pointer


public:
    //inherit from std::vector
    Vector() = default;

    Vector(std::initializer_list<float> list) : data(list) {}

    explicit Vector(std::size_t n, const float& value = float{})
    : data(n, value) {}

    std::size_t size() const {
        return data.size();
    }

    void resize(std::size_t n, const float& value = float{}) {
        data.resize(n, value);
    }

    float* get_raw_ptr() { return data.data(); }
    const float* get_raw_ptr() const { return data.data(); }

    void insert(
        std::vector<float>::const_iterator pos,
        std::vector<float>::const_iterator first,
        std::vector<float>::const_iterator last
    ) {
        data.insert(pos, first, last);
    }

    float& operator[](std::size_t index){

        return data[index];
    }

    void push_back(const float& value) {
        data.push_back(value);
    }

    //typecast


    //const float& :- returned element can't be modified from this ref
    //second const is to assure that memeber func doesnt modify the vector

    const float& operator[](std::size_t index) const {
        return data[index];
    }

    Vector operator+(const Vector &addedVector) {
        //make a new vector who stores the calculated result
        Vector result(*this);
        //point this to "result" vector so instead of this->
        //you can use 'result''
        for (size_t i = 0; i <  addedVector.size(); ++i){
            result.data[i] += addedVector.data[i];}

        return result;
    }

    //vector * scalar
    friend Vector operator*(const Vector& vec, const float scalar) {
        Vector result(vec); // Uses your copy constructor
        for (size_t i = 0; i < vec.size(); ++i) {
            result.data[i] *= scalar;
        }
        return result;
    }
    //inorder to get scalar*vector possible (commutativity sucks)
    friend Vector operator*(const float scalar, const Vector& vec) {
        return vec * scalar; // Instantly forwards to the function above
    }


    Vector hadamard(const Vector &addedVector) const {
    if(this->size() != addedVector.size()){
        throw std::invalid_argument("sizes do not match");

    }

      Vector result(*this);

    for (size_t i = 0; i <  addedVector.size(); ++i){
      result.data[i] *= addedVector.data[i];}

    return result;
    }

    float Sum() const{
        float value = 0;
        for(std::size_t i = 0; i < this->size(); i++){
            value += (*this)[i];
        }
        return value;
    }


    float dot(const Vector &v1) const{
    if(v1.size() != this->size()){
        throw std::invalid_argument("sizes do not match");
    }
      float sum = 0;
      for(std::size_t i = 0; i < v1.size(); i++){
          sum +=  v1[i]*(*this)[i];
    }
    return sum;
    }

    float Ln_norm(int n){
        // take abs of each element
        //raise each value to the power of n
        //sum all of those values
        //take the nth root
        float total_sum = 0.0;

        for (float val : this->data) {
            total_sum += std::pow(std::abs(val), n);
        }

        return std::pow(total_sum, 1.0 / n);
        //float result = pow(((pow(std::abs(*this), n)).Sum()),1.0/n);
        //return result;

    }

    friend float dist_euclidean(Vector v1,Vector v2){
        if(v1.size() != v2.size()){
            throw std::invalid_argument("sizes do not match");
        }

        Vector diff = v1 + -1*v2;
        Vector squared = (diff).hadamard(diff);
        return std::sqrt((squared).Sum());

    }

     friend float dist_manhattan(Vector v1,Vector v2){
        if(v1.size() != v2.size()){
            throw std::invalid_argument("sizes do not match");
        }
        float total_sum = 0;
        Vector diff = v1 + -1*v2;
        for (std::size_t i = 0; i < diff.size(); i++) {
            total_sum += std::abs(diff[i]);
        }
        return total_sum;

    }

    Vector normalize(){
        float normalize_value = (*this).Ln_norm(2) ;
        return (*this)*(1.0/normalize_value);
    }

    float max(){
        float* __restrict destination = (*this).get_raw_ptr();
        int total = (*this).size();
        float temp = 0.0;
        for(std::size_t i = 0; i < total; ++i){
            if(destination[i] > temp){
                temp = destination[i];
            }
        }
        return temp;
    }

    float min(){
        float* __restrict destination = (*this).get_raw_ptr();
        int total = (*this).size();
        float temp = (*this)[0];
        for(std::size_t i = 0; i < total; ++i){
            if(destination[i] < temp){
                temp = destination[i];
            }
        }
        return temp;
    }

    int argmax(){
        float max_val = (*this).max();
        float epsilon = 0.00001f; // Tolerance for safe floating-point comparison
        int argmax_value = 0;

        for (size_t i = 0; i < (*this).size(); ++i) {
            // Check if the current element matches your max value within a tiny margin
            if ((*this)[i] >= max_val - epsilon && (*this)[i] <= max_val + epsilon) {
                argmax_value = i;
                break; // Stop at the very first occurrence of the max value
            }
        } return argmax_value;
    }

    float mean(){
        return (*this).Sum()/(*this).size();
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector &v) {
        os << "[";
        for (size_t i = 0; i <  v.size(); ++i) {
            os << v[i];
            if (i != v.size() - 1) {
                os << ", ";
            }
        }
        os << "]";
        return os; // Return the stream to allow chaining (e.g., cout << v << endl;)
    }



    //destructor
    ~Vector(){}

};



