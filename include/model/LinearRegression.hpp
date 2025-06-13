#pragma once

#include "IModel.hpp"
#include <Eigen/Core>
#include <Eigen/QR>
#include <vector>

template <typename T = double>
class LinearRegression : public IModel<T> {
  public:
    using value_type = T;

  private:
    // Eigen Row-major aliases
    using RowMat = Eigen::Matrix<value_type, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;
    using ColVec = Eigen::Matrix<value_type, Eigen::Dynamic, 1>;
    using Stride = Eigen::Stride<Eigen::Dynamic, Eigen::Dynamic>;
    using RowMap = Eigen::Map<const RowMat, 0, Stride>;
    using VecMap = Eigen::Map<const ColVec>;

  public:
    LinearRegression() : intercept_(0) {}

    void fit(const MatrixView<T> &X, const std::vector<T> &y) override {
        std::size_t n = X.num_rows();
        std::size_t d = X.num_cols();
        assert(y.size() == n && "X and y must have the same size");

        // Map X and y to Eigen structures (no copy)
        RowMap X_map(X.data(), n, d, Stride(X.stride(), 1));
        VecMap y_map(y.data(), n);

        // Build [1 | X]
        RowMat X_aug(n, d + 1); // Expensive?
        X_aug.col(0).setOnes();
        X_aug.block(0, 1, n, d) = X_map;

        // Solve OLS via QR
        ColVec w_aug = X_aug.colPivHouseholderQr().solve(y_map);

        // Store coefficients
        intercept_ = w_aug(0);
        coef_ = w_aug.tail(d);
    }

    T predict(const std::vector<T> &x) const override {
        assert(x.size() == static_cast<std::size_t>(coef_.size()) && "dim mismatch");
        VecMap x_map(x.data(), x.size());
        return coef_.dot(x_map) + intercept_;
    }

    std::vector<T> predictBatch(const MatrixView<T> &X) const override {
        std::size_t n = X.num_rows();
        std::size_t d = X.num_cols();
        assert(d == static_cast<std::size_t>(coef_.size()) && "dim mismatch");

        RowMap X_map(X.data(), n, d, Stride(X.stride(), 1));
        ColVec y = X_map * coef_;
        y.array() += intercept_;

        return {y.data(), y.data() + n};
    }

  private:
    ColVec coef_;
    T intercept_;
};