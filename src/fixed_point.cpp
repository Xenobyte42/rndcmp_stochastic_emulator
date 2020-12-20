#include <fixed_point.hpp>


namespace rndcmp {

    // template<typename INT_T, int FRACT_SIZE, int POW>
    // template<typename T>
    // FixedPointSR<INT_T, FRACT_SIZE, POW>::FixedPointSR(T v, std::enable_if_t<std::is_floating_point<T>::value, bool>) {
    //     setValueFromT<T>(v);
    // }

    // template<typename INT_T, int FRACT_SIZE, int POW>
    // template<typename T>
    // void FixedPointSR<INT_T, FRACT_SIZE, POW>::setValueFromT(T v) {
    //     T powed = v * (1 << FRACT_SIZE);

    //     T int_part(0.0);
    //     T fractional_part = std::modf(powed, &int_part);
    //     double treshold = distribution(generator);
    //     value = static_cast<INT_T>(powed);
    //     if ((fractional_part > treshold) && (fractional_part >= 0)) {
    //         value += 1;
    //     } else if ((fractional_part < 0) && (std::fabs(fractional_part) < treshold)) {
    //         value -= 1;
    //     }
    // }
}