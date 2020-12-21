#include <iostream>
#include <cstdint>
#include "fixed_point.hpp"
#include "integrator.hpp"


using FixedType = rndcmp::FixedPoint<std::int32_t, 16>;
using FixedTypeSR = rndcmp::FixedPointSR<std::int32_t, 16>;

int main() {
    rndcmp::system_type<double> system = {
        [] (const std::vector<double>& x, double t) { return 10.0 * (x[1] - x[0]); },
        [] (const std::vector<double>& x, double t) { return x[0] * (28.0 - x[2]) - x[1]; },
        [] (const std::vector<double>& x, double t) { return x[0] * x[1] - 8.0 / 3.0 * x[2]; }
    };

    rndcmp::system_type<FixedType> system_fp = {
        [] (const std::vector<FixedType>& x, double t) { return FixedType(10.0 * (x[1] - x[0])); },
        [] (const std::vector<FixedType>& x, double t) { return FixedType(x[0] * (28.0 - x[2]) - x[1]); },
        [] (const std::vector<FixedType>& x, double t) { return FixedType(x[0] * x[1] - 8.0 / 3.0 * x[2]); }
    };

    rndcmp::system_type<FixedTypeSR> system_fp_sr = {
        [] (const std::vector<FixedTypeSR>& x, double t) { return FixedTypeSR(10.0 * (x[1] - x[0])); },
        [] (const std::vector<FixedTypeSR>& x, double t) { return FixedTypeSR(x[0] * (28.0 - x[2]) - x[1]); },
        [] (const std::vector<FixedTypeSR>& x, double t) { return FixedTypeSR(x[0] * x[1] - 8.0 / 3.0 * x[2]); }
    };

    std::vector<double> initial = {1., 1., 1.};
    std::vector<FixedType> initial_fp = {FixedType(1.3), FixedType(1.), FixedType(1.)};
    std::vector<FixedTypeSR> initial_fp_sr = {FixedTypeSR(1.3), FixedTypeSR(1.), FixedTypeSR(1.)};

    auto integrator = rndcmp::RK4Integrator<double>(system, 0.0, 100.0, 0.001);
    integrator.setInitial(initial);
    integrator.solve();

    auto integrator_fp = rndcmp::RK4Integrator<FixedType>(system_fp, 0.0, 100.0, 0.001);
    integrator_fp.setInitial(initial_fp);
    integrator_fp.solve();

    auto integrator_fp_sr = rndcmp::RK4Integrator<FixedTypeSR>(system_fp_sr, 0.0, 100.0, 0.001);
    integrator_fp_sr.setInitial(initial_fp_sr);
    integrator_fp_sr.solve();

    auto solution = integrator.getSolution();
    auto solution_fp = integrator_fp.getSolution();
    auto solution_fp_sr = integrator_fp_sr.getSolution();

    /* Do smth with solution */
    return 0;
}