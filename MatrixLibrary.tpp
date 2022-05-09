#ifndef MATRIX_LIBRARY_DEF
#define MATRIX_LIBRARY_DEF
#include "MatrixLibrary.h"

template <typename T>
Matrix<T>::Matrix(const std::vector<std::vector<T>> m)
    : m_data(m)
    , num_rows(m.size())
    , num_cols(m[0].size())
{
}

template <typename T>
std::vector<T>& Matrix<T>::operator[](uint32_t index) {
    return m_data[index];
}

template <typename T>
std::vector<T> Matrix<T>::operator[](uint32_t index) const {
    return m_data[index];
}


template <typename T>
void Matrix<T>::operator+=(const Matrix<T>& rhs){
    if (this->get_num_rows() != rhs.get_num_rows() || this->get_num_cols() != rhs.get_num_cols()) {
        throw std::runtime_error("Matrix sizes do not match");
    }

    for (auto row = 0; row < rhs.get_num_rows(); row++) {
        for (auto col = 0; col < rhs.get_num_cols(); col++) {
            (*this)[row][col] += rhs[row][col];
        }
    }
}

#endif //MATRIX_LIBRARY_DEF