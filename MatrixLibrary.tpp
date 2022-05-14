#ifndef MATRIX_LIBRARY_DEF
#define MATRIX_LIBRARY_DEF

#include "MatrixLibrary.h"
#include "MatrixOperations.h"

// Constructors
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
Matrix<T>::Matrix(std::vector<T> data, size_t rows, size_t cols) :
    m_data(data),
    num_cols(cols),
    num_rows(rows),
    num_items(data.size())
{}

template <typename T>
Matrix<T>::Matrix(T def_val, size_t rows, size_t cols){
    num_rows = rows;
    num_cols = cols;
    num_items = rows*cols;
    m_data = std::vector<T>(num_items, def_val);

}

// Operators
template <typename T>
std::vector<T> Matrix<T>::operator[](int row) const {
    auto start_pos = (this->get_num_cols()) * row;
    auto end_pos = start_pos + (this->get_num_cols());
    std::vector<T> v = {m_data.begin() + start_pos, m_data.begin() + end_pos};
    return v;
}

template <typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& rhs){
    if (this->get_num_rows() != rhs.get_num_rows() || this->get_num_cols() != rhs.get_num_cols()) {
        throw std::runtime_error("Matrix sizes do not match");
    }

    for (size_t item = 0; item < rhs.get_num_items(); item++) {
        this->set_item(item, rhs.get_item(item) + this->get_item(item));
    }
    return (*this);
}


template <typename T>
Matrix<T>& Matrix<T>::operator+=(const T& rhs){
    for (auto& item : this->m_data){
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

            T val = LinearOperations::dot_product(row, col);

            temp_m_data.template emplace_back(val);
        }
    }

    this->m_data = temp_m_data;
    this->num_cols = rhs.num_cols;
    this->num_items = m_data.size();
    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator*=(const T& rhs) {
    for (auto& item : this->m_data){
        item *= rhs;
    }
    return *this;
}

// Friend Operators
template <typename T>
std::ostream& operator<<(std::ostream& os,  const Matrix<T>& m) {
    for (auto r_index = 0; r_index < m.get_num_rows(); r_index++){
        for (auto val : m.get_row(r_index)){
            os << val << ' ';
        }
        os << '\n';
    }
    return os;
}

template <typename T>
bool operator!=(const Matrix<T> &lhs, const Matrix<T> &rhs) {
    if (lhs.get_num_items() != rhs.get_num_items()) return true;
    else{
        for (auto i = 0; i < lhs.get_num_items(); i++){
            if (lhs.get_item(i) != rhs.get_item(i)) return true;
        }
    }
    return false;
}

template <typename T>
bool operator==(const Matrix<T> &lhs, const Matrix<T> &rhs) {
    return !(lhs!=rhs);
}

// Getters
template <typename T>
std::vector<T> Matrix<T>::get_col(size_t col) const{
    std::vector<T> column = {};
    auto index = col;
    while (index < this->get_num_items()){
        column.template emplace_back(m_data[index]);
        index += this->get_num_cols();
    }

    return column;
}

template <typename T>
std::vector<T> Matrix<T>::get_row(size_t row) const {
    return (*this)[row];
}

template <typename T>
T Matrix<T>::get_item(size_t item_pos) const {
    return m_data[item_pos];
}

template <typename T>
T Matrix<T>::get_item(size_t row, size_t col) const {
    return m_data[col + (row * (this->get_num_cols()))];
}

// Setters
template <typename T>
void Matrix<T>::set_item(size_t pos, T val) {
    this->m_data[pos] = val;
}

template <typename T>
void Matrix<T>::set_item(size_t row, size_t col, T val) {
    auto pos = (this->get_num_cols() * row) + col;
    this->m_data[pos] = val;
}

template <typename T>
void Matrix<T>::set_row(size_t row_num, std::vector<T>& new_row){
    if (new_row.size() != this->num_cols) throw std::runtime_error("new row size did not match");
    for (int i = 0; i < this->num_cols; i++){
        m_data[i + ((this->num_cols)*row_num)] = new_row[i];
    }
}

template <typename T>
void Matrix<T>::set_col(size_t col_num, std::vector<T>& new_col){
    if (new_col.size() != this->num_rows) throw std::runtime_error("new col size did not match");
    for (int i = 0; i < this->num_rows; i++){
        m_data[col_num + ((this->num_rows)*i)] = new_col[i];
    }
}

template <typename T>
void Matrix<T>::add_row(const std::vector<T>& new_row, size_t row_num){
    if (new_row.size() != this->num_cols) throw std::runtime_error("new row size did not match");
    size_t insert_pos;
    for (int i = new_row.size() - 1; i >= 0; i--) {
        insert_pos = row_num * (this->num_cols);
        this->m_data.insert(this->m_data.begin() + insert_pos, new_row[i]);
    }

    (this->num_rows) +=1;
    (this->num_items) += new_row.size();
}

template <typename T>
void Matrix<T>::add_row(){
    std::vector<T> zeroes(this->num_cols, 0);
    this->add_row(zeroes, this->num_rows);
}
template <typename T>
void Matrix<T>::add_col(const std::vector<T>& new_col, size_t col_num){
    if (new_col.size() != this->num_rows) throw std::runtime_error("new col size did not match");

    size_t insert_pos;
    for (int i = new_col.size() - 1; i >= 0;  i--) {
        insert_pos =  col_num + (this->num_cols * i);
        this->m_data.insert(this->m_data.begin() + insert_pos, (new_col[i]));
    }

    (this->num_cols)+=1;
    (this->num_items)+=new_col.size();
}

template <typename T>
void Matrix<T>::add_col(){
    std::vector<T> zeroes(this->num_rows, 0);
    this->add_col(zeroes, this->num_cols);
}


template <typename T>
Matrix<T> Matrix<T>::get_transpose() const {
    std::vector<T> new_m_data = {};
    for (size_t col = 0; col < this->num_cols; col++){
        for (T& v : this->get_col(col)){
            new_m_data.emplace_back(v);
        }

    }
    Matrix<T> transposed = Matrix<T>(new_m_data, this->get_num_cols(), this->get_num_rows());

    return transposed;
}

template <typename T>
void Matrix<T>::transpose_in_place() {
    Matrix<T> temp = this->get_transpose();
    this->m_data = temp.m_data;
    this->num_cols = temp.num_cols;
    this->num_rows = temp.num_rows;
}

template <typename T>
std::vector<T> Matrix<T>::diagonal() const{
    size_t smallest_dim = std::min(this->num_cols, this->num_rows);
    std::vector<T> d = {};
    for (size_t i = 0; i < smallest_dim; i++ ) {
        d.emplace_back(this->m_data[i * (this->num_cols + 1)]);
    }
    return d;
}
#endif //MATRIX_LIBRARY_DEF