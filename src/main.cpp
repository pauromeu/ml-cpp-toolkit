#include "core/Dataset.hpp"
#include "model/IModel.hpp"
#include "model/LinearRegression.hpp"
#include <Eigen/Core>
#include <iostream>

int main() {
    using T = double;

    std::vector<std::vector<T>> nested = {{1, 2}, {3, 4}, {5, 6}};

    Dataset<T> X(nested.size(), nested[0].size());
    X.fill([&](std::size_t i, std::size_t j) { return nested[i][j]; });
}
