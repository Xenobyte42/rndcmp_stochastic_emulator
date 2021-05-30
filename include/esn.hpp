#ifndef RNDCMP_INCLUDE_ESN_HPP_
#define RNDCMP_INCLUDE_ESN_HPP_

#include <random>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>
#include <Eigen/SVD>
#include <Eigen/QR>


namespace rndcmp {
    template<typename DATA_TYPE>
    class ESN {
    public:
        using ESNMatrix = Eigen::Matrix<DATA_TYPE, Eigen::Dynamic, Eigen::Dynamic>;

        ESN(
            size_t input_size,
            size_t hidden_size,
            size_t output_size,
            double spectral_radius,
            double sparsity,
            double regularization,
            size_t seed
            ):
            _input_size(input_size),
            _hidden_size(hidden_size),
            _output_size(output_size),
            _regularization(regularization),
            _seed(seed) {
            W_in.resize(_hidden_size, _input_size);
            W.resize(_hidden_size, _hidden_size);
            W_out.resize(_output_size, _hidden_size);
            
            std::mt19937 rd(_seed);
            std::uniform_real_distribution<double> generator(-0.5, 0.5);

            initialize_weight_m(W_in, generator, rd, 0.0, hidden_size, input_size);
            initialize_weight_m(W, generator, rd, sparsity, hidden_size, hidden_size);
            initialize_weight_m(W_out, generator, rd, 0.0, output_size, hidden_size);

            rescale_weight_m(spectral_radius);
        }

        double fit(ESNMatrix inputs, ESNMatrix outputs) {
            ESNMatrix states;
            states.resize(inputs.rows(), _hidden_size);
            states.setZero();

            // Calculate hidden states
            for (size_t i = 0; i < inputs.rows(); i++) {
                if (i == 0) {
                    ESNMatrix initial;
                    initial.resize(1, _hidden_size);
                    initial.setZero();
                    states.row(i) = update(initial.transpose(), inputs.row(i).transpose()).transpose();
                    
                } else {
                    states.row(i) = update(states.row(i - 1).transpose(), inputs.row(i).transpose()).transpose();
                }
            }

            // Find optimal matrix (we do it in double for numerical stability of fixed and other types)
            Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> states_d = states.template cast<double>();
            Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> states_square_d = states_d.transpose() * states_d;
            
            for (size_t i = 0; i < states_square_d.rows(); i++) {
                states_square_d(i, i) += _regularization;
            }
            Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> pinv_d = states_square_d.completeOrthogonalDecomposition().pseudoInverse();
            Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> W_out_d = (pinv_d * states_d.transpose() * outputs.template cast<double>()).transpose();
            // ESNMatrix pinv = pinv_d.template cast<DATA_TYPE>();
            // W_out = (pinv * states.transpose() * outputs).transpose();
            W_out = W_out_d.template cast<DATA_TYPE>();

            // Train prediction
            double pred = error(states * W_out.transpose(), outputs);
            return pred;
        }

        ESNMatrix predict(ESNMatrix inputs, size_t n_future) {
            size_t n_samples = inputs.rows();
            ESNMatrix outputs;
            outputs.resize(n_samples + n_future, _output_size);
            outputs.setZero();

            ESNMatrix prev;
            prev.resize(1, _hidden_size);
            prev.setZero();

            for (size_t i = 0; i < n_samples; i++) {
                ESNMatrix temp_state =
                 update(prev.transpose(), inputs.row(i).transpose()).transpose();
                outputs.row(i) = temp_state * W_out.transpose();
                prev = temp_state;
            }

            for (size_t i = 0; i < n_future; i++) {
                size_t idx = n_samples + i;
                
                ESNMatrix input = outputs.row(idx - 1);
                ESNMatrix temp_state =
                 update(prev.transpose(), input.transpose()).transpose();

                outputs.row(idx) = temp_state * W_out.transpose();
                prev = temp_state;
            }
            return outputs;
        }

        ESNMatrix predict(ESNMatrix inputs) {
            return predict(inputs, 0);
        }

        double score(ESNMatrix x, ESNMatrix y) {
            ESNMatrix y_pred = predict(x);
            return error(y, y_pred);
        }

        double error(ESNMatrix y, ESNMatrix y_pred) {
            Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> error_m = (y - y_pred).template cast<double>();
            return sqrt((error_m.array() * error_m.array()).matrix().rowwise().sum().mean());
        }

    protected:
        ESNMatrix update(ESNMatrix state, ESNMatrix input_vector) {
            ESNMatrix preactivation = W * state.matrix() + W_in * input_vector.matrix();
            return preactivation.array().tanh();
        }

        void initialize_weight_m(ESNMatrix& m, 
                                 std::uniform_real_distribution<double> generator, 
                                 std::mt19937 rd, 
                                 double sparsity,
                                 size_t first_size,
                                 size_t second_size) {
            std::mt19937 random_device(_seed);
            std::uniform_real_distribution<double> probability_gen(0.0, 1.0);

            for (size_t i = 0; i < first_size; i++) {
                for (size_t j = 0; j < second_size; j++) {
                    if (probability_gen(random_device) < sparsity) {
                        m(i, j) = DATA_TYPE(0.0);
                    } else {
                        m(i, j) = DATA_TYPE(generator(rd));
                    }
                }
            }
        }

        void rescale_weight_m(double spectral_radius) {
            Eigen::EigenSolver<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>> solver(W.template cast<double>());
            Eigen::VectorXcd eivals = solver.eigenvalues();

            double real_sr = 0.0;
            for (size_t i = 0; i < eivals.size(); i++) {
                double temp = sqrt(pow(eivals[i].real(), 2) + pow(eivals[i].imag(), 2));
                if (temp > real_sr) {
                    real_sr = temp;
                }
            }

            W /= (real_sr / spectral_radius);
        }

        size_t _seed;

        Eigen::Matrix<DATA_TYPE, Eigen::Dynamic, Eigen::Dynamic> W_in;
        Eigen::Matrix<DATA_TYPE, Eigen::Dynamic, Eigen::Dynamic> W;
        Eigen::Matrix<DATA_TYPE, Eigen::Dynamic, Eigen::Dynamic> W_out;

        size_t _input_size;
        size_t _hidden_size;
        size_t _output_size;
        double _regularization;
    };
}

#endif  // RNDCMP_INCLUDE_ESN_HPP_
