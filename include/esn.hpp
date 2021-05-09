#ifndef RNDCMP_INCLUDE_ESN_HPP_
#define RNDCMP_INCLUDE_ESN_HPP_

#include <random>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>


namespace rndcmp {
    template<typename DATA_TYPE, size_t INPUT_SIZE, size_t HIDDEN_SIZE, size_t OUTPUT_SIZE>
    class ESN {
    public:
        ESN(
            double spectral_radius,
            double sparsity,
            size_t seed
            ):
            _seed(seed) {
            std::mt19937 rd(_seed);
            std::normal_distribution<double> generator(0.0, 1.0);

            initialize_weight_m<INPUT_SIZE, HIDDEN_SIZE>(W_in, generator, rd, sparsity);
            initialize_weight_m<HIDDEN_SIZE, HIDDEN_SIZE>(W, generator, rd, sparsity);
            initialize_weight_m<HIDDEN_SIZE, OUTPUT_SIZE>(W_out, generator, rd, 0.0);

            rescale_weight_m<HIDDEN_SIZE>(W, spectral_radius);
        }

    protected:
        template<size_t FIRST_SIZE, size_t SECOND_SIZE>
        void initialize_weight_m(Eigen::Matrix<DATA_TYPE, FIRST_SIZE, SECOND_SIZE>& m, std::normal_distribution<double> generator, std::mt19937 rd, double sparsity) {
            std::mt19937 random_device(_seed);
            std::uniform_real_distribution<double> probability_gen(0.0, 1.0);

            for (size_t i = 0; i < FIRST_SIZE; i++) {
                for (size_t j = 0; j < SECOND_SIZE; j++) {
                    if (probability_gen(random_device) < sparsity) {
                        m(i, j) = DATA_TYPE(0.0);
                    } else {
                        m(i, j) = DATA_TYPE(generator(rd));
                    }
                }
            }
        }

        template<size_t M_SIZE>
        void rescale_weight_m(Eigen::Matrix<DATA_TYPE, M_SIZE, M_SIZE>& m, double spectral_radius) {
            Eigen::EigenSolver<Eigen::Matrix<double, M_SIZE, M_SIZE>> solver(m.template cast<double>());
            Eigen::VectorXcd eivals = solver.eigenvalues();

            double real_sr = 0.0;
            for (size_t i = 0; i < eivals.size(); i++) {
                double temp = sqrt(pow(eivals[i].real(), 2) + pow(eivals[i].imag(), 2));
                if (temp > real_sr) {
                    real_sr = temp;
                }
            }

            m /= (real_sr / spectral_radius);
        }

        size_t _seed;

        Eigen::Matrix<DATA_TYPE, INPUT_SIZE, HIDDEN_SIZE> W_in;
        Eigen::Matrix<DATA_TYPE, HIDDEN_SIZE, HIDDEN_SIZE> W;
        Eigen::Matrix<DATA_TYPE, HIDDEN_SIZE, OUTPUT_SIZE> W_out;
    };
}

#endif  // RNDCMP_INCLUDE_ESN_HPP_