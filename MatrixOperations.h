#ifndef LINEARLIBRARY_MATRIXOPERATIONS_H
#define LINEARLIBRARY_MATRIXOPERATIONS_H

#include "MatrixLibrary.h"

namespace LinearOperations {

    // Math Functions
    template <typename T>
    T dot_product(std::vector<T> l , std::vector<T> r){
        auto x = 0;
        for (int i = 0; i < l.size(); i++){
            x += (l[i] * r[i]);
        }
        return x;
    }
}

#endif //LINEARLIBRARY_MATRIXOPERATIONS_H
