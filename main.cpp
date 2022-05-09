//
// Created by John Flatley on 5/8/22.
//

#include <iostream>
#include "MatrixLibrary.h"

int main(){
    std::cout << 's';

    std::vector<std::vector<double>> d = {
            {1,2,3,4},
            {5,6,7,8}
    };

    Matrix<double> m = Matrix<double>(d);
    m += m;
    auto r = m[1];

    for (auto val : r){
        std::cout << val << ' ';
    }

    return 0;
}