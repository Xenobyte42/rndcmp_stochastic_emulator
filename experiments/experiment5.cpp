#include <iostream>
#include <cstdint>
#include <string>

#include "types.hpp"
#include "integrator.hpp"


using Fixed16 = rndcmp::Fixed<std::int32_t, 16>;
using FixedSR16 = rndcmp::FixedSR<std::int32_t, 16>;

using Fixed24 = rndcmp::Fixed<std::int32_t, 24>;
using FixedSR24 = rndcmp::FixedSR<std::int32_t, 24>;

using Fixed8 = rndcmp::Fixed<std::int16_t, 8>;
using FixedSR8 = rndcmp::FixedSR<std::int16_t, 8>;

template<typename T>
void calculate(double time_end, double step) {
    rndcmp::system_type<T> system = {
        [] (const std::vector<T>& x, double t) { return T(10.0 * (x[1] - x[0])); },
        [] (const std::vector<T>& x, double t) { return T(x[0] * (28.0 - x[2]) - x[1]); },
        [] (const std::vector<T>& x, double t) { return T(x[0] * x[1] - 8.0 / 3.0 * x[2]); }
    };

    std::vector<T> initial = {T(1.), T(1.), T(1.)};
    auto integrator = rndcmp::RK4Integrator<T>(system, 0.0, time_end, step);
    integrator.setInitial(initial);
    integrator.solve();

    auto solution = integrator.getSolution();
    std::cout.precision(10);
    std::cout.setf(std::ios::fixed);
    for (size_t i = 0; i < solution.size(); i++) {
        std::cout << solution[i][0] << "\t" << solution[i][1] << "\t" << solution[i][2] << std::endl;
    }
}

// Usage: 
// ./experiment5 <type> <time_end> <step>

int main(int argc, char** argv) {
    std::string type(argv[1]);
    double time_end = stod(std::string(argv[2]));
    double step = stod(std::string(argv[3]));

    if (type.compare("double") == 0) {
        calculate<double>(time_end, step);
    }
    if (type.compare("float") == 0) {
        calculate<float>(time_end, step);
    }
    if (type.compare("Fixed16") == 0) {
        calculate<Fixed16>(time_end, step);
    }
    if (type.compare("FixedSR16") == 0) {
        calculate<FixedSR16>(time_end, step);
    }
    if (type.compare("Fixed24") == 0) {
        calculate<Fixed24>(time_end, step);
    }
    if (type.compare("FixedSR24") == 0) {
        calculate<FixedSR24>(time_end, step);
    }
    if (type.compare("Fixed8") == 0) {
        calculate<Fixed8>(time_end, step);
    }
    if (type.compare("FixedSR8") == 0) {
        calculate<FixedSR8>(time_end, step);
    }
    if (type.compare("FloatSR") == 0) {
        calculate<rndcmp::FloatSR>(time_end, step);
    }
    if (type.compare("bfloat16") == 0) {
        calculate<rndcmp::bfloat16>(time_end, step);
    }
    if (type.compare("bfloat16sr") == 0) {
        calculate<rndcmp::bfloat16sr>(time_end, step);
    }
    if (type.compare("half") == 0) {
        std::cout << "half" << std::endl;
        calculate<half_float::half>(time_end, step);
    }
    // if (type.compare("halfsr") == 0) {
    //     calculate<half_float::halfsr>(time_end, step);
    // }
    return 0;
}