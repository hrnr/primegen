#ifndef PRIMEGEN_H_
#define PRIMEGEN_H_

#include <utility>
#include <random>
#include <algorithm>
#include <sstream>
#include <iostream>
#include "known_primes.h"

/* DEFINITIONS */

/**
 * @mainpage PrimeGen – Library for generating prime numbers
 * 
 * @author Jiri Horner
 * 
 * @version 1.1
 * @date 2014
 * @copyright MIT License
 * 
 * @details Template library providing functions for prime numbers generation.
 * 
 * @section bignums Working with big numbers
 * 
 * Instead of standard unsigned integer types, any user-defined class may be used for \c UIntType. Class must define at least <tt>= + & ++ (prefix) == < != > % >> << - *</tt> operators and must provide sqrt(UIntType n) function (callable with ADE), with the same behavior they have with standard unsigned integer types and must be interoperable with standard unsigned integer types. All library functions have been tested with GNU MP Bignum Library's \c mpz_class. 
 */

namespace PrimeGen
{
	/**
	 * @brief Prime generators
	 */
	namespace Generators
	{
		/**
		 * @brief Random prime generator
		 * @details Random prime will be generated using \c std::random_device.
		 * 
		 * @tparam UIntType Unsigned integer type. Must be able to hold 2 times maximum of \c w. (If \c w is 32 \c UIntType must be able to hold 64b numbers.)
		 * @tparam w Size of number to generate in bits. Generated number will be alway greater than \f$ 2^{w-1} \f$. \c w must be greater than 2.
		 * @tparam accuracy Since probabilistic test is used for primarity testing, this parameter determines accuracy of the test. Reasonable values are \b 25 – 50 which gives probability of false-positive composite lower than \f$ \frac{1}{4^{25}} \f$ while test is still reasonably fast.
		 * 
		 * @see Tests::miller_rabin
		 * 
		 * @param token Token passed to \c std::random_device. This parameter is implementation-defined. Typical implementation on a Linux system, for example, expects token to be the name of a character device that produces random numbers when read from, with the default value \c "/dev/urandom". If nothing provided \c "default" is used which should represent system-valuable source of randomness.
		 * 
		 * @return Randomly (randomness depends on random device represented by provided \c token) generated prime number.
		 */
		template <class UIntType, size_t w, uint_fast32_t accuracy> UIntType random_prime (const std::string& token = "default");

		/**
		 * @brief Pseudorandom prime generator
		 * @details Pseudorandom prime will be generated using \c std::minstd_rand.
		 * 
		 * @tparam UIntType Unsigned integer type. Must be able to hold 2 times maximum of \c w. (If \c w is 32 \c UIntType must be able to hold 64b numbers.)
		 * @tparam w Size of number to generate in bits. Generated number will be alway greater than \f$ 2^{w-1} \f$. \c w must be greater than 2.
		 * @tparam accuracy Since probabilistic test is used for primarity testing, this parameter determines accuracy of the test. Reasonable values are \b 25 – 50 which gives probability of false-positive composite lower than \f$ \frac{1}{4^{25}} \f$ while test is still reasonably fast.
		 * 
		 * @see Tests::miller_rabin
		 * 
		 * @param seed Initial seed passed to random engine.
		 * 
		 * @return Pseudorandom prime number.
		 */
		template <class UIntType, size_t w, uint_fast32_t accuracy> UIntType pseudo_random_prime (const uint_fast32_t& seed);

		/**
		 * @brief Generates next prime greater than \c n
		 * 
		 * @tparam UIntType Unsigned integer type. Must be able to hold 2 times size of \c result. Too bad no theory can estimate how exactly this prime will be big. From probabilistic theory you are pretty safe if \c UIntType can hold \f$ 3 \times (n + \ln(n)) \f$.
		 * @tparam accuracy Since probabilistic test is used for primarity testing, this parameter determines accuracy of the test. Reasonable values are \b 25 – 50 which gives probability of false-positive composite lower than \f$ \frac{1}{4^{25}} \f$ while test is still reasonably fast.
		 * 
		 * @see Tests::miller_rabin
		 * 
		 * @param n Generated prime will be greater than \c n. \c n must be greater than 3.
		 * 
		 * @return Prime greater than \c n. There should be no other primes between \c n and generated prime (see \c accuracy).
		 */
		template <class UIntType, uint_fast32_t accuracy> UIntType next_prime (UIntType n);
	}

