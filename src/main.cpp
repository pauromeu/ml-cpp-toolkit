#include "core/Dataset.hpp"
#include "core/MatrixView.hpp"
#include "model/LinearRegression.hpp"
#include <iostream>

int main() {
    constexpr std::size_t n = 5; // rows
    constexpr std::size_t m = 2; // columns (features)

    /* ground-truth parameters:  y = 1 + 2·x₁ − 3·x₂ */
    const double b = 1.0;
    const Eigen::Vector2d w(2.0, -3.0);

    /* ------------------------------------------------------------------ */
    /* create a toy design matrix X (row-major, contiguous)                */
    Dataset<double> ds(n, m);
    const double X_raw[n][m] = {{0, 0}, {1, 0}, {0, 1}, {1, 1}, {2, 2}};
    ds.fill([&](std::size_t i, std::size_t j) { return X_raw[i][j]; });

    /* build the exact target vector y = b + X·w                           */
    std::vector<double> y(n);
    for (std::size_t i = 0; i < n; ++i)
        y[i] = b + w[0] * ds.view()(i, 0) + w[1] * ds.view()(i, 1);

    /* ------------------------------------------------------------------ */
    /* fit the model                                                      */
    LinearRegression<double> lr;
    lr.fit(ds.view(), y);

    // std::cout << "Fitted intercept  = " << lr.intercept()            << '\\n';
    // std::cout << "Fitted coefficients: ["
    //           << lr.coefficients()(0) << ", "
    //           << lr.coefficients()(1) << "]\\n\\n";

    /* ------------------------------------------------------------------ */
    /* 1. single-row predict() ------------------------------------------- */
    std::cout << "-- single predict() --" << std::endl;
    for (std::size_t i = 0; i < n; ++i) {
        std::vector<double> row = {ds.view()(i, 0), ds.view()(i, 1)};
        std::cout << lr.predict(row) << std::endl;
    }

    /* 2. manual batch via loop + predict() ------------------------------ */
    std::cout << std::endl << "manual loop (predict per row)" << std::endl;
    std::vector<double> y_loop;
    y_loop.reserve(n);
    for (std::size_t i = 0; i < n; ++i) {
        std::vector<double> row = {ds.view()(i, 0), ds.view()(i, 1)};
        y_loop.emplace_back(lr.predict(row));
    }
    for (double v : y_loop)
        std::cout << v << std::endl;

    /* 3. vectorised predictBatch() -------------------------------------- */
    // std::cout << "\\n-- vectorised predictBatch() --\\n";
    // auto y_vec = lr.predictBatch(ds.view());
    // for (double v : y_vec) std::cout << v << '\\n';

    return 0;
}
