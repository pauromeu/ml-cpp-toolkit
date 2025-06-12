#pragma once

#include "core/MatrixView.hpp"
#include <iostream>

template <typename T = double>
class IModel {
  public:
    virtual void fit(const MatrixView<T> &X, const std::vector<T> &y) = 0;

    virtual T predict(const std::vector<T> &x) const = 0;

    virtual std::vector<T> predictBatch(const std::vector<std::vector<T>> &X) const {
        std::vector<T> out;
        out.reserve(X.num_rows());
        for (std::size_t i = 0; i < X.num_rows(); i++) {
            const T *row = X.data() + i * X.stride();
            out.emplace_back(predict({row, row + X.num_cols()}));
        }
        return out;
    }

    virtual ~IModel() = default;
};