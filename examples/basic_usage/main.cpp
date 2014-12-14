#include "primegen.h"
#include <gmpxx.h>
#include <utility>
#include <iostream>

using namespace std;

/**
 * @brief Basic usage of primegen library
 */

int main()
{
	cout << "Little demonstration what we can do:" << endl;

	cout << "Random 4096b prime:" << endl;
	// auto i = PrimeGen::Generators::random_prime<mpz, 32, 25>("/dev/urandom");
	cout << "log(2597301101), should be 21.677738704762273: " << endl;
	cout << PrimeGen::Utils::log<uint_fast64_t, 32>(2597301101) << endl;
	// cout << "Is prime (deterministic): " << PrimeGen::Tests::miller_rabin_deterministic(i) << endl;

	cout << "Pseudorandom (seed 256148) 2048b prime:" << endl;
	mpz_class i =  PrimeGen::Generators::pseudo_random_prime<mpz_class, 512, 25>(256148ul);
	cout << i << endl;
	cout << "log: " << endl;
	cout << PrimeGen::Utils::log<mpz_class, 512>(i) << endl;
	cout << PrimeGen::Tests::miller_rabin_deterministic<mpz_class, 512>(i) << endl;

	// cout << "Find next prime for 256148:" << endl;
	// cout << PrimeGen::Generators::next_prime<uint_fast64_t, 25>(256148ul) << endl;

	// cout << "Test for primarity 256148:" << endl;
	// cout << PrimeGen::Tests::miller_rabin(256148ul, 25) << endl;

	return 0;
}
