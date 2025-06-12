#include <iostream>
#include "core/MatrixView.hpp"

template <typename T = double>
class Dataset {
  public:
    Dataset(std::size_t num_rows, std::size_t num_cols)
        : data_(num_rows * num_cols), num_rows_(num_rows), num_cols_(num_cols) {}

    template <typename F>
    void fill(F &&visitor) {
        for (std::size_t i = 0; i < num_rows_; ++i) {
            for (std::size_t j = 0; j < num_cols_; ++j) {
                data_[i * num_cols_ + j] = visitor(i, j);
            }
        }
    }

    MatrixView<T> view() const {
        return {data_.data(), num_rows_, num_cols_};
    }

  private:
    std::vector<T> data_;
    std::size_t num_rows_, num_cols_;
};