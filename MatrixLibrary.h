/**
 * @file MatrixLibrary.h
 * @author Ohnley
 * @version 1.0
 *
 * @section DESCRIPTION
 *
 * This is a sample description of the Matrix class. Matrices can be instantiated with any type, and
 * effectively wrap a 2D vector and some helpful manipulator methods into a class.
 *
 */

#ifndef LINEARLIBRARY_MATRIXLIBRARY_H
#define LINEARLIBRARY_MATRIXLIBRARY_H

#include <vector>
#include <iostream>

template <typename T> class Matrix;
template <typename T> bool operator==(const Matrix<T>& lhs, const Matrix<T>& rhs);
template <typename T> bool operator!=(const Matrix<T>& lhs, const Matrix<T>& rhs);
template <typename T> std::ostream& operator<<(std::ostream& os, const Matrix<T>& m);

template<typename T>
class Matrix {

    private:
        std::vector<T> m_data;
        size_t num_rows;
        size_t num_cols;
        size_t num_items;

    public:

        // Constructors
        explicit Matrix(std::vector<std::vector<T>> m);
        Matrix(std::vector<T>, size_t rows, size_t cols);
        Matrix(T def_val, size_t rows, size_t cols);

        // TODO: Implement constructing from external source

        // Operators
        std::vector<T> operator[](int) const;
        Matrix<T>& operator+=(const Matrix<T>& rhs);
        Matrix<T>& operator+=(const T& rhs);
        Matrix<T>& operator-=(const Matrix<T>& rhs);
        Matrix<T>& operator-=(const T& rhs);
        Matrix<T>& operator*=(const Matrix<T>& rhs);
        Matrix<T>& operator*=(const T& rhs);

        friend bool operator== <> (const Matrix<T>& lhs, const Matrix<T>& rhs);
        friend bool operator!= <> (const Matrix<T>& lhs, const Matrix<T>& rhs);
        friend std::ostream& operator<< <>( std::ostream& os, const Matrix<T>& m) ;

        // Getters
        size_t get_num_rows() const {return num_rows;}
        size_t get_num_cols() const {return num_cols;}
        size_t get_num_items() const {return num_items;}
        std::vector<T> get_row(size_t) const;
        std::vector<T> get_col(size_t) const;
        T get_item(size_t row, size_t col) const;
        T get_item(size_t item_pos) const;

        // Setters
        void set_item(size_t pos, T val);
        void set_item(size_t row, size_t col, T val);
        void set_row(size_t, const std::vector<T>&);
        void set_col(size_t, const std::vector<T>&);

        void add_row(const std::vector<T>&, size_t);
        void add_row();
        void add_col(const std::vector<T>&, size_t);
        void add_col();

        void swap_cols(size_t, size_t);
        void swap_rows(size_t, size_t);

        // Matrix specific operations
        Matrix<T> get_transpose() const;
        void transpose_in_place();
        std::vector<T> diagonal() const;
        Matrix<T> sub_matrix(size_t, size_t, size_t, size_t);
        Matrix<T> sub_matrix(size_t, size_t);
};





#include "MatrixLibrary.tpp"

#endif //LINEARLIBRARY_MATRIXLIBRARY_H
