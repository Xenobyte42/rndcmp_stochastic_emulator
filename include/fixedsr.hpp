#ifndef RNDCMP_INCLUDE_FIXEDSR_HPP_
#define RNDCMP_INCLUDE_FIXEDSR_HPP_

#include <type_traits>
#include <cmath>
#include <random>
#include <iostream>

#include "fixed.hpp"


namespace rndcmp {
    
    static std::random_device rd;
    static std::mt19937 generator = std::mt19937(rd());
    static std::uniform_real_distribution distribution = std::uniform_real_distribution<double>(0.0,1.0);

    template<typename INT_T, int FRACT_SIZE = 0, int POW = 2>
    class FixedSR: public Fixed<INT_T, FRACT_SIZE, POW> {
    public:
        using Fixed<INT_T, FRACT_SIZE, POW>::value;

        /* Constructors */

        template<typename T>
        FixedSR(T v, std::enable_if_t<std::is_floating_point<T>::value, bool> = true) {
            setValueFromT<T>(v);
        }

        FixedSR(INT_T v) {
            setValueFromT<double>(static_cast<double>(v));
        }

        /* + operators */

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        FixedSR operator+(const T& rhs) const {
            return FixedSR(T(*this) + rhs);
        }

        FixedSR operator+(const FixedSR& rhs) const {
            return FixedSR(value + rhs.value);
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        FixedSR& operator+=(const T& rhs) {
            T sum = T(*this) + rhs;
            setValueFromT<T>(sum);
            return *this;
        }

        FixedSR& operator+=(const FixedSR& rhs) {
            value += rhs.value;
            return *this;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        friend FixedSR operator+(T lhs, const FixedSR& rhs) {
            T val = lhs + T(rhs);
            return FixedSR(val);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        FixedSR operator+(const T& rhs) const {
            return FixedSR(double(*this) + double(rhs));
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        friend FixedSR operator+(T lhs, const FixedSR& rhs) {
            double val = double(lhs) + double(rhs);
            return FixedSR(val);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        FixedSR& operator+=(const T& rhs) {
            double val = double(*this) + double(rhs);
            setValueFromT<double>(val);
            return *this;
        }

        /* - operators */

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        FixedSR operator-(const T& rhs) const {
            return FixedSR(T(*this) - rhs);
        }

        FixedSR operator-(const FixedSR& rhs) const {
            return FixedSR(value - rhs.value);
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        FixedSR& operator-=(const T& rhs) {
            T sub = T(*this) - rhs;
            setValueFromT<T>(sub);
            return *this;
        }

        FixedSR& operator-=(const FixedSR& rhs) {
            value -= rhs.value;
            return *this;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        friend FixedSR operator-(T lhs, const FixedSR& rhs) {
            T val = lhs - T(rhs);
            return FixedSR(val);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        FixedSR operator-(const T& rhs) const {
            return FixedSR(double(*this) - double(rhs));
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        friend FixedSR operator-(T lhs, const FixedSR& rhs) {
            double val = double(lhs) - double(rhs);
            return FixedSR(val);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        FixedSR& operator-=(const T& rhs) {
            double val = double(*this) - double(rhs);
            setValueFromT<double>(val);
            return *this;
        }

        /* multiply operators */

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        FixedSR operator*(const T& rhs) const {
            return FixedSR(T(*this) * rhs);
        }

        FixedSR operator*(const FixedSR& rhs) const {
            return FixedSR(double(*this) * double(rhs));
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        FixedSR& operator*=(const T& rhs) {
            T mul = T(*this) * rhs;
            setValueFromT<T>(mul);
            return *this;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        friend FixedSR operator*(T lhs, const FixedSR& rhs) {
            T val = lhs * T(rhs);
            return FixedSR(val);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        FixedSR operator*(const T& rhs) const {
            return FixedSR(double(*this) * double(rhs));
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        friend FixedSR operator*(T lhs, const FixedSR& rhs) {
            double val = double(lhs) * double(rhs);
            return FixedSR(val);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        FixedSR& operator*=(const T& rhs) {
            double val = double(*this) * double(rhs);
            setValueFromT<double>(val);
            return *this;
        }

        /* divide operators */

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        FixedSR operator/(const T& rhs) const {
            return FixedSR<INT_T, FRACT_SIZE, POW> (T(*this) / rhs);
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        FixedSR& operator/=(const T& rhs) {
            T div = T(*this) / rhs;
            setValueFromT<T>(div);
            return *this;
        }

        FixedSR operator/(const FixedSR& rhs) const {
            return FixedSR(double(*this) / double(rhs));
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        friend FixedSR operator/(T lhs, const FixedSR& rhs) {
            T val = lhs / T(rhs);
            return FixedSR(val);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        FixedSR operator/(const T& rhs) const {
            return FixedSR(double(*this) / double(rhs));
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        friend FixedSR operator/(T lhs, const FixedSR& rhs) {
            double val = double(lhs) / double(rhs);
            return FixedSR(val);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        FixedSR& operator/=(const T& rhs) {
            double val = double(*this) / double(rhs);
            setValueFromT<double>(val);
            return *this;
        }

        /* ostream overload */
        friend std::ostream& operator<<(std::ostream& os, const FixedSR& v) {
            os << double(v);
            return os;
        }

    private:
        template<typename T>
        void setValueFromT(T v) {
            T powed = v * (1 << FRACT_SIZE);

            T int_part(0.0);
            T fractional_part = std::modf(powed, &int_part);
            double treshold = distribution(generator);
            value = static_cast<INT_T>(powed);
            if ((fractional_part > treshold) && (fractional_part >= 0)) {
                value += 1;
            } else if ((fractional_part < 0) && (std::fabs(fractional_part) < treshold)) {
                value -= 1;
            }
        }
    }; 

}

#endif  // RNDCMP_INCLUDE_FIXEDSR_HPP_
