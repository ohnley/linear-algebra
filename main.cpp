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
    std::cout << "pre adding col\n";
    std::vector<double> col  = {1,2};
    std::cout << m;

    m.add_col(col, 0);

//    A *= m;

    m.add_row({3, 5}, 2);
    m.add_row({3, 5}, 2);

    std::cout << "post adding col\n" << m;

    m.add_row({3, 5}, 2);

    std::cout << "post adding col\n" << m;

    m.add_col({0, 0, 0, 0, 0}, 2);
    m.add_row({0, 0, 0}, 5);

    m.add_col();
    std::cout << m;
    return 0;
}