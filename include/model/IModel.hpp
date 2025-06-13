#pragma once

#include "core/MatrixView.hpp"
#include <iostream>

template <typename T = double>
class IModel {
  public:
    virtual void fit(const MatrixView<T> &X, const std::vector<T> &y) = 0;

    virtual T predict(const std::vector<T> &x) const = 0;

    virtual std::vector<T> predictBatch(const MatrixView<T> &X) const = 0;

    virtual ~IModel() = default;
};