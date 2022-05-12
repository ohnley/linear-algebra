//
// Created by John Flatley on 5/8/22.
//

#include <iostream>
#include "MatrixLibrary.h"

int main(){


    std::vector<std::vector<double>> d = {
            {1,2,3},
            {0,1,2}
    };

    std::vector<std::vector<double>> v = {
            {1},
            {2},
            {3}
    };

    Matrix<double> m = Matrix<double>(d);
    Matrix<double> A = Matrix<double>(v);


    std::cout << m;
    m *= A;

    std::cout << m;


    return 0;
}