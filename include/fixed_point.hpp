#ifndef RNDCMP_INCLUDE_FIXED_POINT_HPP_
#define RNDCMP_INCLUDE_FIXED_POINT_HPP_

#include <type_traits>

namespace rndcmp {

    template<typename INT_T, int FRACT_SIZE = 0>
    class FixedPoint {
    public:
        template<typename T>
        FixedPoint(T value, std::enable_if_t<std::is_floating_point<T>::value, bool> = true) {
            value = static_cast<INT_T>(value * FRACT_SIZE);
        }

    private:
        INT_T value;
    };

}

#endif  // RNDCMP_INCLUDE_FIXED_POINT_HPP_