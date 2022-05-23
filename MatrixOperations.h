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
    }

    // Math Functions
    template <typename T>
    T dot_product(std::vector<T> l , std::vector<T> r){
        auto x = 0;
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
    std::vector<T> determinant(Matrix<T>& matrix){
        assert(matrix.get_num_cols() == matrix.get_num_rows());

    }

}

#endif //LINEARLIBRARY_MATRIXOPERATIONS_H
