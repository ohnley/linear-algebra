#ifndef LINEARLIBRARY_MATRIXOPERATIONS_H
#define LINEARLIBRARY_MATRIXOPERATIONS_H

#include "MatrixLibrary.h"
#include <cmath>

namespace LinearOperations {

    namespace internal {

        template<typename T>
        void row_echelon_form_helper(Matrix<T>& matrix, size_t row_index, size_t col_index) {
            if(row_index == matrix.get_num_rows()  || col_index == matrix.get_num_cols()  ){
                return;
            }

            // Find the first non-zero entry in the column
            size_t non_zero_item_row_index;
            for (non_zero_item_row_index = row_index; non_zero_item_row_index < matrix.get_num_rows(); non_zero_item_row_index++){
                if (matrix.get_item(non_zero_item_row_index, col_index) != 0){
                    break;
                }
            }

            // If there is a non-zero entry and it is not the first entry in the column, swap those rows
            if (matrix.get_item(non_zero_item_row_index, col_index) != 0 && non_zero_item_row_index != row_index){
                matrix.swap_rows(row_index, non_zero_item_row_index);
            }
            // Otherwise, run the operation from the next column over and return
            else if (non_zero_item_row_index == matrix.get_num_rows()) {
                row_echelon_form_helper(matrix, row_index, col_index +1);
                return;
            }

            // Now the current item at row_index, col_index is non_zero, so we adjust
            for (size_t rows = row_index + 1; rows < matrix.get_num_rows(); rows++){
                auto factor = matrix.get_item(rows, col_index)/matrix.get_item(row_index, col_index);
                for (size_t cols = col_index; cols <matrix.get_num_cols(); cols++){
                    matrix.set_item(rows, cols, (matrix.get_item(rows, cols) - (factor * matrix.get_item(row_index, cols))));
                }
            }

            // normalize the pivot to 1
            auto row_factor = matrix.get_item(row_index, col_index);
            for (size_t cols = col_index; cols < matrix.get_num_cols(); cols++){
                auto new_value = matrix.get_item(row_index, cols) / row_factor;
                matrix.set_item(row_index, cols, new_value);
            }
            row_echelon_form_helper(matrix, row_index + 1, col_index + 1);
            return;
        }

        template <typename T> int sgn(T val) {
            return (T(0) < val) - (val < T(0));
        }
    }

    // Math Functions
    template <typename T>
    T dot_product(std::vector<T> l , std::vector<T> r){
        T x = 0;
        for (int i = 0; i < l.size(); i++){
            x += (l[i] * r[i]);
        }
        return x;
    }

    template <typename T>
    Matrix<T> row_echelon_form(Matrix<T> matrix){
        internal::row_echelon_form_helper(matrix, 0, 0);
        return matrix;
    }

    template <typename T>
    Matrix<T> Identity(size_t rows, size_t cols){
        Matrix<double> i = Matrix<double>(0, rows, cols);
        for (size_t pos = 0; pos < rows*cols; pos+=(cols+1)){
            i.set_item(pos, 1);
        }
        return i;
    }

    template <typename T>
    std::vector<std::pair<size_t, size_t>> get_pivot_positions(Matrix<T>& matrix){
        Matrix<T> ref_matrix = row_echelon_form(matrix);
        std::vector<std::pair<size_t, size_t>> pivot_pos = {};
        size_t row_pos = 0;
        size_t col_pos = 0;
        for (; row_pos < ref_matrix.get_num_rows()  && col_pos < ref_matrix.get_num_cols();){
            if(ref_matrix.get_item(row_pos, col_pos) != 0) {
                pivot_pos.emplace_back(std::pair<size_t, size_t>(row_pos, col_pos));
                col_pos++; row_pos++;
                continue;
            }
            else {col_pos++;}
        }

        return pivot_pos;
    }

    template <typename T>
    std::vector<T> get_pivot_values(Matrix<T>& matrix){
        std::vector<T> pivot_vals = {};
        Matrix<T> ref_matrix = row_echelon_form(matrix);
        size_t row_pos = 0;
        size_t col_pos = 0;
        for (; row_pos < ref_matrix.get_num_rows()  && col_pos < ref_matrix.get_num_cols();){
            if(ref_matrix.get_item(row_pos, col_pos) != 0) {
                pivot_vals.emplace_back(ref_matrix.get_item(row_pos, col_pos));
                col_pos++; row_pos++;
                continue;
            }
            else {col_pos++;}
        }

        return pivot_vals;
    }

    template <typename T>
    T eucledian_norm(Matrix<T>& m){
        T total = 0;
        for (int i = 0; i < m.get_num_rows(); i++){
            for (T element : m[i]){
                total += (element*element);
            }
        }
        return std::sqrt(total);
    }

    template <typename T>
    T eucledian_norm(std::vector<T>& v){
        T total = 0;
        for (T& item : v){
            total += (item * item);
        }
        return std::sqrt(total);
    }

    template <typename T>
    Matrix<T> householder(Matrix<T>& m){
        Matrix<T> col = Matrix(m.get_col(0), m.get_num_rows(), 1);

        T norm = eucledian_norm(col);

        col.set_item(0,0, col[0][0] + (internal::sgn(col[0][0]) * norm));
        std::cout << col;

        Matrix<T> col_matrix = col * col.get_transpose();
        std::cout << col_matrix;
        T dot_prod = eucledian_norm(col) * eucledian_norm(col);

        Matrix<double> i = Identity<double>(col_matrix.get_num_rows(), col_matrix.get_num_cols());

        std::cout << "------sign->" << internal::sgn(col[0][0]) * norm << "-------------\n";

        i -= ((2/ dot_prod) * (col_matrix));

        return i;
    }

    template <typename T>
    std::vector<T> determinant(Matrix<T>& matrix){
        assert(matrix.get_num_cols() == matrix.get_num_rows());

    }




}

#endif //LINEARLIBRARY_MATRIXOPERATIONS_H
