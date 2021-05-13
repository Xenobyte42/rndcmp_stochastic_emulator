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

        FixedSR() = default;

        template<typename T>
        FixedSR(T v, std::enable_if_t<std::is_floating_point<T>::value, bool> = true) {
            setValueFromT<T>(v);
        }

        template<typename T>
        FixedSR(T v, std::enable_if_t<std::is_integral_v<T>, int> = 0) {
            setValueFromT<double>(static_cast<double>(v));
        }

        /* + operators */

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        FixedSR operator+(const T& rhs) const {
            return FixedSR(T(*this) + rhs);
        }

        FixedSR operator+(const FixedSR& rhs) const {
            double val = static_cast<double>(*this) + static_cast<double>(rhs);
            return FixedSR(val);
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
            double val = static_cast<double>(*this) - static_cast<double>(rhs);
            return FixedSR(val);
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

        FixedSR& operator*=(const FixedSR& rhs) {
            value *= rhs.value;
            return *this;
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

        FixedSR& operator/=(const FixedSR& rhs) {
            value /= rhs.value;
            return *this;
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

        /* unary minus */

        FixedSR operator-() const {
            double v = - static_cast<double>(*this);
            return FixedSR(v);
        }

        /* ostream overload */
        friend std::ostream& operator<<(std::ostream& os, const FixedSR& v) {
            os << double(v);
            return os;
        }

        /* Trigonometric functions */
        friend inline FixedSR cos(const FixedSR&  x)  { return cos(static_cast<double>(x)); }
        friend inline FixedSR sin(const FixedSR&  x)  { return sin(static_cast<double>(x)); }
        friend inline FixedSR tan(const FixedSR&  x)  { return tan(static_cast<double>(x)); }
        friend inline FixedSR acos(const FixedSR&  x)  { return acos(static_cast<double>(x)); }
        friend inline FixedSR asin(const FixedSR&  x)  { return asin(static_cast<double>(x)); }
        friend inline FixedSR atan(const FixedSR&  x)  { return atan(static_cast<double>(x)); }

        /* Hyperbolic functions */
        friend inline FixedSR cosh(const FixedSR&  x)  { return cosh(static_cast<double>(x)); }
        friend inline FixedSR sinh(const FixedSR&  x)  { return sinh(static_cast<double>(x)); }
        friend inline FixedSR tanh(const FixedSR&  x)  { return tanh(static_cast<double>(x)); }
        friend inline FixedSR acosh(const FixedSR&  x)  { return acosh(static_cast<double>(x)); }
        friend inline FixedSR asinh(const FixedSR&  x)  { return asinh(static_cast<double>(x)); }
        friend inline FixedSR atanh(const FixedSR&  x)  { return atanh(static_cast<double>(x)); }

        /* Exponential and logarithmic functions */
        friend inline FixedSR exp(const FixedSR&  x)  { return exp(static_cast<double>(x)); }
        friend inline FixedSR log(const FixedSR&  x)  { return log(static_cast<double>(x)); }
        friend inline FixedSR log10(const FixedSR&  x)  { return log10(static_cast<double>(x)); }
        friend inline FixedSR logb(const FixedSR&  x)  { return logb(static_cast<double>(x)); }

        /* Power functions */
        friend inline FixedSR pow(const FixedSR&  base, double exponent)  { return pow(static_cast<double>(base), exponent); }
        friend inline FixedSR sqrt(const FixedSR&  x)  { return sqrt(static_cast<double>(x)); }
        friend inline FixedSR cbrt(const FixedSR&  x)  { return cbrt(static_cast<double>(x)); }

        friend inline FixedSR scalbn(const FixedSR&  x, int n)  { return scalbn(static_cast<double>(x), n); }

        /* Other functions */
        friend inline FixedSR abs(const FixedSR&  x)  { return abs(static_cast<double>(x)); }
        friend inline FixedSR fabs(const FixedSR&  x)  { return fabs(static_cast<double>(x)); }
        friend inline FixedSR abs2(const FixedSR& x)  { return x*x; }

        friend inline FixedSR copysign(const FixedSR&  x1, const FixedSR& x2)  { return copysign(static_cast<double>(x1), static_cast<double>(x2)); }
        friend inline FixedSR fmax(const FixedSR&  x1, const FixedSR&  x2) { return x1 < x2 ? x1 : x2; }
        friend inline bool isfinite(const FixedSR& x) { return true; }

    private:
        template<typename T>
        void setValueFromT(T v) {
            T powed = v * (1 << FRACT_SIZE);

            T int_part(0.0);
            T fractional_part = std::modf(powed, &int_part);
            double treshold = distribution(generator);
            value = static_cast<INT_T>(powed);
            if ((std::fabs(fractional_part) > treshold) && (fractional_part >= 0)) {
                value += 1;
            } else if ((fractional_part < 0) && (std::fabs(fractional_part) > treshold)) {
                value -= 1;
            }
        }
    }; 
}

namespace Eigen {
    template<typename INT_T, int FRACT_SIZE, int POW> struct NumTraits<rndcmp::FixedSR<INT_T, FRACT_SIZE, POW>> {
        typedef rndcmp::FixedSR<INT_T, FRACT_SIZE, POW> Real;
        typedef rndcmp::FixedSR<INT_T, FRACT_SIZE, POW> NonInteger;
        typedef rndcmp::FixedSR<INT_T, FRACT_SIZE, POW> Nested;
        
        enum {
            IsComplex = 0,
            IsInteger = 0,
            IsSigned = 1,
            RequireInitialization = 1,
            ReadCost = 1,
            AddCost = 6,
            MulCost = 8
        };
    };
}

#endif  // RNDCMP_INCLUDE_FIXEDSR_HPP_
