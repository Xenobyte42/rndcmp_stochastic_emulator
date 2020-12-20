#ifndef RNDCMP_INCLUDE_FIXED_POINT_HPP_
#define RNDCMP_INCLUDE_FIXED_POINT_HPP_

#include <type_traits>
#include <cmath>
#include <random>


namespace rndcmp {
    
    static std::default_random_engine generator = std::default_random_engine();
    static std::uniform_real_distribution distribution = std::uniform_real_distribution<double>(0.0,1.0);

    template<typename INT_T, int FRACT_SIZE = 0, int POW = 2>
    class FixedPoint {
    public:
        FixedPoint() = default;

        /* constructors */

        template<typename T>
        FixedPoint(T v, std::enable_if_t<std::is_floating_point<T>::value, bool> = true) {
            setValueFromT(v);
        }

        FixedPoint(INT_T v):
        value(v) {}

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        operator T() const {
            return static_cast<T>(value) / (1 << FRACT_SIZE);
        }

        /* + operators */

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        FixedPoint operator+(const T& rhs) const {
            return FixedPoint<INT_T, FRACT_SIZE, POW> (T(*this) + rhs);
        }

        FixedPoint operator+(const FixedPoint& rhs) {
            return FixedPoint<INT_T, FRACT_SIZE, POW> (value + rhs.value);
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        FixedPoint& operator+=(const T& rhs) {
            T sum = T(*this) + rhs;
            setValueFromT<T>(sum);
            return *this;
        }

        FixedPoint& operator+=(const FixedPoint& rhs) {
            value += rhs.value;
            return *this;
        }

        /* - operators */

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        FixedPoint operator-(const T& rhs) const {
            return FixedPoint<INT_T, FRACT_SIZE, POW> (T(*this) - rhs);
        }

        FixedPoint operator-(const FixedPoint& rhs) {
            return FixedPoint<INT_T, FRACT_SIZE, POW> (value - rhs.value);
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        FixedPoint& operator-=(const T& rhs) {
            T sub = T(*this) - rhs;
            setValueFromT<T>(sub);
            return *this;
        }

        FixedPoint& operator-=(const FixedPoint& rhs) {
            value -= rhs.value;
            return *this;
        }

        /* multiply and divide operators */

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        FixedPoint operator*(const T& rhs) const {
            return FixedPoint<INT_T, FRACT_SIZE, POW> (T(*this) * rhs);
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        FixedPoint& operator*=(const T& rhs) {
            T mul = T(*this) * rhs;
            setValueFromT<T>(mul);
            return *this;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        FixedPoint operator/(const T& rhs) const {
            return FixedPoint<INT_T, FRACT_SIZE, POW> (T(*this) / rhs);
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        FixedPoint& operator/=(const T& rhs) {
            T div = T(*this) / rhs;
            setValueFromT<T>(div);
            return *this;
        }

    protected:
        INT_T value;
    private:
        template<typename T>
        void setValueFromT(T v) {
            value = static_cast<INT_T>(v * (1 << FRACT_SIZE));
        }
    };

    template<typename INT_T, int FRACT_SIZE = 0, int POW = 2>
    class FixedPointSR: public FixedPoint<INT_T, FRACT_SIZE, POW> {
    public:
        using FixedPoint<INT_T, FRACT_SIZE, POW>::value;

        /* Constructors */

        template<typename T>
        FixedPointSR(T v, std::enable_if_t<std::is_floating_point<T>::value, bool> = true) {
            setValueFromT<T>(v);
        }

        FixedPointSR(INT_T v) {
            value = v;
        }

        /* + operators */

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        FixedPointSR operator+(const T& rhs) const {
            return FixedPointSR<INT_T, FRACT_SIZE, POW> (T(*this) + rhs);
        }

        FixedPointSR operator+(const FixedPointSR& rhs) {
            return FixedPointSR<INT_T, FRACT_SIZE, POW> (value + rhs.value);
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        FixedPointSR& operator+=(const T& rhs) {
            T sum = T(*this) + rhs;
            setValueFromT<T>(sum);
            return *this;
        }

        FixedPointSR& operator+=(const FixedPointSR& rhs) {
            value += rhs.value;
            return *this;
        }

        /* - operators */

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        FixedPointSR operator-(const T& rhs) const {
            return FixedPointSR<INT_T, FRACT_SIZE, POW> (T(*this) - rhs);
        }

        FixedPointSR operator-(const FixedPointSR& rhs) {
            return FixedPointSR<INT_T, FRACT_SIZE, POW> (value - rhs.value);
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        FixedPointSR& operator-=(const T& rhs) {
            T sub = T(*this) - rhs;
            setValueFromT<T>(sub);
            return *this;
        }

        FixedPointSR& operator-=(const FixedPointSR& rhs) {
            value -= rhs.value;
            return *this;
        }

        /* multiply and divide operators */

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        FixedPointSR operator*(const T& rhs) const {
            return FixedPointSR<INT_T, FRACT_SIZE, POW> (T(*this) * rhs);
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        FixedPointSR& operator*=(const T& rhs) {
            T mul = T(*this) * rhs;
            setValueFromT<T>(mul);
            return *this;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        FixedPointSR operator/(const T& rhs) const {
            return FixedPointSR<INT_T, FRACT_SIZE, POW> (T(*this) / rhs);
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        FixedPointSR& operator/=(const T& rhs) {
            T div = T(*this) / rhs;
            setValueFromT<T>(div);
            return *this;
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

#endif  // RNDCMP_INCLUDE_FIXED_POINT_HPP_