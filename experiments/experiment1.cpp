#include <iostream>
#include <cstdint>
#include "types.hpp"
#include "integrator.hpp"


int main() {
    size_t N =  100000;

    double s0 = 0.;
    // Candidates
    rndcmp::Fixed fp15_16 = rndcmp::Fixed<std::int32_t, 16>(s0);
    rndcmp::FixedSR fp15_16_sr = rndcmp::FixedSR<std::int32_t, 16>(s0);
    rndcmp::Fixed fp7_24 = rndcmp::Fixed<std::int32_t, 24>(s0);
    rndcmp::FixedSR fp7_24_sr = rndcmp::FixedSR<std::int32_t, 24>(s0);
    rndcmp::Fixed fp7_8 = rndcmp::Fixed<std::int16_t, 8>(s0);
    rndcmp::FixedSR fp7_8_sr = rndcmp::FixedSR<std::int16_t, 8>(s0);
    rndcmp::FloatSR float_sr = rndcmp::FloatSR(0.f);
    float f_val = s0;
    double accurate = s0;

    for (int i = 1; i <= N; i++) {
        double value = 1. / i;
        accurate += value;
        f_val += value;
        fp15_16 += value;
        fp15_16_sr += value;
        fp7_24 += value;
        fp7_24_sr += value;
        fp7_8 += value;
        fp7_8_sr += value;
        float_sr += value;
    }

    std::cout.precision(8);
    std::cout.setf(std::ios::fixed);
    std::cout << accurate << std::endl;
    std::cout << f_val << std::endl;
    std::cout << fp15_16 << std::endl;
    std::cout << fp15_16_sr << std::endl;
    std::cout << fp7_24 << std::endl;
    std::cout << fp7_24_sr << std::endl;
    std::cout << fp7_8 << std::endl;
    std::cout << fp7_8_sr << std::endl;
    std::cout << float_sr << std::endl;
    std::cout << std::endl;
    std::cout.precision(6);
    std::cout << std::fabs(double(f_val) - accurate) << std::endl;
    std::cout << std::fabs(double(fp15_16) - accurate) << std::endl;
    std::cout << std::fabs(double(fp15_16_sr) - accurate) << std::endl;
    std::cout << std::fabs(double(fp7_24) - accurate) << std::endl;
    std::cout << std::fabs(double(fp7_24_sr) - accurate) << std::endl;
    std::cout << std::fabs(double(fp7_8) - accurate) << std::endl;
    std::cout << std::fabs(double(fp7_8_sr) - accurate) << std::endl;
    std::cout << std::fabs(double(float_sr) - accurate) << std::endl;
    return 0;
}