#include <iostream>
#include "MatrixLibrary.h"

int main(){


    std::vector<std::vector<double>> d = {
            {1,2,3,5},
            {0,1,2,2},
            {0,0,0,1},
            {1,1,1,1},
            {3,2,4,1},
            {2,4,6,10}
    };

    std::vector<std::vector<double>> v = {
            {1},
            {2},
            {3}
    };

    Matrix<double> m = Matrix<double>(d);
    Matrix<double> A = Matrix<double>(v);

    std::cout << LinearOperations::row_echelon_form(m);



    return 0;
}