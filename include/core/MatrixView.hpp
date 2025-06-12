#include <iostream>

template <typename T = double>
class MatrixView {
  public:
    MatrixView(T * ptr, std::size_t num_rows, std::size_t num_cols, std::size_t stride = 0)
        : data_(ptr),
          num_rows_(num_rows),
          num_cols_(num_cols),
          stride_(stride ? stride : num_cols) {}

    const T &operator()(std::size_t i, std::size_t j) const { return data_[i * stride_ + j]; }

    const std::size_t num_rows() const { return num_rows_; }
    const std::size_t num_cols() const { return num_cols_; }
    const std::size_t stride() const { return stride_; }
    const T *data() const { return data; }

  private:
    T *data_;
    std::size_t num_rows_, num_cols_, stride_;
};