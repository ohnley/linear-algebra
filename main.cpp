#include <iostream>
#include "MatrixLibrary.h"

int main(){


    std::vector<std::vector<double>> d = {
            {1,2,3,5},
            {3,1,2,2},
            {2,0,0,1}
    };

    std::vector<std::vector<double>> v = {
            {3,2,2},
            {2,3,-2}
    };

//    Matrix<double> m = Matrix<double>(d);
    Matrix<double> A = Matrix<double>(v);

//    std::cout << LinearOperations::row_echelon_form(m);

//    for (auto& i : LinearOperations::get_pivot_values(m)){
//        std::cout << i << 'l';
//    }

    Matrix<double> n = (A.get_transpose() *= A);
    std::cout << (n);

    Matrix<double> hh = LinearOperations::householder(n);

    std::cout << (hh * n);
    return 0;
}