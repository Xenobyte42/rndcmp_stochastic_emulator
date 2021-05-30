#ifndef RNDCMP_INCLUDE_BFLOAT16SR_HPP_
#define RNDCMP_INCLUDE_BFLOAT16SR_HPP_

#include <type_traits>
#include <iostream>
#include <cstring>
#include <random>
#include <cmath>


namespace rndcmp {
    // Мask for 16 low-cut bits for double
    constexpr int64_t res16_mask = 0xffff;

    static std::random_device bfloating_rd;
    static std::mt19937 bint_generator = std::mt19937(bfloating_rd());
    static std::uniform_int_distribution<int32_t> dist16 = std::uniform_int_distribution<int32_t>(0, res16_mask);
        
    class bfloat16sr {
    public:
        bfloat16sr(): bfloat16sr(0.0f) {};

        bfloat16sr(float rhs) { value = round(rhs); };

        bfloat16sr& operator=(const bfloat16sr& rhs) = default;

        bfloat16sr& operator=(float rhs) { value = round(rhs); return *this; }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        operator T() const {
            int32_t shifted_val = value << 16;
            float float_val = reinterpret_cast<float&>(shifted_val);
            return static_cast<T>(float_val);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        operator T() const {
            int32_t shifted_val = value << 16;
            float float_val = reinterpret_cast<float&>(shifted_val);
            return static_cast<T>(float_val);
        }

        /* + operators */
        
        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        bfloat16sr operator+(const T& rhs) const {
            float v = static_cast<float>(*this) + static_cast<float>(rhs);
            return bfloat16sr(v);
        }

        bfloat16sr operator+(const bfloat16sr& rhs) const {
            float v = static_cast<float>(*this) + static_cast<float>(rhs);
            return bfloat16sr(v);
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        friend bfloat16sr operator+(T lhs, const bfloat16sr& rhs) {
            float v = static_cast<float>(lhs) + static_cast<float>(rhs);
            return bfloat16sr(v);
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        bfloat16sr& operator+=(const T& rhs) {
            float v = static_cast<float>(*this) + static_cast<float>(rhs);
            value = round(v);
            return *this;
        }

        bfloat16sr& operator+=(const bfloat16sr& rhs) {
            float v = static_cast<float>(*this) + static_cast<float>(rhs);
            value = round(v);
            return *this;
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        bfloat16sr operator+(const T& rhs) const {
            float v = static_cast<float>(*this) + rhs;
            return bfloat16sr(v);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        friend bfloat16sr operator+(T lhs, const bfloat16sr& rhs) {
            float v = lhs + static_cast<float>(rhs);
            return bfloat16sr(v);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        bfloat16sr& operator+=(const T& rhs) {
            float v = static_cast<float>(*this) + rhs;
            value = round(v);
            return *this;
        }

        /* - operators */

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        bfloat16sr operator-(const T& rhs) const {
            float v = static_cast<float>(*this) - static_cast<float>(rhs);
            return bfloat16sr(v);
        }

        bfloat16sr operator-(const bfloat16sr& rhs) const {
            float v = static_cast<float>(*this) - static_cast<float>(rhs);
            return bfloat16sr(v);
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        bfloat16sr& operator-=(const T& rhs) {
            float v = static_cast<float>(*this) - static_cast<float>(rhs);
            value = round(v);
            return *this;
        }

        bfloat16sr& operator-=(const bfloat16sr& rhs) {
            float v = static_cast<float>(*this) - static_cast<float>(rhs);
            value = round(v);
            return *this;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        friend bfloat16sr operator-(T lhs, const bfloat16sr& rhs) {
            float v = static_cast<float>(lhs) - static_cast<float>(rhs);
            return bfloat16sr(v);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        bfloat16sr operator-(const T& rhs) const {
            float v = static_cast<float>(*this) - static_cast<float>(rhs);
            return bfloat16sr(v);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        friend bfloat16sr operator-(T lhs, const bfloat16sr& rhs) {
            float v = static_cast<float>(lhs) - static_cast<float>(rhs);
            return bfloat16sr(v);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        bfloat16sr& operator-=(const T& rhs) {
            float v = static_cast<float>(*this) - rhs;
            value = round(v);
            return *this;
        }

        // Unary minus
        bfloat16sr operator-() const {
            float v = - static_cast<float>(*this);
            return bfloat16sr(v);
        }

        /* multiply operators */

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        bfloat16sr operator*(const T& rhs) const {
            float v = static_cast<float>(*this) * static_cast<float>(rhs);
            return bfloat16sr(v);
        }

        bfloat16sr operator*(const bfloat16sr& rhs) const {
            float v = static_cast<float>(*this) * static_cast<float>(rhs);
            return bfloat16sr(v);
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        bfloat16sr& operator*=(const T& rhs) {
            float v = static_cast<float>(*this) * static_cast<float>(rhs);
            value = round(v);
            return *this;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        friend bfloat16sr operator*(T lhs, const bfloat16sr& rhs) {
            float v = static_cast<float>(lhs) * static_cast<float>(rhs);
            return bfloat16sr(v);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        bfloat16sr operator*(const T& rhs) const {
            float v = static_cast<float>(*this) * rhs;
            return bfloat16sr(v);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        friend bfloat16sr operator*(T lhs, const bfloat16sr& rhs) {
            float v = lhs * static_cast<float>(rhs);
            return bfloat16sr(v);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        bfloat16sr& operator*=(const T& rhs) {
            float v = static_cast<float>(*this) * rhs;
            value = round(v);
            return *this;
        }

        bfloat16sr& operator*=(const bfloat16sr& rhs) {
            float v = static_cast<float>(*this) * static_cast<float>(rhs);
            value = round(v);
            return *this;
        }

        /* divide operators */

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        bfloat16sr operator/(const T& rhs) const {
            float v = static_cast<float>(*this) / static_cast<float>(rhs);
            return bfloat16sr(v);
        }

        bfloat16sr operator/(const bfloat16sr& rhs) const {
            float v = static_cast<float>(*this) / static_cast<float>(rhs);
            return bfloat16sr(v);
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        bfloat16sr& operator/=(const T& rhs) {
            float v = static_cast<float>(*this) / static_cast<float>(rhs);
            value = round(v);
            return *this;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        friend bfloat16sr operator/(T lhs, const bfloat16sr& rhs) {
            float v = static_cast<float>(lhs) / static_cast<float>(rhs);
            return bfloat16sr(v);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        bfloat16sr operator/(const T& rhs) const {
            float v = static_cast<float>(*this) / rhs;
            return bfloat16sr(v);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        friend bfloat16sr operator/(T lhs, const bfloat16sr& rhs) {
            float v = lhs / static_cast<float>(rhs);
            return bfloat16sr(v);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        bfloat16sr& operator/=(const T& rhs) {
            float v = static_cast<float>(*this) / rhs;
            round(v);
            return *this;
        }

        bfloat16sr& operator/=(const bfloat16sr& rhs) {
            float v = static_cast<float>(*this) / static_cast<float>(rhs);
            value = round(v);
            return *this;
        }

        /* comparison operators */

        /* less */

        bool operator<(const bfloat16sr& rhs) const {
            return value < rhs.value;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        bool operator<(const T& rhs) const {
            return static_cast<T>(*this) < rhs;
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        bool operator<(const T& rhs) const {
            return static_cast<T>(*this) < rhs;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        friend bool operator<(const T& rhs, const bfloat16sr& lhs) {
            return static_cast<float>(rhs) < static_cast<float>(lhs);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        friend bool operator<(const T& rhs, const bfloat16sr& lhs) {
            return static_cast<float>(rhs) < static_cast<float>(lhs);
        }

        /* greater */

        bool operator>(const bfloat16sr& rhs) const {
            return value > rhs.value;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        bool operator>(const T& rhs) const {
            return static_cast<T>(*this) > rhs;
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        bool operator>(const T& rhs) const {
            return static_cast<T>(*this) > rhs;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        friend bool operator>(const T& rhs, const bfloat16sr& lhs) {
            return static_cast<float>(rhs) > static_cast<float>(lhs);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        friend bool operator>(const T& rhs, const bfloat16sr& lhs) {
            return static_cast<float>(rhs) > static_cast<float>(lhs);
        }

        /* equal */

        bool operator==(const bfloat16sr& rhs) const {
            return value == rhs.value;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        bool operator==(const T& rhs) const {
            return static_cast<T>(*this) == rhs;
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        bool operator==(const T& rhs) const {
            return static_cast<T>(*this) == rhs;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        friend bool operator==(const T& rhs, const bfloat16sr& lhs) {
            return static_cast<float>(rhs) == static_cast<float>(lhs);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        friend bool operator==(const T& rhs, const bfloat16sr& lhs) {
            return static_cast<float>(rhs) == static_cast<float>(lhs);
        }

        /* not equal */
       
        bool operator!=(const bfloat16sr& rhs) const {
            return value != rhs.value;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        bool operator!=(const T& rhs) const {
            return static_cast<T>(*this) != rhs;
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        bool operator!=(const T& rhs) const {
            return static_cast<T>(*this) != rhs;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        friend bool operator!=(const T& rhs, const bfloat16sr& lhs) {
            return static_cast<float>(rhs) != static_cast<float>(lhs);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        friend bool operator!=(const T& rhs, const bfloat16sr& lhs) {
            return static_cast<float>(rhs) != static_cast<float>(lhs);
        }

        /* less or equal */

        bool operator<=(const bfloat16sr& rhs) const {
            return value <= rhs.value;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        bool operator<=(const T& rhs) const {
            return static_cast<T>(*this) <= rhs;
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        bool operator<=(const T& rhs) const {
            return static_cast<T>(*this) <= rhs;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        friend bool operator<=(const T& rhs, const bfloat16sr& lhs) {
            return static_cast<float>(rhs) <= static_cast<float>(lhs);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        friend bool operator<=(const T& rhs, const bfloat16sr& lhs) {
            return static_cast<float>(rhs) <= static_cast<float>(lhs);
        }

        /* greater or equal */

        bool operator>=(const bfloat16sr& rhs) const {
            return value >= rhs.value;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        bool operator>=(const T& rhs) const {
            return static_cast<T>(*this) >= rhs;
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        bool operator>=(const T& rhs) const {
            return static_cast<T>(*this) >= rhs;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        friend bool operator>=(const T& rhs, const bfloat16sr& lhs) {
            return static_cast<float>(rhs) >= static_cast<float>(lhs);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        friend bool operator>=(const T& rhs, const bfloat16sr& lhs) {
            return static_cast<float>(rhs) >= static_cast<float>(lhs);
        }

        /* ostream overload */
        friend std::ostream& operator<<(std::ostream& os, const bfloat16sr& v) {
            os << float(v);
            return os;
        }

        /* Trigonometric functions */
        friend inline bfloat16sr cos(const bfloat16sr&  x)  { return cos(static_cast<float>(x)); }
        friend inline bfloat16sr sin(const bfloat16sr&  x)  { return sin(static_cast<float>(x)); }
        friend inline bfloat16sr tan(const bfloat16sr&  x)  { return tan(static_cast<float>(x)); }
        friend inline bfloat16sr acos(const bfloat16sr&  x)  { return acos(static_cast<float>(x)); }
        friend inline bfloat16sr asin(const bfloat16sr&  x)  { return asin(static_cast<float>(x)); }
        friend inline bfloat16sr atan(const bfloat16sr&  x)  { return atan(static_cast<float>(x)); }

        /* Hyperbolic functions */
        friend inline bfloat16sr cosh(const bfloat16sr&  x)  { return cosh(static_cast<float>(x)); }
        friend inline bfloat16sr sinh(const bfloat16sr&  x)  { return sinh(static_cast<float>(x)); }
        friend inline bfloat16sr tanh(const bfloat16sr&  x)  { return tanh(static_cast<float>(x)); }
        friend inline bfloat16sr acosh(const bfloat16sr&  x)  { return acosh(static_cast<float>(x)); }
        friend inline bfloat16sr asinh(const bfloat16sr&  x)  { return asinh(static_cast<float>(x)); }
        friend inline bfloat16sr atanh(const bfloat16sr&  x)  { return atanh(static_cast<float>(x)); }

        /* Exponential and logarithmic functions */
        friend inline bfloat16sr exp(const bfloat16sr&  x)  { return exp(static_cast<float>(x)); }
        friend inline bfloat16sr log(const bfloat16sr&  x)  { return log(static_cast<float>(x)); }
        friend inline bfloat16sr log10(const bfloat16sr&  x)  { return log10(static_cast<float>(x)); }
        friend inline bfloat16sr logb(const bfloat16sr&  x)  { return logb(static_cast<float>(x)); }

        /* Power functions */
        friend inline bfloat16sr pow(const bfloat16sr&  base, double exponent)  { return pow(static_cast<float>(base), exponent); }
        friend inline bfloat16sr sqrt(const bfloat16sr&  x)  { return sqrt(static_cast<float>(x)); }
        friend inline bfloat16sr cbrt(const bfloat16sr&  x)  { return cbrt(static_cast<float>(x)); }
    
        friend inline bfloat16sr scalbn(const bfloat16sr&  x, int n)  { return scalbn(static_cast<float>(x), n); }

        /* Other functions */
        friend inline bfloat16sr abs(const bfloat16sr&  x)  { return abs(static_cast<float>(x)); }
        friend inline bfloat16sr fabs(const bfloat16sr&  x)  { return fabs(static_cast<float>(x)); }
        friend inline bfloat16sr abs2(const bfloat16sr& x)  { return x*x; }

        friend inline bfloat16sr copysign(const bfloat16sr&  x1, const bfloat16sr& x2)  { return copysign(static_cast<float>(x1), static_cast<float>(x2)); }
        friend inline bfloat16sr fmax(const bfloat16sr&  x1, const bfloat16sr&  x2) { return x1 < x2 ? x1 : x2; }
        friend inline bool isfinite(const bfloat16sr& x) { return true; }

    protected:
        int16_t round(float rhs) {
            int16_t val = 0;
            int32_t rhs_int = reinterpret_cast<int32_t&>(rhs);
            int32_t p = dist16(bint_generator);

            #if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
                memcpy(&val, &rhs, sizeof(val));
            #else
                memcpy(&val, reinterpret_cast<char *>(&rhs) + sizeof(rhs) - sizeof(val), sizeof(val));
            #endif

            if (p < (rhs_int & res16_mask)) {
                val += 1;
            }
            return val;
        }

        int16_t value;
    };
}

namespace Eigen {
    // Inheritance from float is a temporary bad solution. Need specify all NumTraits explicitly
    template<> struct NumTraits<rndcmp::bfloat16sr>: NumTraits<float> {
        typedef rndcmp::bfloat16sr Real;
        typedef rndcmp::bfloat16sr NonInteger;
        typedef rndcmp::bfloat16sr Nested;
        
        enum {
            IsComplex = 0,
            IsInteger = 0,
            IsSigned = 1,
            RequireInitialization = 1,
            ReadCost = 2,
            AddCost = 3,
            MulCost = 3
        };
    };
}

#endif  // RNDCMP_INCLUDE_BFLOAT16SR_HPP_