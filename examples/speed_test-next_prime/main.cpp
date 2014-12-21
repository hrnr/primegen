#include "primegen.h"
#include <gmpxx.h>
#include <gmp.h>
#include <utility>
#include <algorithm>
#include <iostream>
#include <chrono>

int main() {
  constexpr size_t iterations = 10;
  constexpr size_t width = 2048;
  constexpr size_t seed = 254148ul;

  std::cout
      << "This test shows speed comparison with GMP, it uses `next_prime` "
         "functions" << std::endl;

  std::cout << "Setup:" << std::endl;
  std::cout << "Iterations: " << iterations << std::endl;
  std::cout << "Number width: " << width << std::endl;
  std::cout << "Random seed: " << seed << std::endl;
  std::cout << std::endl;

  std::chrono::high_resolution_clock clock;
  std::chrono::time_point<std::chrono::high_resolution_clock> start, end;

  /* number to start with */
  PrimeGen::Generators::pseudo_random_prime_engine<mpz_class, width> pseudo_p(
      seed);
  mpz_class i_prime = pseudo_p();

  {
    std::cout << "--- Running test on GMP library (composite probability "
                 "2^(-50))---" << std::endl;
    mpz_class j = i_prime;

    start = clock.now();
    for (size_t i = 0; i < iterations; ++i) {
      mpz_nextprime(j.get_mpz_t(), j.get_mpz_t());
    }
    end = clock.now();
    std::cout << "Test took: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     end - start).count() /
                     1000.0 << " seconds" << std::endl;
    std::cout << std::endl << std::endl;
  }

  {
    std::cout << "--- Running test on primegen library (composite probability "
                 "2^(-10)) ---" << std::endl;
    mpz_class j = i_prime;

    start = clock.now();
    for (size_t i = 0; i < iterations; ++i) {
      j = PrimeGen::Generators::next_prime<mpz_class, 5>(j);
    }
    end = clock.now();
    std::cout << "Test took: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     end - start).count() /
                     1000.0 << " seconds" << std::endl;
    std::cout << std::endl << std::endl;
  }

  {
    std::cout << "--- Running test on primegen library (composite probability "
                 "2^(-50)) ---" << std::endl;
    mpz_class j = i_prime;

    start = clock.now();
    for (size_t i = 0; i < iterations; ++i) {
      j = PrimeGen::Generators::next_prime<mpz_class, 25>(j);
    }
    end = clock.now();
    std::cout << "Test took: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     end - start).count() /
                     1000.0 << " seconds" << std::endl;
    std::cout << std::endl << std::endl;
  }

  return 0;
}
