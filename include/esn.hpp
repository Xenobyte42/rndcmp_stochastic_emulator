#ifndef RNDCMP_INCLUDE_ESN_HPP_
#define RNDCMP_INCLUDE_ESN_HPP_

#include <random>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>
#include <Eigen/SVD>
#include <Eigen/QR>


namespace rndcmp {
    template<typename DATA_TYPE, size_t INPUT_SIZE, size_t HIDDEN_SIZE, size_t OUTPUT_SIZE>
    class ESN {
    public:
        using HiddenVector = Eigen::Array<DATA_TYPE, HIDDEN_SIZE, 1>;
        using InputVector = Eigen::Array<DATA_TYPE, INPUT_SIZE, 1>;

        ESN(
            double spectral_radius,
            double sparsity,
            size_t seed
            ):
            _seed(seed) {
            std::mt19937 rd(_seed);
            std::normal_distribution<double> generator(0.0, 1.0);

            initialize_weight_m<HIDDEN_SIZE, INPUT_SIZE>(W_in, generator, rd, sparsity);
            initialize_weight_m<HIDDEN_SIZE, HIDDEN_SIZE>(W, generator, rd, sparsity);
            initialize_weight_m<OUTPUT_SIZE, HIDDEN_SIZE>(W_out, generator, rd, 0.0);

            rescale_weight_m<HIDDEN_SIZE>(W, spectral_radius);
        }

        double fit(Eigen::Matrix<DATA_TYPE, Eigen::Dynamic, INPUT_SIZE> inputs, Eigen::Matrix<DATA_TYPE, Eigen::Dynamic, OUTPUT_SIZE> outputs) {
            Eigen::Matrix<DATA_TYPE, Eigen::Dynamic, Eigen::Dynamic> states;
            states.resize(inputs.rows(), HIDDEN_SIZE);
            states.setZero();

            // Calculate hidden states
            for (size_t i = 0; i < inputs.rows(); i++) {
                if (i == 0) {
                    Eigen::Matrix<DATA_TYPE, Eigen::Dynamic, Eigen::Dynamic> initial;
                    initial.resize(1, HIDDEN_SIZE);
                    initial.setZero();
                    states.row(i) = update(initial.transpose(), inputs.row(i).transpose()).transpose();
                } else {
                    states.row(i) = update(states.row(i - 1).transpose(), inputs.row(i).transpose()).transpose();
                }
            }

            // Find optimal matrix
            Eigen::Matrix<DATA_TYPE, Eigen::Dynamic, Eigen::Dynamic> states_square = states.transpose() * states;
            Eigen::Matrix<DATA_TYPE, Eigen::Dynamic, Eigen::Dynamic> pinv = states_square.completeOrthogonalDecomposition().pseudoInverse();
            W_out = (pinv * states.transpose() * outputs).transpose();

            // Train prediction
            double pred = error(states * W_out.transpose(), outputs);
            std::cout  << "Prediction error: " << pred <<  std::endl;
            return pred;
        }

        Eigen::Matrix<DATA_TYPE, Eigen::Dynamic, Eigen::Dynamic> predict(Eigen::Matrix<DATA_TYPE, Eigen::Dynamic, INPUT_SIZE> inputs) {
            size_t n_samples = inputs.rows();
            Eigen::Matrix<DATA_TYPE, Eigen::Dynamic, Eigen::Dynamic> outputs;
            outputs.resize(n_samples, OUTPUT_SIZE);
            outputs.setZero();

            Eigen::Matrix<DATA_TYPE, Eigen::Dynamic, Eigen::Dynamic> prev;
            prev.resize(1, HIDDEN_SIZE);
            prev.setZero();

            for (size_t i = 0; i < n_samples; i++) {
                Eigen::Matrix<DATA_TYPE, Eigen::Dynamic, Eigen::Dynamic> temp_state =
                 update(prev.transpose(), inputs.row(i).transpose()).transpose();

                outputs.row(i) = temp_state * W_out.transpose();
                prev = temp_state;
            }

            return outputs;
        }

        double score(Eigen::Matrix<DATA_TYPE, Eigen::Dynamic, INPUT_SIZE> x, Eigen::Matrix<DATA_TYPE, Eigen::Dynamic, OUTPUT_SIZE> y) {
            Eigen::Matrix<DATA_TYPE, Eigen::Dynamic, Eigen::Dynamic> y_pred = predict(x);
            return error(y, y_pred);
        }

    protected:
        double error(Eigen::Matrix<DATA_TYPE, Eigen::Dynamic, OUTPUT_SIZE> y, Eigen::Matrix<DATA_TYPE, Eigen::Dynamic, OUTPUT_SIZE> y_pred) {
            Eigen::Matrix<DATA_TYPE, Eigen::Dynamic, Eigen::Dynamic> error_m = y - y_pred;
            return sqrt((error_m.array() * error_m.array()).matrix().mean());
        }

        HiddenVector update(HiddenVector state, InputVector input_vector) {
            HiddenVector preactivation = W * state.matrix() + W_in * input_vector.matrix();
            return preactivation.array().tanh();
        }

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

        Eigen::Matrix<DATA_TYPE, HIDDEN_SIZE, INPUT_SIZE> W_in;
        Eigen::Matrix<DATA_TYPE, HIDDEN_SIZE, HIDDEN_SIZE> W;
        Eigen::Matrix<DATA_TYPE, OUTPUT_SIZE, HIDDEN_SIZE> W_out;
    };
}

#endif  // RNDCMP_INCLUDE_ESN_HPP_