	/**
	 * @brief Primality tests
	 */
	namespace Tests
	{
		/**
		 * @brief Miller-Rabin probabilistic primality test.
		 *
		 * @tparam UIntType Unsigned integer type. Must be able to hold 2 times size of \c n. (Even if \c n would fit in 32b type \c UIntType must be able to hold 64b number.)
		 *
		 * @param n Number to be tested for primality. Must be greater than 3.
		 * @param accuracy Since this is only probabilistic test, test has its accuracy determined by this parameter. Probability of false-positive match is only \f$ \frac{1}{4^{accuracy}} \f$. Prime will be always determined as prime. Reasonable values are 25 – 50 which gives probability of false-positive composite lower than \f$ \frac{1}{4^{25}} \f$ while test is still reasonably fast.
		 *
		 * @return \c true if number is probable prime, \c false if number is definitely composite.
		 *
		 */
		template <class UIntType> bool miller_rabin (const UIntType& n, const uint_fast32_t& accuracy);

		/**
		 * @brief Miller-Rabin deterministic primality test.
		 *
		 * @details This test depends on (unproved in time of writting) generalized Riemann hypothesis. Don't use this test if dependency on unproved theories is unaccetable for you.
		 * 
		 * @tparam UIntType Unsigned integer type. Must be able to hold 2 times size of \c n. (Even if \c n would fit in 32b type \c UIntType must be able to hold 64b number.)
		 *
		 * @param n Number to be tested for primality. Must be greater than 3.
		 *
		 * @return \c true if number is probable prime, \c false if number is definitely composite.
		 *
 		 */
		template <class UIntType, size_t w> bool miller_rabin_deterministic (const UIntType& n);

		/**
		 * @brief Quick test, testing only first 100 prime factors.
		 *
		 * @tparam UIntType Unsigned integer type.
		 *
		 * @param n number to be tested for primality
		 *
		 * @return \c true if no prime factor was found, \c false otherwise. This test does not guarantee number to be prime, it should be used only together with other tests or for testing very small numbers.
		 *
		 */
		template <class UIntType> bool f100_prime_factors (const UIntType& n);

		/**
		 * @brief Quick test, testing only first 1000 prime factors.
		 *
		 * @tparam UIntType Unsigned integer type.
		 *
		 * @param n number to be tested for primarity
		 *
		 * @return \c true if no prime factor was found, \c false otherwise. This test does not guarantee number to be prime, it should be used only together with other tests or for testing very small numbers.
		 *
		 */
		template <class UIntType> bool f1000_prime_factors (const UIntType& n);
	}

	/**
	 * @brief Various arithmetic functions used in library algorithms
	 */
	namespace Utils
	{
		/**
		 * @brief Factorize powers of 2 from n
		 *
		 * @tparam UIntType Unsigned integer type.
		 *
		 * @param n number to be factorized
		 *
		 * @return std::pair (s, d) where s, d holds \f$ n = 2^{s} \times d \f$
		 *
		 */
		template <class UIntType> std::pair<UIntType, UIntType> fac_2_powers (const UIntType& n);

		/**
		 * @brief Exponentiation over a modulo. Exponentiation will be done by repeated squaring.
		 *
		 * @tparam UIntType Unsigned integer type. Must be able to hold 2 times size of \c base and \c mod. (Even if \c base would fit in 32b type \c UIntType must be able to hold 64b number.)
		 *
		 * @param base
		 * @param exp exponent
		 * @param mod modulo
		 *
		 * @return \f$ ({base}^{exponent}) \% modulo \f$
		 *
		 */
		template <class UIntType> UIntType pow_mod (UIntType base, UIntType exp, const UIntType& mod);

