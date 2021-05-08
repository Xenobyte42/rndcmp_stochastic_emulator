#ifndef RNDCMP_INCLUDE_BFLOAT16_HPP_
#define RNDCMP_INCLUDE_BFLOAT16_HPP_

#include <type_traits>
#include <iostream>
#include <cstring>
#include <cmath>


namespace rndcmp {
    class bfloat16 {
    public:
        bfloat16(): bfloat16(0.0f) {};

        bfloat16(float rhs): value(round(rhs)) {};

        bfloat16& operator=(const bfloat16& rhs) = default;

        bfloat16& operator=(float rhs) { value = round(rhs); return *this; }

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
        bfloat16 operator+(const T& rhs) const {
            float v = static_cast<float>(value) + static_cast<float>(rhs);
            return bfloat16(v);
        }

        bfloat16 operator+(const bfloat16& rhs) const {
            float v = static_cast<float>(value) + static_cast<float>(rhs);
            return bfloat16(v);
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        friend bfloat16 operator+(T lhs, const bfloat16& rhs) {
            float v = static_cast<float>(lhs) + static_cast<float>(rhs);
            return bfloat16(v);
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        bfloat16& operator+=(const T& rhs) {
            float v = static_cast<float>(*this) + static_cast<float>(rhs);
            value = round(v);
            return *this;
        }

        bfloat16& operator+=(const bfloat16& rhs) {
            float v = static_cast<float>(*this) + static_cast<float>(rhs);
            value = round(v);
            return *this;
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        bfloat16 operator+(const T& rhs) const {
            float v = static_cast<float>(*this) + rhs;
            return bfloat16(v);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        friend bfloat16 operator+(T lhs, const bfloat16& rhs) {
            float v = lhs + static_cast<float>(rhs);
            return bfloat16(v);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        bfloat16& operator+=(const T& rhs) {
            float v = static_cast<float>(*this) + rhs;
            value = round(v);
            return *this;
        }

        /* - operators */

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        bfloat16 operator-(const T& rhs) const {
            float v = static_cast<float>(*this) - static_cast<float>(rhs);
            return bfloat16(v);
        }

        bfloat16 operator-(const bfloat16& rhs) const {
            float v = static_cast<float>(*this) - static_cast<float>(rhs);
            return bfloat16(v);
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        bfloat16& operator-=(const T& rhs) {
            float v = static_cast<float>(*this) - static_cast<float>(rhs);
            value = round(v);
            return *this;
        }

        bfloat16& operator-=(const bfloat16& rhs) {
            float v = static_cast<float>(value) - static_cast<float>(rhs);
            value = round(v);
            return *this;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        friend bfloat16 operator-(T lhs, const bfloat16& rhs) {
            float v = static_cast<float>(lhs) - static_cast<float>(rhs);
            return bfloat16(v);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        bfloat16 operator-(const T& rhs) const {
            float v = static_cast<float>(*this) - static_cast<float>(rhs);
            return bfloat16(v);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        friend bfloat16 operator-(T lhs, const bfloat16& rhs) {
            float v = static_cast<float>(lhs) - static_cast<float>(rhs);
            return bfloat16(v);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        bfloat16& operator-=(const T& rhs) {
            float v = static_cast<float>(*this) - rhs;
            value = round(v);
            return *this;
        }

        // Unary minus
        bfloat16 operator-() const {
            float v = - static_cast<float>(*this);
            return bfloat16(v);
        }

        /* multiply operators */

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        bfloat16 operator*(const T& rhs) const {
            float v = static_cast<float>(*this) * static_cast<float>(rhs);
            return bfloat16(v);
        }

        bfloat16 operator*(const bfloat16& rhs) const {
            float v = static_cast<float>(*this) * static_cast<float>(rhs);
            return bfloat16(v);
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        bfloat16& operator*=(const T& rhs) {
            float v = static_cast<float>(*this) * static_cast<float>(rhs);
            value = round(v);
            return *this;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        friend bfloat16 operator*(T lhs, const bfloat16& rhs) {
            float v = static_cast<float>(lhs) * static_cast<float>(rhs);
            return bfloat16(v);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        bfloat16 operator*(const T& rhs) const {
            float v = static_cast<float>(*this) * rhs;
            return bfloat16(v);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        friend bfloat16 operator*(T lhs, const bfloat16& rhs) {
            float v = lhs * static_cast<float>(rhs);
            return bfloat16(v);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        bfloat16& operator*=(const T& rhs) {
            float v = static_cast<float>(*this) * rhs;
            value = round(v);
            return *this;
        }

        /* divide operators */

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        bfloat16 operator/(const T& rhs) const {
            float v = static_cast<float>(*this) / static_cast<float>(rhs);
            return bfloat16(v);
        }

        bfloat16 operator/(const bfloat16& rhs) const {
            float v = static_cast<float>(*this) / static_cast<float>(rhs);
            return bfloat16(v);
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        bfloat16& operator/=(const T& rhs) {
            float v = static_cast<float>(*this) / static_cast<float>(rhs);
            value = round(v);
            return *this;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        friend bfloat16 operator/(T lhs, const bfloat16& rhs) {
            float v = static_cast<float>(lhs) / static_cast<float>(rhs);
            return bfloat16(v);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        bfloat16 operator/(const T& rhs) const {
            float v = static_cast<float>(*this) / rhs;
            return bfloat16(v);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        friend bfloat16 operator/(T lhs, const bfloat16& rhs) {
            float v = lhs / static_cast<float>(rhs);
            return bfloat16(v);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        bfloat16& operator/=(const T& rhs) {
            float v = static_cast<float>(*this) / rhs;
            round(v);
            return *this;
        }

        /* comparison operators */

        /* less */

        bool operator<(const bfloat16& rhs) const {
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
        friend bool operator<(const T& rhs, const bfloat16& lhs) {
            return static_cast<float>(rhs) < static_cast<float>(lhs);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        friend bool operator<(const T& rhs, const bfloat16& lhs) {
            return static_cast<float>(rhs) < static_cast<float>(lhs);
        }

        /* greater */

        bool operator>(const bfloat16& rhs) const {
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
        friend bool operator>(const T& rhs, const bfloat16& lhs) {
            return static_cast<float>(rhs) > static_cast<float>(lhs);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        friend bool operator>(const T& rhs, const bfloat16& lhs) {
            return static_cast<float>(rhs) > static_cast<float>(lhs);
        }

        /* equal */

        bool operator==(const bfloat16& rhs) const {
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
        friend bool operator==(const T& rhs, const bfloat16& lhs) {
            return static_cast<float>(rhs) == static_cast<float>(lhs);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        friend bool operator==(const T& rhs, const bfloat16& lhs) {
            return static_cast<float>(rhs) == static_cast<float>(lhs);
        }

        /* not equal */
       
        bool operator!=(const bfloat16& rhs) const {
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
        friend bool operator!=(const T& rhs, const bfloat16& lhs) {
            return static_cast<float>(rhs) != static_cast<float>(lhs);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        friend bool operator!=(const T& rhs, const bfloat16& lhs) {
            return static_cast<float>(rhs) != static_cast<float>(lhs);
        }

        /* less or equal */

        bool operator<=(const bfloat16& rhs) const {
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
        friend bool operator<=(const T& rhs, const bfloat16& lhs) {
            return static_cast<float>(rhs) <= static_cast<float>(lhs);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        friend bool operator<=(const T& rhs, const bfloat16& lhs) {
            return static_cast<float>(rhs) <= static_cast<float>(lhs);
        }

        /* greater or equal */

        bool operator>=(const bfloat16& rhs) const {
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
        friend bool operator>=(const T& rhs, const bfloat16& lhs) {
            return static_cast<float>(rhs) >= static_cast<float>(lhs);
        }

        template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        friend bool operator>=(const T& rhs, const bfloat16& lhs) {
            return static_cast<float>(rhs) >= static_cast<float>(lhs);
        }

        /* ostream overload */
        friend std::ostream& operator<<(std::ostream& os, const bfloat16& v) {
            os << float(v);
            return os;
        }

        /* Trigonometric functions */
        friend inline bfloat16 cos(const bfloat16&  x)  { return cos(static_cast<float>(x)); }
        friend inline bfloat16 sin(const bfloat16&  x)  { return sin(static_cast<float>(x)); }
        friend inline bfloat16 tan(const bfloat16&  x)  { return tan(static_cast<float>(x)); }
        friend inline bfloat16 acos(const bfloat16&  x)  { return acos(static_cast<float>(x)); }
        friend inline bfloat16 asin(const bfloat16&  x)  { return asin(static_cast<float>(x)); }
        friend inline bfloat16 atan(const bfloat16&  x)  { return atan(static_cast<float>(x)); }

        /* Hyperbolic functions */
        friend inline bfloat16 cosh(const bfloat16&  x)  { return cosh(static_cast<float>(x)); }
        friend inline bfloat16 sinh(const bfloat16&  x)  { return sinh(static_cast<float>(x)); }
        friend inline bfloat16 tanh(const bfloat16&  x)  { return tanh(static_cast<float>(x)); }
        friend inline bfloat16 acosh(const bfloat16&  x)  { return acosh(static_cast<float>(x)); }
        friend inline bfloat16 asinh(const bfloat16&  x)  { return asinh(static_cast<float>(x)); }
        friend inline bfloat16 atanh(const bfloat16&  x)  { return atanh(static_cast<float>(x)); }

        /* Exponential and logarithmic functions */
        friend inline bfloat16 exp(const bfloat16&  x)  { return exp(static_cast<float>(x)); }
        friend inline bfloat16 log(const bfloat16&  x)  { return log(static_cast<float>(x)); }
        friend inline bfloat16 log10(const bfloat16&  x)  { return log10(static_cast<float>(x)); }

        /* Power functions */
        friend inline bfloat16 pow(const bfloat16&  base, double exponent)  { return pow(static_cast<float>(base), exponent); }
        friend inline bfloat16 sqrt(const bfloat16&  x)  { return sqrt(static_cast<float>(x)); }
        friend inline bfloat16 cbrt(const bfloat16&  x)  { return cbrt(static_cast<float>(x)); }

        /* Other functions */
        friend inline bfloat16 abs(const bfloat16&  x)  { return abs(static_cast<float>(x)); }
        friend inline bfloat16 fabs(const bfloat16&  x)  { return fabs(static_cast<float>(x)); }
        friend inline bfloat16 abs2(const bfloat16& x)  { return x*x; }

    protected:
        int16_t round(float rhs) {
            int16_t val = 0;

            // Magic value for rounding to nearest (simply just push bottom bits into the upper)
            rhs *= 1.001957f;
            #if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
                memcpy(&val, &rhs, sizeof(val));
            #else
                memcpy(&val, reinterpret_cast<char *>(&rhs) + sizeof(rhs) - sizeof(val), sizeof(val));
            #endif
            return val;
        }

        int16_t value;
    };
}

#endif  // RNDCMP_INCLUDE_BFLOAT16_HPP_