#include <iostream>
#include <cstdint>
#include "fixed_point.hpp"
#include "integrator.hpp"


int main() {
    size_t N = 1000000;
    std::default_random_engine gen = std::default_random_engine();
    std::uniform_real_distribution dist = std::uniform_real_distribution<double>(-0.004,0.016);

    std::cout.precision(8);
    std::cout.setf(std::ios::fixed);
    for (size_t n = 1000; n < N; n+=5000) {
        double s0 = 1000.;
        // Candidates
        rndcmp::FixedPoint fp15_16 = rndcmp::FixedPoint<std::int32_t, 16>(s0);
        rndcmp::FixedPointSR fp15_16_sr = rndcmp::FixedPointSR<std::int32_t, 16>(s0);
        float f_val = s0;
        double accurate = s0;
        for (int i = 1; i <= n; i++) {
            double value = dist(gen);
            accurate += value;
            f_val += value;
            fp15_16 += value;
            fp15_16_sr += value;
        }
        std::cout << n << "\t";
        std::cout << std::fabs(double(f_val) - accurate) << "\t";
        std::cout << std::fabs(double(fp15_16) - accurate) << "\t";
        std::cout << std::fabs(double(fp15_16_sr) - accurate);
        std::cout << std::endl;
    }
    
    return 0;
}