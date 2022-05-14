#ifndef LINEARLIBRARY_MATRIXOPERATIONS_H
#define LINEARLIBRARY_MATRIXOPERATIONS_H

#include "MatrixLibrary.h"

namespace LinearOperations {

    namespace internal {

        template<typename T>
        void row_echelon_form_helper(Matrix<T>& matrix, size_t position) {
            if (matrix.get_item(position, position) != 0) {

                // Normalize first row
                std::vector<T> current_row = matrix.get_row(position);
                T first_item = current_row[position];
                for (auto& i : current_row){
                    i = i/first_item;
                }
                matrix.set_row(position, current_row);

                // Normalize lower rows
                for (size_t row_index = position + 1; row_index < matrix.get_num_rows(); row_index++) {
                    std::vector<T> lower_row = matrix.get_row(row_index);
                    T first_item_lower = lower_row[position];
                    for (size_t i = position; i < matrix.get_num_cols(); i++){
                        lower_row[i] = lower_row[i] - (first_item_lower * current_row[i]);
                    }
                    matrix.set_row(row_index, lower_row);
                }
            }

            else if (matrix.get_item(position, position) == 0 && position < matrix.get_num_rows() - 1){
                std::vector<T> col = matrix.get_col(position);
                size_t col_index;
                for (col_index = position; col_index < col.size(); col_index++){
                    if (col[col_index] > 0){
                        break;
                    }
                }
                if (col[col_index] == 0) {return;}
                else if (col[col_index] != 0 ) {
                    matrix.swap_rows(position, position + 1);
                    row_echelon_form_helper(matrix, position);
                    return;
                }
            }
            else {
                return;
            }

            if (position >= (matrix.get_num_rows() - 1) || position >= (matrix.get_num_cols() - 1) ) {
                return;
            } else {
                row_echelon_form_helper(matrix, position + 1);
                return;
            }
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
        internal::row_echelon_form_helper(matrix, 0);
        return matrix;
    }

}

#endif //LINEARLIBRARY_MATRIXOPERATIONS_H
