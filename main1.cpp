#include <iostream>
#include <limits>
#include <cstdint>
#include <type_traits>
#include <random>
#include <bitset>
#include <cmath>


int64_t m_mask = 0x007fffff;
int64_t s_mask = 0x80000000;
int64_t e_mask = 0x7f800000;
// 29 единиц
int64_t residual_mask = 0x1fffffff;
// 1111111...000, 29 нулей, чтобы убрать отбрасываемую часть
int64_t residual_clearer = ~residual_mask;
int64_t eps = residual_mask + 1;

const int64_t abs_mask = std::numeric_limits<int64_t>::max();
double next_after_float_zero = static_cast<double>(std::nextafter(0.f, 1.f));
int64_t next_after_float_zeroi = reinterpret_cast<int64_t&>(next_after_float_zero);

std::random_device rd;
std::mt19937 gen = std::mt19937(rd());
std::uniform_int_distribution<int64_t> dist = std::uniform_int_distribution<int64_t>(0, residual_mask);

float round_stochastically(double x) {
    int64_t xi64 = reinterpret_cast<int64_t&>(x);
    std::cout << "xi64:         " << std::bitset<64>(xi64) << std::endl;
    // Calc residual (m - tr(m) operation)
    int64_t res = xi64 & residual_mask;
    std::cout << "res:          " << std::bitset<64>(res) << std::endl;
    // Clear residual part
    int64_t xi64_e = xi64 & residual_clearer;
    std::cout << "xi64_cleared: " << std::bitset<64>(xi64_e) << std::endl;
    // Generate random number
    int64_t p = dist(gen);
    int64_t sign_mask = ~std::numeric_limits<int64_t>::max();
    int64_t sign = xi64 & 0x1fffffff;
    std::cout << "p:            " << std::bitset<64>(sign ) << std::endl;
    // Eps
    std::cout << "eps:          " << std::bitset<64>(eps) << std::endl;
    if (p + res >= eps) {
        xi64_e += eps;
    }
    int64_t p_plus_res = p + res;
    std::cout << "p_plus_res:   " << std::bitset<64>(p_plus_res) << std::endl;
    std::cout << "xi64_mod:     " << std::bitset<64>(xi64_e) << std::endl;
    double result = reinterpret_cast<double&>(xi64_e);
    std::cout << "resultdouble: " << result << std::endl;
    std::cout << "resultfloat:  " << static_cast<float>(result) << std::endl;
    float resf = static_cast<float>(result);
    int32_t res_int = reinterpret_cast<int32_t&>(resf);
    std::cout << "float:        " << std::bitset<32>(res_int) << std::endl;
    return static_cast<float>(result);
}

int main() {
    // Example of stochastic float rounding
    double a = 1.0;
    double b = 3.0;
    double x = 1.99999999999;
    std::cout.precision(32);
    std::cout.setf(std::ios::fixed);
    std::cout << static_cast<double>(std::numeric_limits<float>::epsilon()) << std::endl;
    std::cout << std::nextafter(0.f, 1.f) << std::endl;
    std::cout << round_stochastically(x) << std::endl;
    std::cout << x << std::endl;
}