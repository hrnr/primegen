#include "primegen.h"
#include <gmpxx.h>
#include <utility>
#include <algorithm>
#include <iostream>

using namespace std;

/**
 * @brief Test test show how accurate is miller-rabin probabilistic
 * test
 */

int main() {
  constexpr size_t iterations = 10000;
  constexpr size_t width = 512;
  constexpr size_t accuracy = 1;
  constexpr size_t seed = 254148ul;

  cout << "This test shows accuracy of miller-rabin probabilistic test:"
       << endl;

  cout << "Setup:" << endl;
  cout << "Iterations: " << iterations << endl;
  cout << "Number width: " << width << endl;
  cout << "Miller-rabin accuracy: " << accuracy << endl;
  cout << "Random seed: " << seed << endl;
  cout << endl;

  {
    cout << "--- Running test on randomly generated ints ---" << endl;
    std::minstd_rand rnd(seed);
    size_t probabilistic_count = 0;
    size_t deterministic_count = 0;
    for (size_t i = 0; i < iterations; ++i) {
      mpz_class p = PrimeGen::Utils::independent_bits_generator<
          mpz_class, std::minstd_rand, width>(rnd);
      if (PrimeGen::Tests::miller_rabin<mpz_class, accuracy>(p))
        ++probabilistic_count;
      // lets pretend this is deterministic test
      if (PrimeGen::Tests::miller_rabin<mpz_class, 25>(p))
        ++deterministic_count;
      if ((i % (iterations / 10)) == 0)
        cout << (i * 100 / double(iterations)) << "% iterations done\r"
             << flush;
    }
    cout << endl << endl;
    cout << "Total primes: " << deterministic_count << endl;
    cout << "False-positives: " << probabilistic_count - deterministic_count
         << endl;
    cout << "False-positives rate: "
         << (deterministic_count != 0
                 ? double(probabilistic_count - deterministic_count) * 100 /
                       deterministic_count
                 : 0) << "%" << endl;
    cout << endl;
  }

  {
    std::minstd_rand rnd(seed);
    mpz_class p = PrimeGen::Utils::independent_bits_generator<
        mpz_class, std::minstd_rand, width>(rnd);
    cout << "--- Running test on interval [" << p << ", " << p + iterations
         << "] ---" << endl;
    size_t probabilistic_count = 0;
    size_t deterministic_count = 0;
    for (size_t i = 0; i < iterations; ++i, ++p) {
      if (PrimeGen::Tests::miller_rabin<mpz_class, accuracy>(p))
        ++probabilistic_count;
      // lets pretend this is deterministic test
      if (PrimeGen::Tests::miller_rabin<mpz_class, 25>(p))
        ++deterministic_count;
      if ((i % (iterations / 10)) == 0)
        cout << (i * 100 / double(iterations)) << "% iterations done\r"
             << flush;
    }
    cout << endl << endl;
    cout << "Total primes: " << deterministic_count << endl;
    cout << "False-positives: " << probabilistic_count - deterministic_count
         << endl;
    cout << "False-positives rate: "
         << (deterministic_count != 0
                 ? double(probabilistic_count - deterministic_count) * 100 /
                       deterministic_count
                 : 0) << "%" << endl;
    cout << endl;
  }

  {
    std::minstd_rand rnd(seed);
    mpz_class p = PrimeGen::Utils::independent_bits_generator<
        mpz_class, std::minstd_rand, width>(rnd);
    cout << "Running with fully deterministic test - this may take long"
         << endl;
    cout << "--- Running test on interval [" << p << ", " << p + iterations
         << "] ---" << endl;
    size_t probabilistic_count = 0;
    size_t deterministic_count = 0;
    for (size_t i = 0; i < iterations; ++i, ++p) {
      if (PrimeGen::Tests::miller_rabin<mpz_class, accuracy>(p))
        ++probabilistic_count;
      if (PrimeGen::Tests::miller_rabin_deterministic<mpz_class, width>(p))
        ++deterministic_count;
      if ((i % (iterations / 10)) == 0)
        cout << (i * 100 / double(iterations)) << "% iterations done\r"
             << flush;
    }
    cout << endl << endl;
    cout << "Total primes: " << deterministic_count << endl;
    cout << "False-positives: " << probabilistic_count - deterministic_count
         << endl;
    cout << "False-positives rate: "
         << (deterministic_count != 0
                 ? double(probabilistic_count - deterministic_count) * 100 /
                       deterministic_count
                 : 0) << "%" << endl;
    cout << endl;
  }

  return 0;
}
