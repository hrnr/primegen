#include "primegen.h"
#include <gmpxx.h>
#include <utility>
#include <iostream>

/**
 * @brief Basic usage of primegen library
 */

int main() {
  std::cout << "Little demonstration what we can do:" << std::endl;

  std::cout << "Find next prime for 256148:" << std::endl;
  std::cout << PrimeGen::Generators::next_prime<uint_fast64_t, 25>(256148ul)
            << std::endl;

  std::cout << "Test for primarity 256148 (probabilistic):" << std::endl;
  std::cout << PrimeGen::Tests::miller_rabin<uint_fast64_t, 25>(256148ul)
            << std::endl;

  std::cout << "Test for primarity 256148 (deterministic):" << std::endl;
  std::cout << PrimeGen::Tests::miller_rabin_deterministic(256148ul)
            << std::endl;

  std::cout << "Pseudorandom (seed 256148) 2048b prime:" << std::endl;
  PrimeGen::Generators::pseudo_random_prime_engine<mpz_class, 2048> pseudo_2048(
      256148ul);
  std::cout << pseudo_2048() << std::endl;

  std::cout << "Random 4096b prime:" << std::endl;
  PrimeGen::Generators::truly_random_prime_engine<mpz_class, 4096> random_4096(
      "/dev/urandom");
  std::cout << random_4096() << std::endl;

  return 0;
}
