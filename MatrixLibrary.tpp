
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
Matrix<T>& operator* (const Matrix<T>& rhs) const {

}

template <typename T>
void operator+=(Matrix<T>& lm,  Matrix<T>& rm) {

    if (lm.get_num_rows() != rm.get_num_rows() || lm.get_num_cols() != lm.get_num_cols()) {
        throw std::runtime_error("Matrices sizes do not match");
    }

    for (auto row = 0; row < rm.get_num_rows(); row++) {
        for (auto col = 0; col < rm.get_num_cols(); col++) {
            lm[row][col] += rm[row][col];
        }
    }
}