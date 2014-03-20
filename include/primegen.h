#ifndef PRIMEGEN_H
#define PRIMEGEN_H

#include <gmpxx.h>
#include <utility>

/**
 * @mainpage PrimeGen – Library for generating prime numbers
 * 
 * @author Jiri Horner
 * 
 * @version 1.0
 * @date 2014
 * @copyright MIT License
 * 
 * @details Template library providing functions for prime numbers generation.
 * 
 * @section bignums Working with big numbers
 * 
 * Instead of standard unsigned integer types, any user-defined class may be used for \c UIntType. Class must define at least <tt>= + & ++ (prefix) == < != > % >> << - *</tt> operators, with the same behavior they have with standard unsigned integer types and must be interoperable with standard unsigned integer types. All library functions have been tested with GNU MP Bignum Library's \c mpz_class. 
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

#include "../src/primegen.cpp" // providing templates implementation

#endif // PRIMEGEN_H