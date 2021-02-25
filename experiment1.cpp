#include <iostream>
#include <cstdint>
#include "fixed_point.hpp"
#include "integrator.hpp"
#include "floatsr.hpp"


int main() {
    size_t N =  100000;

    double s0 = 0.;
    // Candidates
    rndcmp::FixedPoint fp15_16 = rndcmp::FixedPoint<std::int32_t, 16>(s0);
    rndcmp::FixedPointSR fp15_16_sr = rndcmp::FixedPointSR<std::int32_t, 16>(s0);
    rndcmp::FixedPoint fp7_24 = rndcmp::FixedPoint<std::int32_t, 24>(s0);
    rndcmp::FixedPointSR fp7_24_sr = rndcmp::FixedPointSR<std::int32_t, 24>(s0);
    rndcmp::FixedPoint fp7_8 = rndcmp::FixedPoint<std::int16_t, 8>(s0);
    rndcmp::FixedPointSR fp7_8_sr = rndcmp::FixedPointSR<std::int16_t, 8>(s0);
    rndcmp::FloatSR float_sr = rndcmp::FloatSR(0.f);
    float f_val = s0;
    double accurate = s0;

    for (int i = 1; i <= N; i++) {
        double value = 0.0001;
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