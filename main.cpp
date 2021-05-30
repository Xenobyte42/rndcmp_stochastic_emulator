#include <iostream>
#include <cstdint>
#include <ctime> 
#include "types.hpp"
#include "integrator.hpp"
#include "esn.hpp"

using Fixed16 = rndcmp::Fixed<std::int32_t, 16>;
using FixedSR16 = rndcmp::FixedSR<std::int32_t, 16>;

using Fixed24 = rndcmp::Fixed<std::int32_t, 24>;
using FixedSR24 = rndcmp::FixedSR<std::int32_t, 24>;

using Fixed8 = rndcmp::Fixed<std::int16_t, 8>;
using FixedSR8 = rndcmp::FixedSR<std::int16_t, 8>;

template<typename T>
std::vector<std::vector<T>> calculate(double time_end, double step) {
    rndcmp::system_type<T> system = {
        [] (const std::vector<T>& x, double t) { return T(10.0 * (x[1] - x[0])); },
        [] (const std::vector<T>& x, double t) { return T(x[0] * (28.0 - x[2]) - x[1]); },
        [] (const std::vector<T>& x, double t) { return T(x[0] * x[1] - 8.0 / 3.0 * x[2]); }
    };

    std::vector<T> initial = {T(1.), T(1.), T(1.)};
    auto integrator = rndcmp::RK4Integrator<T>(system, 0.0, time_end, step);
    integrator.setInitial(initial);
    integrator.solve();

    return integrator.getSolution();
}

template<typename T>
std::vector<double> run_once(size_t layers_cnt, double time_end, double step, double sparsity, double spectral_radius) {
    size_t seed = time(NULL);
    std::vector<std::vector<double>> inputs = calculate<double>(time_end, step);
    size_t full_size = inputs.size() / 10;
    size_t train_size = full_size / 6.0 * 5;
    size_t test_size = full_size - train_size;    

    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> eigen_inputs_d;
    eigen_inputs_d.resize(full_size, 3);

    size_t idx_step = inputs.size() / full_size;

    for (size_t i = 0; i < full_size; i++) {
        eigen_inputs_d.row(i) = Eigen::Map<Eigen::Matrix<double, 1, 3>>(inputs[i * idx_step].data());
    }

    Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> eigen_inputs = eigen_inputs_d.template cast<T>();

    Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> train = eigen_inputs.block(0, 0, train_size, 3);

    rndcmp::ESN<T> net(
        3,      // input size
        layers_cnt,   // hidden size
        3,      // output size
        spectral_radius,   // spectral radius
        sparsity,    // sparsity
        0.1,
        seed    // random seed
    );

    net.fit(train.block(0, 0, train.rows() - 1, train.cols()), train.block(1, 0, train.rows() - 1, train.cols()));
    Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> predicted = net.predict(train, test_size - 1);
    
    std::vector<double> errors;
    for (size_t i = 0; i < predicted.rows(); i++) {
        errors.push_back(net.error(eigen_inputs.block(1, 0, i + 1, eigen_inputs.cols()),
                               predicted.block(0, 0, i + 1, predicted.cols())));
    }

    return errors;
}

template<typename T>
void run(size_t layers_cnt, double time_end, double step, double sparsity, double spectral_radius) {
    std::vector<std::vector<double>> errors_arr;
    for (size_t i = 0; i < 1; i++) {
        errors_arr.push_back(run_once<T>(layers_cnt, time_end, step, sparsity, spectral_radius));
    }

    size_t best = 0;
    double min = -1;
    for (size_t i = 0; i < errors_arr.size(); i++) {
        size_t last = errors_arr[i].size() - 1;
        if (errors_arr[i][last] < min || min < 0) {
            min = errors_arr[i][last];
            best = i;
        }
    }

    for (size_t i = 0; i < errors_arr[best].size(); i++) {
        std::cout << errors_arr[best][i] << std::endl;
    }
}

int main(int argc, char** argv) {
    if (argc < 6) {
        std::cout << argv[0] << " neurons_cnt time_end step sparsity spectral_radius type" << std::endl;
        return -1;
    }
    int layers_cnt = stoi(std::string(argv[1]));
    double time_end = stod(std::string(argv[2]));
    double step = stod(std::string(argv[3]));
    double sparsity = stod(std::string(argv[4]));
    double spectral_radius = stod(std::string(argv[5]));
    std::string type(argv[6]);
    if (type.compare("double") == 0) {
        run<double>(layers_cnt, time_end, step, sparsity, spectral_radius);
    }
    if (type.compare("float") == 0) {
        run<float>(layers_cnt, time_end, step, sparsity, spectral_radius);
    }
    if (type.compare("Fixed16") == 0) {
        run<Fixed16>(layers_cnt, time_end, step, sparsity, spectral_radius);
    }
    if (type.compare("FixedSR16") == 0) {
        run<FixedSR16>(layers_cnt, time_end, step, sparsity, spectral_radius);
    }
    if (type.compare("Fixed24") == 0) {
        run<Fixed24>(layers_cnt, time_end, step, sparsity, spectral_radius);
    }
    if (type.compare("FixedSR24") == 0) {
        run<FixedSR24>(layers_cnt, time_end, step, sparsity, spectral_radius);
    }
    if (type.compare("Fixed8") == 0) {
        run<Fixed8>(layers_cnt, time_end, step, sparsity, spectral_radius);
    }
    if (type.compare("FixedSR8") == 0) {
        run<FixedSR8>(layers_cnt, time_end, step, sparsity, spectral_radius);
    }
    if (type.compare("FloatSR") == 0) {
        run<rndcmp::FloatSR>(layers_cnt, time_end, step, sparsity, spectral_radius);
    }
    if (type.compare("bfloat16") == 0) {
        run<rndcmp::bfloat16>(layers_cnt, time_end, step, sparsity, spectral_radius);
    }
    if (type.compare("bfloat16sr") == 0) {
        run<rndcmp::bfloat16sr>(layers_cnt, time_end, step, sparsity, spectral_radius);
    }

    return 0;
}