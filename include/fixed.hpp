#ifndef RNDCMP_INCLUDE_FIXED_HPP_
#define RNDCMP_INCLUDE_FIXED_HPP_

#include <cmath>
#include <Eigen/Core>


namespace rndcmp {
    template<typename INT_T, int FRACT_SIZE = 0, int POW = 2>
    class Fixed {
    public:
        Fixed() = default;

        /* constructors */

        template<typename T>
        Fixed(T v, std::enable_if_t<std::is_floating_point<T>::value, bool> = true) {
            setValueFromT(v);
        }

        template<typename T>
        Fixed(T v, std::enable_if_t<std::is_integral_v<T>, int> = 0) {
            setValueFromT(static_cast<double>(v));
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        operator T() const {
            return static_cast<T>(value) / (1 << FRACT_SIZE);
        }

        /* + operators */

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        Fixed operator+(const T& rhs) const {
            return Fixed(T(*this) + rhs);
        }

        Fixed operator+(const Fixed& rhs) const {
            return Fixed(value + rhs.value);
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        friend Fixed operator+(T lhs, const Fixed& rhs) {
            T val = lhs + T(rhs);
            return Fixed(val);
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        Fixed& operator+=(const T& rhs) {
            T sum = T(*this) + rhs;
            setValueFromT<T>(sum);
            return *this;
        }

        Fixed& operator+=(const Fixed& rhs) {
            value += rhs.value;
            return *this;
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        Fixed operator+(const T& rhs) const {
            return Fixed(double(*this) + double(rhs));
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        friend Fixed operator+(T lhs, const Fixed& rhs) {
            double val = double(lhs) + double(rhs);
            return Fixed(val);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        Fixed& operator+=(const T& rhs) {
            double val = double(*this) + double(rhs);
            setValueFromT<double>(val);
            return *this;
        }

        /* - operators */

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        Fixed operator-(const T& rhs) const {
            return Fixed(T(*this) - rhs);
        }

        Fixed operator-(const Fixed& rhs) const {
            return Fixed(value - rhs.value);
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        Fixed& operator-=(const T& rhs) {
            T sub = T(*this) - rhs;
            setValueFromT<T>(sub);
            return *this;
        }

        Fixed& operator-=(const Fixed& rhs) {
            value -= rhs.value;
            return *this;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        friend Fixed operator-(T lhs, const Fixed& rhs) {
            T val = lhs - T(rhs);
            return Fixed(val);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        Fixed operator-(const T& rhs) const {
            return Fixed(double(*this) - double(rhs));
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        friend Fixed operator-(T lhs, const Fixed& rhs) {
            double val = double(lhs) - double(rhs);
            return Fixed(val);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        Fixed& operator-=(const T& rhs) {
            double val = double(*this) - double(rhs);
            setValueFromT<double>(val);
            return *this;
        }

        /* multiply operators */

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        Fixed operator*(const T& rhs) const {
            return Fixed(T(*this) * rhs);
        }

        Fixed operator*(const Fixed& rhs) const {
            return Fixed(double(*this) * double(rhs));
        }

        Fixed& operator*=(const Fixed& rhs) {
            value *= rhs.value;
            return *this;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        Fixed& operator*=(const T& rhs) {
            T mul = T(*this) * rhs;
            setValueFromT<T>(mul);
            return *this;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        friend Fixed operator*(T lhs, const Fixed& rhs) {
            T val = lhs * T(rhs);
            return Fixed(val);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        Fixed operator*(const T& rhs) const {
            return Fixed(double(*this) * double(rhs));
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        friend Fixed operator*(T lhs, const Fixed& rhs) {
            double val = double(lhs) * double(rhs);
            return Fixed(val);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        Fixed& operator*=(const T& rhs) {
            double val = double(*this) * double(rhs);
            setValueFromT<double>(val);
            return *this;
        }

        /* divide operators */

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        Fixed operator/(const T& rhs) const {
            return Fixed(T(*this) / rhs);
        }

        Fixed operator/(const Fixed& rhs) const {
            return Fixed(double(*this) / double(rhs));
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        Fixed& operator/=(const T& rhs) {
            T div = T(*this) / rhs;
            setValueFromT<T>(div);
            return *this;
        }

        Fixed& operator/=(const Fixed& rhs) {
            value /= rhs.value;
            return *this;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        friend Fixed operator/(T lhs, const Fixed& rhs) {
            T val = lhs / T(rhs);
            return Fixed(val);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        Fixed operator/(const T& rhs) const {
            return Fixed(double(*this) / double(rhs));
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        friend Fixed operator/(T lhs, const Fixed& rhs) {
            double val = double(lhs) / double(rhs);
            return Fixed(val);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        Fixed& operator/=(const T& rhs) {
            double val = double(*this) / double(rhs);
            setValueFromT<double>(val);
            return *this;
        }

        /* comparison operators */

        /* less */

        bool operator<(const Fixed& rhs) const {
            return value < rhs.value;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        bool operator<(const T& rhs) const {
            return static_cast<double>(*this) < rhs;
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        bool operator<(const T& rhs) const {
            return static_cast<double>(*this) < rhs;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        friend bool operator<(const T& rhs, const Fixed& lhs) {
            return static_cast<double>(rhs) < static_cast<double>(lhs);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        friend bool operator<(const T& rhs, const Fixed& lhs) {
            return static_cast<double>(rhs) < static_cast<double>(lhs);
        }

        /* greater */

        bool operator>(const Fixed& rhs) const {
            return value > rhs.value;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        bool operator>(const T& rhs) const {
            return static_cast<double>(*this) > rhs;
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        bool operator>(const T& rhs) const {
            return static_cast<double>(*this) > rhs;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        friend bool operator>(const T& rhs, const Fixed& lhs) {
            return static_cast<double>(rhs) > static_cast<double>(lhs);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        friend bool operator>(const T& rhs, const Fixed& lhs) {
            return static_cast<double>(rhs) > static_cast<double>(lhs);
        }

        /* equal */

        bool operator==(const Fixed& rhs) const {
            return value == rhs.value;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        bool operator==(const T& rhs) const {
            return static_cast<double>(*this) == rhs;
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        bool operator==(const T& rhs) const {
            return static_cast<double>(*this) == rhs;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        friend bool operator==(const T& rhs, const Fixed& lhs) {
            return static_cast<double>(rhs) == static_cast<double>(lhs);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        friend bool operator==(const T& rhs, const Fixed& lhs) {
            return static_cast<double>(rhs) == static_cast<double>(lhs);
        }

        /* not equal */
       
        bool operator!=(const Fixed& rhs) const {
            return value != rhs.value;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        bool operator!=(const T& rhs) const {
            return static_cast<double>(*this) != rhs;
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        bool operator!=(const T& rhs) const {
            return static_cast<double>(*this) != rhs;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        friend bool operator!=(const T& rhs, const Fixed& lhs) {
            return static_cast<double>(rhs) != static_cast<double>(lhs);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        friend bool operator!=(const T& rhs, const Fixed& lhs) {
            return static_cast<double>(rhs) != static_cast<double>(lhs);
        }

        /* less or equal */

        bool operator<=(const Fixed& rhs) const {
            return value <= rhs.value;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        bool operator<=(const T& rhs) const {
            return static_cast<double>(*this)  <= rhs;
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        bool operator<=(const T& rhs) const {
            return static_cast<double>(*this)  <= rhs;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        friend bool operator<=(const T& rhs, const Fixed& lhs) {
            return static_cast<double>(rhs) <= static_cast<double>(lhs);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        friend bool operator<=(const T& rhs, const Fixed& lhs) {
            return static_cast<double>(rhs) <= static_cast<double>(lhs);
        }

        /* greater or equal */

        bool operator>=(const Fixed& rhs) const {
            return value >= rhs.value;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        bool operator>=(const T& rhs) const {
            return static_cast<double>(*this) >= rhs;
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        bool operator>=(const T& rhs) const {
            return static_cast<double>(*this) >= rhs;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        friend bool operator>=(const T& rhs, const Fixed& lhs) {
            return static_cast<double>(rhs) >= static_cast<double>(lhs);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        friend bool operator>=(const T& rhs, const Fixed& lhs) {
            return static_cast<double>(rhs) >= static_cast<double>(lhs);
        }

        /* unary minus */

        Fixed operator-() const {
            double v = - static_cast<double>(*this);
            return Fixed(v);
        }

        /* ostream overload */
        friend std::ostream& operator<<(std::ostream& os, const Fixed& v) {
            os << double(v);
            return os;
        }
    
        /* Trigonometric functions */
        friend inline Fixed cos(const Fixed&  x)  { return cos(static_cast<double>(x)); }
        friend inline Fixed sin(const Fixed&  x)  { return sin(static_cast<double>(x)); }
        friend inline Fixed tan(const Fixed&  x)  { return tan(static_cast<double>(x)); }
        friend inline Fixed acos(const Fixed&  x)  { return acos(static_cast<double>(x)); }
        friend inline Fixed asin(const Fixed&  x)  { return asin(static_cast<double>(x)); }
        friend inline Fixed atan(const Fixed&  x)  { return atan(static_cast<double>(x)); }

        /* Hyperbolic functions */
        friend inline Fixed cosh(const Fixed&  x)  { return cosh(static_cast<double>(x)); }
        friend inline Fixed sinh(const Fixed&  x)  { return sinh(static_cast<double>(x)); }
        friend inline Fixed tanh(const Fixed&  x)  { return tanh(static_cast<double>(x)); }
        friend inline Fixed acosh(const Fixed&  x)  { return acosh(static_cast<double>(x)); }
        friend inline Fixed asinh(const Fixed&  x)  { return asinh(static_cast<double>(x)); }
        friend inline Fixed atanh(const Fixed&  x)  { return atanh(static_cast<double>(x)); }

        /* Exponential and logarithmic functions */
        friend inline Fixed exp(const Fixed&  x)  { return exp(static_cast<double>(x)); }
        friend inline Fixed log(const Fixed&  x)  { return log(static_cast<double>(x)); }
        friend inline Fixed log10(const Fixed&  x)  { return log10(static_cast<double>(x)); }
        friend inline Fixed logb(const Fixed&  x)  { return logb(static_cast<double>(x)); }

        /* Power functions */
        friend inline Fixed pow(const Fixed&  base, double exponent)  { return pow(static_cast<double>(base), exponent); }
        friend inline Fixed sqrt(const Fixed&  x)  { return sqrt(static_cast<double>(x)); }
        friend inline Fixed cbrt(const Fixed&  x)  { return cbrt(static_cast<double>(x)); }

        friend inline Fixed scalbn(const Fixed&  x, int n)  { return scalbn(static_cast<double>(x), n); }

        /* Other functions */
        friend inline Fixed abs(const Fixed&  x)  { return abs(static_cast<double>(x)); }
        friend inline Fixed fabs(const Fixed&  x)  { return fabs(static_cast<double>(x)); }
        friend inline Fixed abs2(const Fixed& x)  { return x*x; }

        friend inline Fixed copysign(const Fixed&  x1, const Fixed& x2)  { return copysign(static_cast<double>(x1), static_cast<double>(x2)); }
        friend inline Fixed fmax(const Fixed&  x1, const Fixed&  x2) { return x1 < x2 ? x1 : x2; }
        friend inline bool isfinite(const Fixed& x) { return true; }

    protected:
        INT_T value;
    private:
        template<typename T>
        void setValueFromT(T v) {
            value = static_cast<INT_T>(v * (1 << FRACT_SIZE));
        }
    };
}

namespace Eigen {
    template<typename INT_T, int FRACT_SIZE, int POW> struct NumTraits<rndcmp::Fixed<INT_T, FRACT_SIZE, POW>> {
        typedef rndcmp::Fixed<INT_T, FRACT_SIZE, POW> Real;
        typedef rndcmp::Fixed<INT_T, FRACT_SIZE, POW> NonInteger;
        typedef rndcmp::Fixed<INT_T, FRACT_SIZE, POW> Nested;
        
        enum {
            IsComplex = 0,
            IsInteger = 0,
            IsSigned = 1,
            RequireInitialization = 1,
            ReadCost = 1,
            AddCost = 4,
            MulCost = 4
        };
    };
}

#endif  // RNDCMP_INCLUDE_FIXED_HPP_
