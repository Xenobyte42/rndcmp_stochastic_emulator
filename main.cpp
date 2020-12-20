#include <iostream>
#include <cstdint>
#include "fixed_point.hpp"
#include "integrator.hpp"


int main() {
    // Uniform distribution random generator
    std::default_random_engine gen = std::default_random_engine();
    std::uniform_real_distribution dist = std::uniform_real_distribution<double>(0.0,2.0);

    // Candidates
    rndcmp::FixedPoint fp15_16 = rndcmp::FixedPoint<std::int32_t, 16>(0.0);
    rndcmp::FixedPointSR fp15_16_sr = rndcmp::FixedPointSR<std::int32_t, 16>(0.0);
    float f_val = 0.0;
    double accurate = 0.0;

    std::cout << "Size of FixedPoint15_16: " << sizeof(rndcmp::FixedPoint<std::int32_t, 16>) << std::endl;
    std::cout << "Size of FixedPointSR15_16: " << sizeof(rndcmp::FixedPointSR<std::int32_t, 16>) << std::endl;
    std::cout << "Size of float: " << sizeof(float) << std::endl;
    std::cout << "Size of double: " << sizeof(double) << std::endl;

    for (int i = 1; i < 10000; i++) {
        double value = dist(gen); 
        // double value = std::pow(2, -i);
        // std::cout << value << std::endl;
        accurate += value;
        f_val += value;
        fp15_16 += value;
        fp15_16_sr += value;
    }

    std::cout.precision(32);
    std::cout.setf(std::ios::fixed);
    std::cout << accurate << std::endl;
    std::cout << double(fp15_16_sr) << std::endl;
    std::cout << "FixedPoint diff:" << std::fabs(double(fp15_16) - accurate) << std::endl;
    std::cout << "float diff:" << std::fabs(double(f_val) - accurate) << std::endl;
    std::cout << "FixedPointSR diff:" << std::fabs(double(fp15_16_sr) - accurate) << std::endl;
}