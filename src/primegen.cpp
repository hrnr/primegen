/*
* this file implements templates and is only valid when included in primegen.h
*/
#ifdef PRIMEGEN_H

#include <gmpxx.h>
#include <utility>
#include <random>
#include "../include/known_primes.h"

namespace PrimeGen
{
	namespace Generators
	{
		template <class UIntType, size_t w, uint_fast32_t accuracy>
		UIntType random_prime (const std::string& token = "default")
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

		template <class UIntType, class EngineType, size_t w>
		UIntType independent_bits_generator (EngineType& _32b_generator)
		{
			UIntType return_val = 0;
			for (uint_fast32_t i = 0; i < (w/32)*32; i += 32)
			{
				return_val = return_val | ((UIntType)(_32b_generator ()) << i);
			}
			// generating rest of number
			if (w-(w/32)*32 > 0)
			{
				uint_fast32_t mask = (1 << (w-(w/32)*32)) - 1;
				return_val = return_val | ((UIntType)(_32b_generator () & mask) << (w/32)*32);
			}
			return return_val;
		}
	}
}

#endif