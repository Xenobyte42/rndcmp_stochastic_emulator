#include <iostream>
#include <cstdint>
#include "types.hpp"
#include "integrator.hpp"
#include "esn.hpp"

/* DELETE THIS FILE IN FUTURE AND USE ONLY FOR CUSTOM TESTS */

int main() {
    size_t seed = 42;

    rndcmp::ESN<rndcmp::FloatSR, 2, 10, 2> net(
        0.95,   // spectral radius
        0.2,    // sparsity
        seed    // random seed
    );
}