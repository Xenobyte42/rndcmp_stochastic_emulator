#include <iostream>
#include <cstdint>
#include "types.hpp"
#include "integrator.hpp"
#include "esn.hpp"

/* DELETE THIS FILE IN FUTURE AND USE ONLY FOR CUSTOM TESTS */

int main() {
    size_t seed = 42;

    rndcmp::ESN<rndcmp::FloatSR, 2, 100, 2> net(
        0.95,   // spectral radius
        0.2,    // sparsity
        seed    // random seed
    );

    Eigen::Matrix<rndcmp::FloatSR, 2, 2> x;
    x << 0, 1, 2, 3;
    Eigen::Matrix<rndcmp::FloatSR, 2, 2> y;
    y << 0, 2, 2, 6;

    Eigen::Matrix<rndcmp::FloatSR, 3, 2> x_test;
    x_test << 0, 1, 2, 3, 4, 5;
    net.fit(x, y);
    std::cout << net.predict(x_test) << std::endl;
}