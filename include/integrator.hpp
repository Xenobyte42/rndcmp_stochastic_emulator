#ifndef RNDCMP_INCLUDE_INTEGRATOR_HPP_
#define RNDCMP_INCLUDE_INTEGRATOR_HPP_

#include <vector>
#include <exception>
#include <string>


namespace rndcmp {

    template<typename T>
    using system_func = std::function<const T(const std::vector<T>&, double)>;
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

        RK4Integrator(const system_type<DTYPE>& system, double timeStart, double timeEnd, double step):
        _system(system), _timeStart(timeStart), _timeEnd(timeEnd), _step(step) {}

        void setInitial(const std::vector<DTYPE>& initial) {
            if (initial.size() != _system.size()) {
                throw IntegratorException("incorrect vector size");
            }

            _initial = initial;
        }

        void solve() {
            std::vector<DTYPE> tempX = _initial;
            _solution.push_back(_initial);

            for (double t = _timeStart; t <= _timeEnd; t+=_step) {
                std::vector<DTYPE> k1 = getk1(tempX, t);
                std::vector<DTYPE> k2 = getk2(tempX, k1, t);
                std::vector<DTYPE> k3 = getk3(tempX, k2, t);
                std::vector<DTYPE> k4 = getk4(tempX, k3, t);

                std::vector<DTYPE> newX;
                for (size_t i = 0; i < tempX.size(); i++) {
                    newX.push_back(tempX[i] + _step / 6. * (k1[i] + 2 * k2[i] + 2 * k3[i] + k4[i]));
                }
                tempX = newX;
                _solution.push_back(tempX);
            }
        }

        std::vector<std::vector<DTYPE>> getSolution() const {
            return _solution;
        }

    protected:
        std::vector<DTYPE> getk1(const std::vector<DTYPE>& x, double t) {
            return calculate(x, t);
        }

        std::vector<DTYPE> getk2(const std::vector<DTYPE>& x, const std::vector<DTYPE>& k1, double t) {
            std::vector<DTYPE> k2X;
            for (size_t i = 0; i < x.size(); i++) {
                k2X.push_back(x[i] + _step / 2. * k1[i]);
            }
            return calculate(k2X, t + _step / 2.);
        }

        std::vector<DTYPE> getk3(const std::vector<DTYPE>& x, const std::vector<DTYPE>& k2, double t) {
            std::vector<DTYPE> k3X;
            for (size_t i = 0; i < x.size(); i++) {
                k3X.push_back(x[i] + _step / 2. * k2[i]);
            }
            return calculate(k3X, t + _step / 2.);
        }

        std::vector<DTYPE> getk4(const std::vector<DTYPE>& x, const std::vector<DTYPE>& k3, double t) {
            std::vector<DTYPE> k4X;
            for (size_t i = 0; i < x.size(); i++) {
                k4X.push_back(x[i] + _step * k3[i]);
            }
            return calculate(k4X, t + _step);
        }

        std::vector<DTYPE> calculate(const std::vector<DTYPE>& x, double t) {
            std::vector<DTYPE> result;
            for (auto func : _system) {
                result.push_back(func(x, t));
            }
            return result;
        }

        std::vector<DTYPE> _initial;
        std::vector<std::vector<DTYPE>> _solution;
        system_type<DTYPE> _system;
        double _timeStart;
        double _timeEnd;
        double _step;
    };
}

#endif  // RNDCMP_INCLUDE_INTEGRATOR_HPP_
