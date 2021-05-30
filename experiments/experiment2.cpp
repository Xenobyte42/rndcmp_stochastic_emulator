#include <iostream>
#include <cstdint>
#include "types.hpp"
#include "integrator.hpp"


int main() {
    size_t N = 1e4;
    size_t N_count = 200;
    static std::random_device floating_rd;
    static std::mt19937 gen = std::mt19937(floating_rd());

    std::uniform_real_distribution dist = std::uniform_real_distribution<double>(-0.0004,0.0016);

    std::cout.precision(8);
    std::cout.setf(std::ios::fixed);

    double float_err = 0.0;
    double floatsr_err = 0.0;
    double fp1516_err = 0.0;
    double fp1516sr_err = 0.0;
    double fp724_err = 0.0;
    double fp724sr_err = 0.0;
    double fp78_err = 0.0;
    double fp78sr_err = 0.0;
    double half_err = 0.0;
    double halfsr_err = 0.0;
    double bfloat_err = 0.0;
    double bfloatsr_err = 0.0;

    for (size_t i = 0; i < N_count; i++) {
        double s0 = 100.;
        // Candidates
        float f_val = s0;
        double accurate = s0;
        rndcmp::FloatSR floar_sr = rndcmp::FloatSR(s0);
        rndcmp::Fixed fp15_16 = rndcmp::Fixed<std::int32_t, 16>(s0);
        rndcmp::FixedSR fp15_16_sr = rndcmp::FixedSR<std::int32_t, 16>(s0);

        rndcmp::Fixed fp7_24 = rndcmp::Fixed<std::int32_t, 24>(s0);
        rndcmp::FixedSR fp7_24_sr = rndcmp::FixedSR<std::int32_t, 24>(s0);

        rndcmp::Fixed fp7_8 = rndcmp::Fixed<std::int16_t, 8>(s0);
        rndcmp::FixedSR fp7_8sr = rndcmp::FixedSR<std::int16_t, 8>(s0);
        
        half_float::halfsr half_sr = s0;
        half_float::half half_sum(static_cast<float>(s0));

        rndcmp::bfloat16 bfloat = rndcmp::bfloat16(s0);
        rndcmp::bfloat16sr bfloatsr = rndcmp::bfloat16sr(s0);
        
        for (int j = 1; j <= N; j++) {
            double value = dist(gen);
            accurate += value;
            f_val += value;

            floar_sr += value;

            fp15_16 += value;
            fp15_16_sr += value;

            fp7_24 += value;
            fp7_24_sr += value;

            fp7_8 += value;
            fp7_8sr += value;

            half_sr += value;
            half_sum += value;

            bfloat += value;
            bfloatsr += value;
        }

        float_err += std::fabs(static_cast<double>(accurate - f_val));
        floatsr_err += std::fabs(static_cast<double>(accurate - floar_sr));
        fp1516_err += std::fabs(static_cast<double>(accurate - fp15_16));
        fp1516sr_err += std::fabs(static_cast<double>(accurate - fp15_16_sr));
        fp724_err += std::fabs(static_cast<double>(accurate - fp7_24));
        fp724sr_err += std::fabs(static_cast<double>(accurate - fp7_24_sr));
        fp78_err += std::fabs(static_cast<double>(accurate - fp7_8));
        fp78sr_err += std::fabs(static_cast<double>(accurate - fp7_8sr));
        half_err += std::fabs(static_cast<double>(accurate - half_sum));
        halfsr_err += std::fabs(static_cast<double>(accurate - half_sr));
        bfloat_err += std::fabs(static_cast<double>(accurate - bfloat));
        bfloatsr_err += std::fabs(static_cast<double>(accurate - bfloatsr));
    }

    std::cout << float_err / N_count << std::endl;
    std::cout << floatsr_err / N_count << std::endl;
    std::cout << fp1516_err / N_count << std::endl;
    std::cout << fp1516sr_err / N_count << std::endl;
    std::cout << fp724_err / N_count << std::endl;
    std::cout << fp724sr_err / N_count << std::endl;
    std::cout << fp78_err / N_count << std::endl;
    std::cout << fp78sr_err / N_count << std::endl;
    std::cout << half_err / N_count << std::endl;
    std::cout << halfsr_err / N_count << std::endl;
    std::cout << bfloat_err / N_count << std::endl;
    std::cout << bfloatsr_err / N_count << std::endl;
    return 0;
}