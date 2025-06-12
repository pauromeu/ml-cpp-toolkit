#include <iostream>

template <typename T = double>
class MatrixView {
  public:
    MatrixView{T * ptr, std::size_t num_rows, std::size_t num_cols, std::size_t stride = 0}
        : data_(ptr),
          num_rows(num_rows),
          num_cols(num_cols),
          stride(stride ? stride : cols) {}

    const T &operator()(std::size_t i, std::size_t j) const { return data_[i * stride + j] }

  private:
    T *data_;
    std::size_t num_rows, num_cols, stride;
};