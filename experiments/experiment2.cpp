#include <iostream>
#include <cstdint>
#include "types.hpp"
#include "integrator.hpp"


int main() {
    size_t N = 10000000;
    static std::random_device floating_rd;
    static std::mt19937 gen = std::mt19937(floating_rd());

    std::uniform_real_distribution dist = std::uniform_real_distribution<double>(-0.002,0.016);

    std::cout.precision(8);
    std::cout.setf(std::ios::fixed);
    for (size_t n = 1000; n <= N; n+=5000) {
        double s0 = 0.;
        // Candidates
        rndcmp::Fixed fp15_16 = rndcmp::Fixed<std::int32_t, 16>(s0);
        rndcmp::FixedSR fp15_16_sr = rndcmp::FixedSR<std::int32_t, 16>(s0);
        rndcmp::FloatSR floar_sr = rndcmp::FloatSR(s0);
        float f_val = s0;
        double accurate = s0;
        for (int i = 1; i <= n; i++) {
            double value = dist(gen);
            accurate += value;
            f_val += value;
            fp15_16 += value;
            fp15_16_sr += value;
            floar_sr += value;
        }
        std::cout << n << "\t";
        std::cout << std::fabs(double(f_val) - accurate) << "\t";
        std::cout << std::fabs(double(fp15_16) - accurate) << "\t";
        std::cout << std::fabs(double(fp15_16_sr) - accurate) << "\t";
        std::cout << std::fabs(double(floar_sr) - accurate);
        std::cout << std::endl;
    }

    return 0;
}