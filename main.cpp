//#include <iostream>
//#include "Vector.hpp"
#include "Matrix.hpp"


int main(){

    Vector p = {1, 2};
    Vector q = {3 , 4};
    Vector r = {5.09, 6.04, 7.03, 15.09, 1.04, 8.09};
    // std::cout << dist_euclidean(p,q ) << std::endl;

    Matrix TestMatrix = {{1,2,3},{4,5,6},{7,8,9}};
    Matrix identity_matrix = {{1,0,0},{0,1,0},{0,0,1}};
    Matrix notTestMatrix = transpose(TestMatrix);
    Vector normalized_vector = r.normalize();
    std::cout << sq_matrix_full(7, 2);

    return 0;
}

//scalar  * vector and vice versa
//
