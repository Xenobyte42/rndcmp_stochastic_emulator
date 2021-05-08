#ifndef RNDCMP_INCLUDE_FLOATSR_HPP_
#define RNDCMP_INCLUDE_FLOATSR_HPP_

#include <type_traits>
#include <cmath>
#include <random>
#include <iostream>

namespace rndcmp {
    // Мask for 29 low-cut bits for double
    constexpr int64_t res32_mask = 0x1fffffff;
    // Epsilon for double to float conversion
    constexpr int64_t eps32 = res32_mask + 1;

    constexpr float float_max = std::numeric_limits<float>::max();
    constexpr float float_min = std::numeric_limits<float>::lowest();

    static std::random_device floating_rd;
    static std::mt19937 int_generator = std::mt19937(floating_rd());
    static std::uniform_int_distribution<int64_t> dist32 = std::uniform_int_distribution<int64_t>(0, res32_mask);

    class FloatSR {
    public:
        FloatSR() = default;

        FloatSR(float v): value(v) {}

        template<typename T>
        FloatSR(T v, std::enable_if_t<std::is_floating_point<T>::value, bool> = true) {
            double double_val = static_cast<double>(v);
            round(double_val);
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        operator T() const {
            return static_cast<T>(value);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        operator T() const {
            return static_cast<T>(value);
        }

        /* + operators */
        
        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        FloatSR operator+(const T& rhs) const {
            double v = static_cast<double>(value) + static_cast<double>(rhs);
            return FloatSR(v);
        }

        FloatSR operator+(const FloatSR& rhs) const {
            double v =  static_cast<double>(value) + static_cast<double>(rhs);
            return FloatSR(v);
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        friend FloatSR operator+(T lhs, const FloatSR& rhs) {
            double v = static_cast<double>(lhs) + static_cast<double>(rhs);
            return FloatSR(v);
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        FloatSR& operator+=(const T& rhs) {
            double v = static_cast<double>(*this) + static_cast<double>(rhs);
            round(v);
            return *this;
        }

        FloatSR& operator+=(const FloatSR& rhs) {
            double v = static_cast<double>(*this) + static_cast<double>(rhs);
            round(v);
            return *this;
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        FloatSR operator+(const T& rhs) const {
            double v = static_cast<double>(*this) + rhs;
            return FloatSR(v);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        friend FloatSR operator+(T lhs, const FloatSR& rhs) {
            double v = lhs + static_cast<double>(rhs);
            return FloatSR(v);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        FloatSR& operator+=(const T& rhs) {
            double v = static_cast<double>(*this) + rhs;
            round(v);
            return *this;
        }

        /* - operators */

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        FloatSR operator-(const T& rhs) const {
            double v = static_cast<double>(*this) - static_cast<double>(rhs);
            return FloatSR(v);
        }

        FloatSR operator-(const FloatSR& rhs) const {
            double v = static_cast<double>(*this) - static_cast<double>(rhs);
            return FloatSR(v);
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        FloatSR& operator-=(const T& rhs) {
            double v = static_cast<double>(*this) - static_cast<double>(rhs);
            round(v);
            return *this;
        }

        FloatSR& operator-=(const FloatSR& rhs) {
            double v = static_cast<double>(value) - static_cast<double>(rhs);
            round(v);
            return *this;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        friend FloatSR operator-(T lhs, const FloatSR& rhs) {
            double v = static_cast<double>(lhs) - static_cast<double>(rhs);
            return FloatSR(v);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        FloatSR operator-(const T& rhs) const {
            double v = static_cast<double>(*this) - static_cast<double>(rhs);
            return FloatSR(v);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        friend FloatSR operator-(T lhs, const FloatSR& rhs) {
            double v = static_cast<double>(lhs) - static_cast<double>(rhs);
            return FloatSR(v);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        FloatSR& operator-=(const T& rhs) {
            double v = static_cast<double>(*this) - rhs;
            round(v);
            return *this;
        }

        // Unary minus
        FloatSR operator-() const {
            return FloatSR(-value);
        }

        /* multiply operators */

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        FloatSR operator*(const T& rhs) const {
            double v = static_cast<double>(*this) * static_cast<double>(rhs);
            return FloatSR(v);
        }

        FloatSR operator*(const FloatSR& rhs) const {
            double v = static_cast<double>(*this) * static_cast<double>(rhs);
            return FloatSR(v);
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        FloatSR& operator*=(const T& rhs) {
            double v = static_cast<double>(*this) * static_cast<double>(rhs);
            round(v);
            return *this;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        friend FloatSR operator*(T lhs, const FloatSR& rhs) {
            double v = static_cast<double>(lhs) * static_cast<double>(rhs);
            return FloatSR(v);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        FloatSR operator*(const T& rhs) const {
            double v = static_cast<double>(*this) * rhs;
            return FloatSR(v);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        friend FloatSR operator*(T lhs, const FloatSR& rhs) {
            double v = lhs * static_cast<double>(rhs);
            return FloatSR(v);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        FloatSR& operator*=(const T& rhs) {
            double v = static_cast<double>(*this) * rhs;
            round(v);
            return *this;
        }

        /* divide operators */

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        FloatSR operator/(const T& rhs) const {
            double v = static_cast<double>(*this) / static_cast<double>(rhs);
            return FloatSR(v);
        }

        FloatSR operator/(const FloatSR& rhs) const {
            double v = static_cast<double>(*this) / static_cast<double>(rhs);
            return FloatSR(v);
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        FloatSR& operator/=(const T& rhs) {
            double v = static_cast<double>(*this) / static_cast<double>(rhs);
            round(v);
            return *this;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        friend FloatSR operator/(T lhs, const FloatSR& rhs) {
            double v = static_cast<double>(lhs) / static_cast<double>(rhs);
            return FloatSR(v);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        FloatSR operator/(const T& rhs) const {
            double v = static_cast<double>(*this) / rhs;
            return FloatSR(v);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        friend FloatSR operator/(T lhs, const FloatSR& rhs) {
            double v = lhs / static_cast<double>(rhs);
            return FloatSR(v);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        FloatSR& operator/=(const T& rhs) {
            double v = static_cast<double>(*this) / rhs;
            round(v);
            return *this;
        }

        /* comparison operators */

        /* less */

        bool operator<(const FloatSR& rhs) const {
            return value < rhs.value;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        bool operator<(const T& rhs) const {
            return value < rhs;
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        bool operator<(const T& rhs) const {
            return value < rhs;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        friend bool operator<(const T& rhs, const FloatSR& lhs) {
            return static_cast<double>(rhs) < static_cast<double>(lhs);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        friend bool operator<(const T& rhs, const FloatSR& lhs) {
            return static_cast<double>(rhs) < static_cast<double>(lhs);
        }

        /* greater */

        bool operator>(const FloatSR& rhs) const {
            return value > rhs.value;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        bool operator>(const T& rhs) const {
            return value > rhs;
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        bool operator>(const T& rhs) const {
            return value > rhs;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        friend bool operator>(const T& rhs, const FloatSR& lhs) {
            return static_cast<double>(rhs) > static_cast<double>(lhs);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        friend bool operator>(const T& rhs, const FloatSR& lhs) {
            return static_cast<double>(rhs) > static_cast<double>(lhs);
        }

        /* equal */

        bool operator==(const FloatSR& rhs) const {
            return value == rhs.value;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        bool operator==(const T& rhs) const {
            return value == rhs;
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        bool operator==(const T& rhs) const {
            return value == rhs;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        friend bool operator==(const T& rhs, const FloatSR& lhs) {
            return static_cast<double>(rhs) == static_cast<double>(lhs);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        friend bool operator==(const T& rhs, const FloatSR& lhs) {
            return static_cast<double>(rhs) == static_cast<double>(lhs);
        }

        /* not equal */
       
        bool operator!=(const FloatSR& rhs) const {
            return value != rhs.value;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        bool operator!=(const T& rhs) const {
            return value != rhs;
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        bool operator!=(const T& rhs) const {
            return value != rhs;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        friend bool operator!=(const T& rhs, const FloatSR& lhs) {
            return static_cast<double>(rhs) != static_cast<double>(lhs);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        friend bool operator!=(const T& rhs, const FloatSR& lhs) {
            return static_cast<double>(rhs) != static_cast<double>(lhs);
        }

        /* less or equal */

        bool operator<=(const FloatSR& rhs) const {
            return value <= rhs.value;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        bool operator<=(const T& rhs) const {
            return value <= rhs;
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        bool operator<=(const T& rhs) const {
            return value <= rhs;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        friend bool operator<=(const T& rhs, const FloatSR& lhs) {
            return static_cast<double>(rhs) <= static_cast<double>(lhs);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        friend bool operator<=(const T& rhs, const FloatSR& lhs) {
            return static_cast<double>(rhs) <= static_cast<double>(lhs);
        }

        /* greater or equal */

        bool operator>=(const FloatSR& rhs) const {
            return value >= rhs.value;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        bool operator>=(const T& rhs) const {
            return value >= rhs;
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        bool operator>=(const T& rhs) const {
            return value >= rhs;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        friend bool operator>=(const T& rhs, const FloatSR& lhs) {
            return static_cast<double>(rhs) >= static_cast<double>(lhs);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        friend bool operator>=(const T& rhs, const FloatSR& lhs) {
            return static_cast<double>(rhs) >= static_cast<double>(lhs);
        }

        /* ostream overload */
        friend std::ostream& operator<<(std::ostream& os, const FloatSR& v) {
            os << float(v);
            return os;
        }

        /* Trigonometric functions */
        friend inline FloatSR cos(const FloatSR&  x)  { return cos(static_cast<double>(x)); }
        friend inline FloatSR sin(const FloatSR&  x)  { return sin(static_cast<double>(x)); }
        friend inline FloatSR tan(const FloatSR&  x)  { return tan(static_cast<double>(x)); }
        friend inline FloatSR acos(const FloatSR&  x)  { return acos(static_cast<double>(x)); }
        friend inline FloatSR asin(const FloatSR&  x)  { return asin(static_cast<double>(x)); }
        friend inline FloatSR atan(const FloatSR&  x)  { return atan(static_cast<double>(x)); }

        /* Hyperbolic functions */
        friend inline FloatSR cosh(const FloatSR&  x)  { return cosh(static_cast<double>(x)); }
        friend inline FloatSR sinh(const FloatSR&  x)  { return sinh(static_cast<double>(x)); }
        friend inline FloatSR tanh(const FloatSR&  x)  { return tanh(static_cast<double>(x)); }
        friend inline FloatSR acosh(const FloatSR&  x)  { return acosh(static_cast<double>(x)); }
        friend inline FloatSR asinh(const FloatSR&  x)  { return asinh(static_cast<double>(x)); }
        friend inline FloatSR atanh(const FloatSR&  x)  { return atanh(static_cast<double>(x)); }

        /* Exponential and logarithmic functions */
        friend inline FloatSR exp(const FloatSR&  x)  { return exp(static_cast<double>(x)); }
        friend inline FloatSR log(const FloatSR&  x)  { return log(static_cast<double>(x)); }
        friend inline FloatSR log10(const FloatSR&  x)  { return log10(static_cast<double>(x)); }

        /* Power functions */
        friend inline FloatSR pow(const FloatSR&  base, double exponent)  { return pow(static_cast<double>(base), exponent); }
        friend inline FloatSR sqrt(const FloatSR&  x)  { return sqrt(static_cast<double>(x)); }
        friend inline FloatSR cbrt(const FloatSR&  x)  { return cbrt(static_cast<double>(x)); }

        /* Other functions */
        friend inline FloatSR abs(const FloatSR&  x)  { return abs(static_cast<double>(x)); }
        friend inline FloatSR fabs(const FloatSR&  x)  { return fabs(static_cast<double>(x)); }
        friend inline FloatSR abs2(const FloatSR& x)  { return x*x; }

    private:
        void round(double x) {
            // Interpret double as int64 for better bits manipulating
            int64_t x_int = reinterpret_cast<int64_t&>(x);
            // Truncate lower bits
            int64_t x_tr = x_int & ~res32_mask;
            // Generate random value
            int64_t p = dist32(int_generator);
            if (p < (x_int & res32_mask)) {
                x_tr += eps32;
            }
            double result = reinterpret_cast<double&>(x_tr);

            // Check for overflow
            if (result > float_max) {
                value = float_max;
            } else if (result < float_min) {
                value = float_min;
            } else {
                value = static_cast<float>(result);
            }
        }

        float value;
    };
}

#endif  // RNDCMP_INCLUDE_FLOATSR_HPP_