#ifndef LINEARLIBRARY_MATRIXLIBRARY_H
#define LINEARLIBRARY_MATRIXLIBRARY_H

#include <vector>

//template<typename T> class Matrix;
//template<typename T> void operator+=(Matrix<T>& lm, Matrix<T>& rm);

template<typename T>
class Matrix {
    private:
        std::vector<std::vector<T>> m_data;
        uint32_t num_rows;
        uint32_t num_cols;

    public:
        explicit Matrix(std::vector<std::vector<T>> m);

        // Operators
        std::vector<T>& operator[](uint32_t);
        Matrix<T>& operator* (const Matrix<T>& rhs) const;


        // Getters / Setters
        uint32_t get_num_rows() {return num_rows;}
        uint32_t get_num_cols() {return num_cols;}



//        friend void operator+=(Matrix<T>& lm, Matrix<T>& rm);

};

#include "MatrixLibrary.tpp"

#endif //LINEARLIBRARY_MATRIXLIBRARY_H