		template <class UIntType, size_t w> double log (const UIntType& n);

		/**
		 * @brief Generates random number using provided engine. Randomness of generated number depends on randomness of provided engine.
		 *
		 * @tparam UIntType Unsigned integer type. Must be able to hold \c w long numbers
		 * @tparam EngineType Function support all standard engine types defined in \c \<random\>, including	\c std::random_device. (Hence all classes generating 32b numbers with \c () operator should work). Internal state of engine will be modified. Engine must be initialized and provide \c () operator generating 32b numbers.
		 * @tparam w size of number to generate in bits
		 *
		 * @param _32b_generator Initialized number generator
		 *
		 * @return std::pair (s, d) where s, d holds \f$ n = 2^{s} \times d \f$
		 *
		 */
		template <class UIntType, class EngineType, size_t w> UIntType independent_bits_generator (EngineType& _32b_generator);
	}
}


/* IMPLEMENTATION */

namespace PrimeGen
{
	namespace Generators
	{
		template <class UIntType, size_t w, uint_fast32_t accuracy>
		UIntType random_prime (const std::string& token)
		{
			std::random_device random_32b_generator (token);
			UIntType prime_candidate = Utils::independent_bits_generator<UIntType, std::random_device, w> (random_32b_generator);
			prime_candidate = prime_candidate | 1; // we need odd number
			while (true)
			{
				prime_candidate = prime_candidate + 2;
				prime_candidate = prime_candidate | (1u << (w-1)); // we want big primes
				if (Tests::f1000_prime_factors(prime_candidate) && Tests::miller_rabin(prime_candidate, accuracy))
				{
					return prime_candidate;
				}
			}
		}

		template <class UIntType, size_t w, uint_fast32_t accuracy>
		UIntType pseudo_random_prime (const uint_fast32_t& seed)
		{
			std::minstd_rand standard_32b_generator (seed);
			UIntType prime_candidate = Utils::independent_bits_generator<UIntType, std::minstd_rand, w> (standard_32b_generator);
			prime_candidate = prime_candidate | 1; // we need odd number
			while (true)
			{
				prime_candidate = prime_candidate + 2;
				prime_candidate = prime_candidate | (1u << (w-1)); // we want big primes
				if (Tests::f1000_prime_factors(prime_candidate) && Tests::miller_rabin(prime_candidate, accuracy))
				{
					return prime_candidate;
				}
			}
		}

		template <class UIntType, uint_fast32_t accuracy>
		UIntType next_prime (UIntType n)
		{
			n = n | 1;
			while (true)
			{
				n = n + 2;
				if (Tests::f1000_prime_factors(n) && Tests::miller_rabin(n, accuracy))
				{
					return n;
				}
			}
		}
	}
	namespace Tests
	{
		template <class UIntType>
		bool miller_rabin (const UIntType& n, const uint_fast32_t& accuracy)
		{
			std::random_device rd;
			UIntType witness = rd();
			std::pair<UIntType, UIntType> factors = Utils::fac_2_powers<UIntType>(n-1); // factors in format 2^first * second
			for (uint_fast32_t i = 0; i < accuracy; ++i)
			{
				// @todo check if we are getting something close to uniform distribution
				witness = ((witness * 48271) % (n-4)) + 2; // generates witnesses from interval [2, n-2]
				UIntType x = Utils::pow_mod(witness, factors.second, n);
				if (x == 1 || x == n-1)
				{
					continue;
				}
				for (UIntType j = 1; j < factors.first; ++j)
				{
					x = (x * x) % n;
					if (x == 1 || x == n-1)
					{
						break;
					}
				}
				if (x != n-1)
				{
					return false;
				}
			}
			return true;
		}

