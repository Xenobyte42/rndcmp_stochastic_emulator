#ifndef RNDCMP_INCLUDE_FIXED_POINT_HPP_
#define RNDCMP_INCLUDE_FIXED_POINT_HPP_

#include <type_traits>
#include <cmath>
#include <random>

namespace rndcmp {
    
    /* TODO: стоит пробрасывать генератор в шаблон также, как и POW */
    std::default_random_engine generator = std::default_random_engine();
    std::uniform_real_distribution distribution = std::uniform_real_distribution<double>(0.0,1.0);

    template<typename INT_T, int FRACT_SIZE = 0, int POW = 2>
    class FixedPoint {
    public:
        FixedPoint() = default;
        template<typename T>
        FixedPoint(T v, std::enable_if_t<std::is_floating_point<T>::value, bool> = true) {
            value = static_cast<INT_T>(v * std::pow(POW, FRACT_SIZE));
        }

        FixedPoint(INT_T v):
        value(v) {}

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
        operator T() {
            return static_cast<T>(value) / std::pow(POW, FRACT_SIZE);
        }
    protected:
        INT_T value;
    };

    template<typename INT_T, int FRACT_SIZE = 0, int POW = 2>
    class FixedPointSR: public FixedPoint<INT_T, FRACT_SIZE, POW> {
    public:
        using FixedPoint<INT_T, FRACT_SIZE, POW>::value;

        /* TODO(Xenobyte42): удалить этот комментарий позднее и порефакторить код */
        template<typename T>
        FixedPointSR(T v, std::enable_if_t<std::is_floating_point<T>::value, bool> = true) {
            // В кратце, мы переводим число в fixed point путем домножения на 2^fract_bit_count
            // Реализация без SR просто кастит этот fp к инту, отрезая дробную часть
            // SR берет дробную часть получившегося числа (которая обрежется при касте)
            // И с помощью сгенерированного treshold, который по сути является вероятностью
            // округляет int либо в большую (прибавляем 1), либо в меньшую сторону (оставляем как есть)
            T powed = v * std::pow(POW, FRACT_SIZE);
            T int_part(0.0);
            T fractional_part = std::modf(powed, &int_part);
            double treshold = distribution(generator);
            value = static_cast<INT_T>(powed);
            if (fractional_part > treshold) {
                value += 1;
            }
        }
    }; 

}

#endif  // RNDCMP_INCLUDE_FIXED_POINT_HPP_