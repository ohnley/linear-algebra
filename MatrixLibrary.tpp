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
Matrix<T>::Matrix(T def_val, uint32_t rows, uint32_t cols){
    num_rows = rows;
    num_cols = cols;
    num_items = rows*cols;
    m_data = std::vector<T>(num_items, def_val);

}

template <typename T>
std::vector<T> Matrix<T>::operator[](uint32_t row) const {
    auto start_pos = (this->get_num_cols()) * row;
    auto end_pos = start_pos + (this->get_num_col());
    std::vector<T> v = {m_data.begin() + start_pos, m_data.data.begin + end_pos};
    return v;
}

template <typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& rhs){
    if (this->get_num_rows() != rhs.get_num_rows() || this->get_num_cols() != rhs.get_num_cols()) {
        throw std::runtime_error("Matrix sizes do not match");
    }

    for (auto item = 0; item < rhs.get_num_items(); item++) {
        this->set_item(item, rhs.get_item(item) + this->get_item(item));
    }
    return (*this);
}


template <typename T>
Matrix<T>& Matrix<T>::operator+=(const T& rhs){
    for (auto item : this->m_data){
        item += rhs;
    }

    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& rhs){
    if (this->num_rows != rhs.get_num_rows() || this->num_cols != rhs.get_num_cols()) {
        throw std::runtime_error("Matrix sizes do not match");
    }

    for (auto item = 0; item < this->num_cols; item++){
        this->set_item(item, this->get_item(item) - rhs.get_item(item));
    }

    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator-=(const T& rhs){
    for (auto item : this->m_data){
        item -= rhs;
    }

    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& rhs){
    if (this->num_cols not_eq rhs.num_rows) {
        throw std::runtime_error("Matrix sizes do not match");
    }
    std::vector<T> temp_m_data = {};

    // TODO: Can some of this be cached to prevent n*m^2 time?
    for (auto row_index = 0; row_index < this->num_rows; row_index++){
        std::vector<T> row = (*this)[row_index];
        for (auto col_index = 0; col_index < rhs.num_cols; col_index++){
            std::vector<T> col = rhs.get_col(col_index);

            T val = dot_product(row, col);

            temp_m_data.template emplace_back(val);
        }
    }

    this->m_data = temp_m_data;
    this->num_cols = rhs.num_cols;

    return *this;

}


#endif //MATRIX_LIBRARY_DEF