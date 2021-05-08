#include <iostream>
#include <cstdint>
#include "types.hpp"
#include "integrator.hpp"
#include <boost/numeric/ublas/matrix.hpp>

/* DELETE THIS FILE IN FUTURE AND USE ONLY FOR CUSTOM TESTS */

int main() {
    double n = 5;
    half_float::halfsr a(5);
    rndcmp::Fixed<int32_t, 16> b(4);
 
    // Eigen::Matrix<half_float::halfsr, 2, 2> m;
    // m(0,0) = 4.5;
    // m(1,0) = 4.5;
    // m(0,1) = 4.5;
    // m(1,1) = 4.5;
    // std::cout << m << std::endl;
}