		template <class UIntType, size_t w>
		bool miller_rabin_deterministic (const UIntType& n)
		{
			UIntType witness;
			std::pair<UIntType, UIntType> factors = Utils::fac_2_powers<UIntType>(n-1); // factors in format 2^first * second

			// check for all generators of (Z/nZ)* (witness for n must be one of them)
			// according to GRH, generators must be in [2, min(n-1, floor(2*(ln n)^2))]
			
			// calculate log 
			double n_log = Utils::log<UIntType, w>(n);
			UIntType upper_bound = static_cast<UIntType>(2*n_log*n_log);
			std::cout << upper_bound << std::endl;
			upper_bound = (n-1) < upper_bound ? n-1 : upper_bound;
			for (witness = 2; witness <= upper_bound; ++witness)
			{
				std::cout << witness << " : " << upper_bound << " : " << n << std::endl;
				UIntType x = Utils::pow_mod(witness, factors.second, n);
				if (x == 1 || x == n-1)
				{
					continue;
				}
				for (UIntType j = 1; j < factors.first; ++j)
				{
					x = (x * x) % n;
					if (x == 1 || x == n-1)
					{
						break;
					}
				}
				if (x != n-1)
				{
					return false;
				}
			}
			return true;
		}

		template <class UIntType>
		bool f100_prime_factors (const UIntType& n)
		{
			for (const uint_fast32_t& i : KnownPrimes::first_100_primes)
			{
				if (n%i == 0 && n != i)
				{
					return false;
				}
			}
			return true;
		}

		template <class UIntType>
		bool f1000_prime_factors (const UIntType& n)
		{
			for (const uint_fast32_t& i : KnownPrimes::first_1000_primes)
			{
				if (n%i == 0 && n != i)
				{
					return false;
				}
			}
			return true;
		}
	}

	namespace Utils
	{
		template <class UIntType>
		std::pair<UIntType, UIntType> fac_2_powers (const UIntType& n)
		{
			std::pair<UIntType, UIntType> factored (0, n);
			while ((factored.second & 1) == 0) // if even
			{
				factored.second = factored.second >> 1;
				++factored.first;
			}
			return factored;
		}

		template <class UIntType>
		UIntType pow_mod (UIntType base, UIntType exp, const UIntType& mod)
		{
			UIntType result = 1;
			while (exp > 0)
			{
				if ((exp & 1) == 1) // if odd
				{
					result = (result * base) % mod;
				}
				base = (base * base) % mod;
				exp = exp >> 1;
			}
			return result;
		}

		template <class UIntType, size_t w> double log (const UIntType& n) {
			constexpr size_t w_64 = std::numeric_limits<uint_fast64_t>::digits;
			constexpr size_t w_rest = w < w_64 ? 0 : (w - w_64);
			constexpr double log_2 = std::log(2);
			
			double result;
			double log_b;
			uint_fast64_t high_order;
			UIntType high_order_big;
			std::stringstream ss;

			// compute logarithm only from highest order that fit in 64b integer, rest is truncated as effectively zero
			high_order_big = (n >> w_rest);

			// it's sure high_order not fits to uint_64t
			// streams are slow, but most generic conversion
			ss << high_order_big;
			ss >> high_order;

			log_b = std::log(high_order);
			result = log_b + w_rest * log_2;

			return result;
		}

		template <class UIntType, class EngineType, size_t w>
		UIntType independent_bits_generator (EngineType& _32b_generator)
		{
			UIntType return_val = 0;
			for (uint_fast32_t i = 0; i < (w/32)*32; i += 32)
			{
				return_val = return_val | (static_cast<UIntType>(_32b_generator ()) << i);
			}
			// generating rest of number
			if (w-(w/32)*32 > 0)
			{
				uint_fast32_t mask = (1u << (w-(w/32)*32)) - 1;
				return_val = return_val | (static_cast<UIntType>(_32b_generator () & mask) << (w/32)*32);
			}
			return return_val;
		}
	}
}

#endif
