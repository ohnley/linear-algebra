#include <iostream>
#include "MatrixLibrary.h"

int main(){


    std::vector<std::vector<double>> d = {
            {1,2,3,5},
            {3,1,2,2},
            {2,0,0,1}
    };

    std::vector<std::vector<double>> v = {
            {1},
            {2},
            {3}
    };

    Matrix<double> m = Matrix<double>(d);
    Matrix<double> A = Matrix<double>(v);

    std::cout << LinearOperations::row_echelon_form(m);

    for (auto& i : LinearOperations::get_pivot_values(m)){
        std::cout << i << 'l';
    }


    return 0;
}