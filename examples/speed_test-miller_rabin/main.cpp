#include "primegen.h"
#include <gmpxx.h>
#include <gmp.h>
#include <utility>
#include <algorithm>
#include <iostream>
#include <chrono>

int main() {
  constexpr size_t iterations = 1000;
  constexpr size_t width = 2048;
  constexpr size_t seed = 254148ul;

  std::cout
      << "This test shows speed comparison with GMP, it uses `miller_rabin` "
         "functions" << std::endl;

  std::cout << "Setup:" << std::endl;
  std::cout << "Iterations: " << iterations << std::endl;
  std::cout << "Number width: " << width << std::endl;
  std::cout << "Random seed: " << seed << std::endl;
  std::cout << std::endl;

  typedef std::chrono::nanoseconds duration_t;

  std::chrono::high_resolution_clock clock;
  std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
  std::minstd_rand rnd(seed);

  {
    std::cout << "--- Testing pure `miller_rabin` tests (composite "
                 "probability "
                 "2^(-50))---" << std::endl;

    duration_t gmp_duration(0);
    duration_t primegen_duration(0);
    mpz_class j;

    for (size_t i = 0; i < iterations; ++i) {
      j = PrimeGen::Utils::independent_bits_generator<
          mpz_class, std::minstd_rand, 2048>(rnd);

      start = clock.now();
      mpz_millerrabin(j.get_mpz_t(), 25);
      end = clock.now();
      gmp_duration += std::chrono::duration_cast<duration_t>(end - start);

      start = clock.now();
      PrimeGen::Tests::miller_rabin<mpz_class, 25>(j);
      end = clock.now();
      primegen_duration += std::chrono::duration_cast<duration_t>(end - start);
    }
    std::cout << "Primegen test took: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     primegen_duration).count() /
                     1000.0 << " seconds" << std::endl;
    std::cout << "GMP test took: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     gmp_duration).count() /
                     1000.0 << " seconds" << std::endl;
    std::cout << std::endl << std::endl;
  }

  {
    std::cout << "--- Testing `miller_rabin` + trivial divisions (composite "
                 "probability "
                 "2^(-50))---" << std::endl;

    duration_t gmp_duration(0);
    duration_t primegen_duration(0);
    mpz_class j;

    for (size_t i = 0; i < iterations; ++i) {
      j = PrimeGen::Utils::independent_bits_generator<
          mpz_class, std::minstd_rand, 2048>(rnd);

      start = clock.now();
      mpz_probab_prime_p(j.get_mpz_t(), 25);
      end = clock.now();
      gmp_duration += std::chrono::duration_cast<duration_t>(end - start);

      start = clock.now();
      PrimeGen::Tests::f1000_prime_factors(j) &&
          PrimeGen::Tests::miller_rabin<mpz_class, 25>(j);
      end = clock.now();
      primegen_duration += std::chrono::duration_cast<duration_t>(end - start);
    }
    std::cout << "Primegen test took: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     primegen_duration).count() /
                     1000.0 << " seconds" << std::endl;
    std::cout << "GMP test took: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     gmp_duration).count() /
                     1000.0 << " seconds" << std::endl;
    std::cout << std::endl << std::endl;
  }

  return 0;
}
