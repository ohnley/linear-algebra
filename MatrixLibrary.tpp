#ifndef MATRIX_LIBRARY_DEF
#define MATRIX_LIBRARY_DEF
#include "MatrixLibrary.h"

template <typename T>
Matrix<T>::Matrix(const std::vector<std::vector<T>> m){
    assert(m.size() > 0);
    num_rows = m.size();
    num_cols = m[0].size();

    for (auto row : m){
        for (T val: row){
            m_data.push_back(val);
        }
    }
    num_items = m_data.size();
}

template <typename T>
std::vector<T>& Matrix<T>::operator[](uint32_t index) {
    return m_data[index];
}

template <typename T>
std::vector<T> Matrix<T>::operator[](uint32_t row) const {
    auto start_pos = row * (this->get_num_cols());
    auto end_post = start_pos + (this->get_num_cols());
    return m_data[row];
}

template <typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& rhs){
    if (this->get_num_rows() != rhs.get_num_rows() || this->get_num_cols() != rhs.get_num_cols()) {
        throw std::runtime_error("Matrix sizes do not match");
    }

    for (auto item = 0; item < rhs.get_num_items(); item++) {
            (*this)[item] += rhs[item];
    }
    return (*this);
}


template <typename T>
Matrix<T>& Matrix<T>::operator+=(const T& rhs){
    for (auto item : this->m_data){
        item += rhs;
    }

    return (*this);
}
#endif //MATRIX_LIBRARY_DEF