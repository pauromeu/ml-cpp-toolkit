#include <iostream>

template <typename T = double>
class Dataset {
  public:
    Dataset(std::size_t num_rows, std::size_t num_cols)
        : data_(num_rows * num_cols), num_rows(num_rows), num_cols(num_cols) {
        std::cout << num_rows << std::endl;
        std::cout << num_cols << std::endl;
    }

    template <typename F>
    void fill(F &&visitor) {
        for (std::size_t i = 0; i < num_rows; ++i) {
            for (std::size_t j = 0; j < num_cols; ++j) {
                data_[i * num_cols + j] = visitor(i, j);
            }
        }
    }

  private:
    std::vector<T> data_;
    std::size_t num_rows, num_cols;
};