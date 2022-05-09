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
        std::vector<T> operator[](uint32_t) const;
        void operator+=(const Matrix<T>& rhs);

//        Matrix<T>& operator* (const Matrix<T>&);
        Matrix<T>& operator= (const Matrix<T>&);


        // Getters / Setters
        uint32_t get_num_rows() const {return num_rows;}
        uint32_t get_num_cols() const {return num_cols;}

        // Standard matrix operations
        void swap_columns(uint32_t, uint32_t);
        void swap_rows(uint32_t, uint32_t);
        void add_row(std::vector<T>, uint32_t);
        void add_column(std::vector<T>, uint32_t);










};
#include "MatrixLibrary.tpp"

#endif //LINEARLIBRARY_MATRIXLIBRARY_H
