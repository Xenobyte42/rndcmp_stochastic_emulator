#ifndef RNDCMP_INCLUDE_FIXED_HPP_
#define RNDCMP_INCLUDE_FIXED_HPP_

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

        /* ostream overload */
        friend std::ostream& operator<<(std::ostream& os, const Fixed& v) {
            os << double(v);
            return os;
        }

    protected:
        INT_T value;
    private:
        template<typename T>
        void setValueFromT(T v) {
            value = static_cast<INT_T>(v * (1 << FRACT_SIZE));
        }
    };
}

#endif  // RNDCMP_INCLUDE_FIXED_HPP_
