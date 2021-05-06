#ifndef RNDCMP_INCLUDE_BFLOAT16SR_HPP_
#define RNDCMP_INCLUDE_BFLOAT16SR_HPP_

#include <type_traits>
#include <iostream>
#include <cstring>
#include <random>


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
            float v = static_cast<float>(value) + static_cast<float>(rhs);
            return bfloat16sr(v);
        }

        bfloat16sr operator+(const bfloat16sr& rhs) const {
            float v = static_cast<float>(value) + static_cast<float>(rhs);
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
            float v = static_cast<float>(value) - static_cast<float>(rhs);
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

#endif  // RNDCMP_INCLUDE_BFLOAT16SR_HPP_