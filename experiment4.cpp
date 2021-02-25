#include <iostream>
#include <cstdint>
#include "fixed_point.hpp"
#include "integrator.hpp"
#include "floatsr.hpp"


int main() {
    rndcmp::system_type<double> system = {
        [] (const std::vector<double>& x, double t) { return 10.0 * (x[1] - x[0]); },
        [] (const std::vector<double>& x, double t) { return x[0] * (28.0 - x[2]) - x[1]; },
        [] (const std::vector<double>& x, double t) { return x[0] * x[1] - 8.0 / 3.0 * x[2]; }
    };

    rndcmp::system_type<float> system_float = {
        [] (const std::vector<float>& x, double t) { return 10.0 * (x[1] - x[0]); },
        [] (const std::vector<float>& x, double t) { return x[0] * (28.0 - x[2]) - x[1]; },
        [] (const std::vector<float>& x, double t) { return x[0] * x[1] - 8.0 / 3.0 * x[2]; }
    };

    rndcmp::system_type<rndcmp::FloatSR> system_float_sr = {
        [] (const std::vector<rndcmp::FloatSR>& x, double t) { return 10.0 * (x[1] - x[0]); },
        [] (const std::vector<rndcmp::FloatSR>& x, double t) { return x[0] * (28.0 - x[2]) - x[1]; },
        [] (const std::vector<rndcmp::FloatSR>& x, double t) { return x[0] * x[1] - 8.0 / 3.0 * x[2]; }
    };

    std::vector<double> initial = {1., 1., 1.};
    std::vector<float> initial_f = {1., 1., 1.};
    std::vector<rndcmp::FloatSR> initial_float_sr = {rndcmp::FloatSR(1.f), rndcmp::FloatSR(1.f), rndcmp::FloatSR(1.f)};

    auto integrator = rndcmp::RK4Integrator<double>(system, 0.0, 100., 0.0001);
    integrator.setInitial(initial);
    integrator.solve();

    auto integrator_f = rndcmp::RK4Integrator<float>(system_float, 0.0, 100., 0.0001);
    integrator_f.setInitial(initial_f);
    integrator_f.solve();

    auto integrator_float_sr = rndcmp::RK4Integrator<rndcmp::FloatSR>(system_float_sr, 0.0, 100., 0.0001);
    integrator_float_sr.setInitial(initial_float_sr);
    integrator_float_sr.solve();

    auto solution = integrator.getSolution();
    auto solution_f = integrator_f.getSolution();
    auto solution_float_sr = integrator_float_sr.getSolution();
    std::cout << "x\tx_f\tx_fsr\ty\ty_f\ty_fsr\tz\tz_f\tz_fsr" << std::endl;
    std::cout.precision(8);
    std::cout.setf(std::ios::fixed);
    for (size_t i = 0; i < solution.size(); i++) {
        for (size_t j = 0; j < 3; j++) {
            std::cout << solution[i][j] << "\t" << solution_f[i][j];
            std::cout << "\t" << solution_float_sr[i][j];
            if (j == 2) {
                std::cout << std::endl;
            } else {
                std::cout << "\t";
            }
        }
        
    }
    return 0;
}