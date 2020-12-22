#ifndef RNDCMP_INCLUDE_INTEGRATOR_HPP_
#define RNDCMP_INCLUDE_INTEGRATOR_HPP_

#include <vector>
#include <exception>
#include <string>
#include <iostream>


namespace rndcmp {

    template<typename T>
    using system_func = std::function<T(const std::vector<T>&, double)>;
    template<typename T>
    using system_type = std::vector<system_func<T>>;

    template<typename DTYPE>
    class RK4Integrator {
    public:
        class IntegratorException: std::exception {
        public:
            IntegratorException(const std::string& msg): _msg(msg) {}
             virtual const char* what() const noexcept override {
                return _msg.c_str();
            }
        private:
            std::string _msg;
        };

        RK4Integrator(const system_type<double>& system, double timeStart, double timeEnd, double step):
        _system(system), _timeStart(timeStart), _timeEnd(timeEnd), _step(step) {}

        void setInitial(const std::vector<DTYPE>& initial) {
            if (initial.size() != _system.size()) {
                throw IntegratorException("incorrect vector size");
            }

            _initial = initial;
        }

        void solve() {
            std::vector<double> tempX(_initial.begin(), _initial.end());
            _solution.push_back(_initial);

            for (double t = _timeStart; t <= _timeEnd; t+=_step) {
                std::vector<double> k1 = getk1(tempX, t);
                std::vector<double> k2 = getk2(tempX, k1, t);
                std::vector<double> k3 = getk3(tempX, k2, t);
                std::vector<double> k4 = getk4(tempX, k3, t);

                std::vector<DTYPE> newX;
                for (size_t i = 0; i < tempX.size(); i++) {
                    newX.push_back(tempX[i] + _step / 6. * (k1[i] + 2. * k2[i] + 2. * k3[i] + k4[i]));
                }
                std::transform(newX.begin(), newX.end(), tempX.begin(), [](double x) { return (DTYPE)x;});
                _solution.push_back(newX);
            }
        }

        std::vector<std::vector<DTYPE>> getSolution() const {
            return _solution;
        }

    protected:
        std::vector<double> getk1(const std::vector<double>& x, double t) {
            auto res = calculate(x, t);
            return res;
        }

        std::vector<double> getk2(const std::vector<double>& x, const std::vector<double>& k1, double t) {
            std::vector<double> k2X;
            for (size_t i = 0; i < x.size(); i++) {
                k2X.push_back(x[i] + _step / 2. * k1[i]);
            }
            return calculate(k2X, t + _step / 2.);
        }

        std::vector<double> getk3(const std::vector<double>& x, const std::vector<double>& k2, double t) {
            std::vector<double> k3X;
            for (size_t i = 0; i < x.size(); i++) {
                k3X.push_back(x[i] + _step / 2. * k2[i]);
            }
            return calculate(k3X, t + _step / 2.);
        }

        std::vector<double> getk4(const std::vector<double>& x, const std::vector<double>& k3, double t) {
            std::vector<double> k4X;
            for (size_t i = 0; i < x.size(); i++) {
                k4X.push_back(x[i] + _step * k3[i]);
            }
            return calculate(k4X, t + _step);
        }

        std::vector<double> calculate(const std::vector<double>& x, double t) {
            std::vector<double> result;
            for (auto func : _system) {
                result.push_back(func(x, t));
            }
            return result;
        }

        std::vector<DTYPE> _initial;
        std::vector<std::vector<DTYPE>> _solution;
        system_type<double> _system;
        double _timeStart;
        double _timeEnd;
        double _step;
    };
}

#endif  // RNDCMP_INCLUDE_INTEGRATOR_HPP_
