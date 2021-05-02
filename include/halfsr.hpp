#ifndef RNDCMP_INCLUDE_HALFSR_HPP_
#define RNDCMP_INCLUDE_HALFSR_HPP_

#include "half.hpp"
#include <random>


namespace half_float {

    // Мask for 13 low-cut bits for double
    constexpr int64_t res16_mask = 0x1fff;

    static std::random_device half_rd;
    static std::mt19937 int_generator = std::mt19937(half_rd());
    static std::uniform_int_distribution<int32_t> dist32 = std::uniform_int_distribution<int32_t>(0, res16_mask);

    class halfsr: public half {
        public:
            constexpr halfsr() noexcept : half() {}

            halfsr(detail::expr rhs) : half(float2halfsr(static_cast<float>(rhs))) {}

            halfsr(float rhs) : half(float2halfsr(rhs)) {}

            halfsr& operator=(float rhs) { setValue(float2halfsr(rhs)); return *this; }

            halfsr& operator+=(float rhs) { setValue(float2halfsr(static_cast<float>(*this) + rhs)); return *this; }

            halfsr& operator-=(float rhs) { setValue(float2halfsr(static_cast<float>(*this) - rhs)); return *this; }

            halfsr& operator*=(float rhs) { setValue(float2halfsr(static_cast<float>(*this) * rhs)); return *this; }

            halfsr& operator/=(float rhs) { setValue(float2halfsr(static_cast<float>(*this) / rhs)); return *this; }

            halfsr& operator++() { return *this += 1.0f; }

            halfsr& operator--() { return *this -= 1.0f; }

            halfsr operator++(int) { halfsr out(*this); ++*this; return out; }

            halfsr operator--(int) { halfsr out(*this); --*this; return out; }

            template<typename T>
            detail::uint16 float2halfsr(T value) {
                detail::uint16 rounded = detail::float2half<std::round_toward_zero, T>(value);
                bool is_rounding_needed = is_need_round_up(value);
                if (is_rounding_needed) {
                    rounded += 1;
                }
                return rounded;
            }

            friend std::ostream& operator<<(std::ostream& os, const halfsr& v) {
                os << float(v);
                return os;
            }
        private:
            bool is_need_round_up(float x) {
                int32_t x_int = reinterpret_cast<int32_t&>(x);
                int32_t p = dist32(int_generator);
                return p < (x_int & res16_mask);
            }
    };
}

#endif  // RNDCMP_INCLUDE_FIXEDSR_HPP_