#include "primegen.h"
#include <gmpxx.h>
#include <utility>
#include <iostream>

using namespace std;

/**
 * @brief Basic usage of primegen library
 */

int main() {
  cout << "Little demonstration what we can do:" << endl;

  cout << "Find next prime for 256148:" << endl;
  cout << PrimeGen::Generators::next_prime<uint_fast64_t, 25>(256148ul) << endl;

  cout << "Test for primarity 256148 (probabilistic):" << endl;
  cout << PrimeGen::Tests::miller_rabin<uint_fast64_t, 25>(256148ul) << endl;

  cout << "Test for primarity 256148 (deterministic):" << endl;
  cout << PrimeGen::Tests::miller_rabin_deterministic(256148ul) << endl;

  cout << "Pseudorandom (seed 256148) 2048b prime:" << endl;
  PrimeGen::Generators::pseudo_random_prime_engine<mpz_class, 2048> pseudo_2048(
      256148ul);
  cout << pseudo_2048() << endl;

  cout << "Random 4096b prime:" << endl;
  PrimeGen::Generators::truly_random_prime_engine<mpz_class, 4096> random_4096(
      "/dev/urandom");
  cout << random_4096() << endl;

  return 0;
}
