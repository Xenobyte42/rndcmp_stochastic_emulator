#include <iostream>
#include <cstdint>
#include "types.hpp"
#include "integrator.hpp"


int main() {
    size_t N =  1000000;

    double s0 = 0.;
    // Candidates
    rndcmp::Fixed fp15_16 = rndcmp::Fixed<std::int32_t, 16>(s0);
    rndcmp::FixedSR fp15_16_sr = rndcmp::FixedSR<std::int32_t, 16>(s0);
    rndcmp::Fixed fp7_24 = rndcmp::Fixed<std::int32_t, 24>(s0);
    rndcmp::FixedSR fp7_24_sr = rndcmp::FixedSR<std::int32_t, 24>(s0);
    rndcmp::Fixed fp7_8 = rndcmp::Fixed<std::int16_t, 8>(s0);
    rndcmp::FixedSR fp7_8_sr = rndcmp::FixedSR<std::int16_t, 8>(s0);
    rndcmp::FloatSR float_sr = rndcmp::FloatSR(s0);
    half_float::half half_sum(static_cast<float>(s0));
    half_float::halfsr halfsr_sum(static_cast<float>(s0));
    rndcmp::bfloat16 bfloat(s0);
    rndcmp::bfloat16sr bfloatsr(s0);
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
        half_sum += value;
        halfsr_sum += value;
        bfloat += value;
        bfloatsr += value;
    }

    std::cout.precision(8);
    std::cout.setf(std::ios::fixed);
    std::cout << "Accurate sum: " << accurate << std::endl;
    std::cout << "Float sum: " << f_val << std::endl;
    std::cout << "Fp<15.16> sum: " << fp15_16 << std::endl;
    std::cout << "FpSR<15.16> sum: " << fp15_16_sr << std::endl;
    std::cout << "Fp<7.24> sum: " << fp7_24 << std::endl;
    std::cout << "FpSR<7.24> sum: " << fp7_24_sr << std::endl;
    std::cout << "Fp<7.8> sum: " << fp7_8 << std::endl;
    std::cout << "FpSR<7.8> sum: " << fp7_8_sr << std::endl;
    std::cout << "FloatSR sum: " << float_sr << std::endl;
    std::cout << "Half sum: " << half_sum << std::endl;
    std::cout << "HalfSR sum: " << halfsr_sum << std::endl;
    std::cout << "Bfloat16 sum: " << bfloat << std::endl;
    std::cout << "Bfloat16SR sum: " << bfloatsr << std::endl;
    std::cout << std::endl;
    std::cout.precision(6);
    std::cout << "Float error: " << std::fabs(double(f_val) - accurate) << std::endl;
    std::cout << "Fp<15.16> error: " << std::fabs(double(fp15_16) - accurate) << std::endl;
    std::cout << "FpSR<15.16> error: " << std::fabs(double(fp15_16_sr) - accurate) << std::endl;
    std::cout << "Fp<7.24> error: " << std::fabs(double(fp7_24) - accurate) << std::endl;
    std::cout << "FpSR<7.24> error: " << std::fabs(double(fp7_24_sr) - accurate) << std::endl;
    std::cout << "Fp<7.8> error: " << std::fabs(double(fp7_8) - accurate) << std::endl;
    std::cout << "FpSR<7.8> error: " << std::fabs(double(fp7_8_sr) - accurate) << std::endl;
    std::cout << "FloatSR error: " << std::fabs(double(float_sr) - accurate) << std::endl;
    std::cout << "Half error: " << std::fabs(double(half_sum) - accurate) << std::endl;
    std::cout << "HalfSR error: " << std::fabs(double(halfsr_sum) - accurate) << std::endl;
    std::cout << "Bfloat16 error: " << std::fabs(double(bfloat) - accurate) << std::endl;
    std::cout << "Bfloat16SR error: " << std::fabs(double(bfloatsr) - accurate) << std::endl;
    return 0;
}