#include <iostream>
#include <cstdint>
#include "fixed_point.hpp"
#include "integrator.hpp"


int main() {
    rndcmp::system_type<double> system = {
        [] (const std::vector<double>& x, double t) { return 10.0 * (x[1] - x[0]); },
        [] (const std::vector<double>& x, double t) { return x[0] * (28.0 - x[2]) - x[1]; },
        [] (const std::vector<double>& x, double t) { return x[0] * x[1] - 8.0 / 3.0 * x[2]; }
    };
    std::vector<double> initial = {1., 1., 1.};

    auto integrator = rndcmp::RK4Integrator<double>(system, 0.0, 100.0, 0.001);
    integrator.setInitial(initial);
    integrator.solve();

    auto solution = integrator.getSolution();
    for (auto point : solution) {
        for (auto val : point) {
            std::cout << val << "\t";
        }
        std::cout << std::endl;
    }
    return 0;
}