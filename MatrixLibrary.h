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

//template<typename T> class Matrix;
//template<typename T> void operator+=(Matrix<T>& lm, Matrix<T>& rm);

template<typename T>
class Matrix {

    private:
        std::vector<T> m_data;
        uint32_t num_rows;
        uint32_t num_cols;
        uint64_t num_items;

    public:

        // Constructors
        explicit Matrix(std::vector<std::vector<T>> m);
        Matrix(T def_val, uint32_t rows, uint32_t cols);

        // TODO: Implement constructing from external source

        // Operators
        std::vector<T> operator[](uint32_t) const;
        Matrix<T>& operator+=(const Matrix<T>& rhs);
        Matrix<T>& operator+=(const T& rhs);
        Matrix<T>& operator-=(const Matrix<T>& rhs);
        Matrix<T>& operator-=(const T& rhs);
        Matrix<T>& operator*=(const Matrix<T>& rhs);
        Matrix<T>& operator*=(const T& rhs);

        friend bool operator==(const Matrix<T>& lhs, const Matrix<T>& rhs);
        friend bool operator!=(const Matrix<T>& lhs, const Matrix<T>& rhs);

        // Getters
        uint32_t get_num_rows() const {return num_rows;}
        uint32_t get_num_cols() const {return num_cols;}
        uint64_t get_num_items() const {return num_items;}
        std::vector<T> get_row(uint32_t);
        std::vector<T> get_col(uint32_t);
        T get_item(uint32_t row, uint32_t col) const;
        T get_item(uint64_t item_pos) const;


        // Setters
        void swap_columns(uint32_t, uint32_t);
        void swap_rows(uint32_t, uint32_t);
        void add_row(std::vector<T>, uint32_t);
        void add_column(std::vector<T>, uint32_t);
        void set_item(uint64_t pos, T val);
        void set_item(uint32_t row, uint32_t col, T val);
        void set_row(std::vector<T>, uint32_t);
        void set_col(std::vector<T>, uint32_t);

        Matrix<T> t() const;
        std::vector<T> diagonal() const;

};



// Math Functions
template <typename T>
T dot_product(std::vector<T>, std::vector<T>);


#include "MatrixLibrary.tpp"

#endif //LINEARLIBRARY_MATRIXLIBRARY_H
