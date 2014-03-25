PrimeGen – Library for generating prime numbers
===============================================

Author
:   Jiri Horner

Version
:   1.0

Date
:   2014

Copyright
:   MIT License

Template library providing functions for prime numbers generation.

Working with big numbers
------------------------

Instead of standard unsigned integer types, any user-defined class may
be used for `UIntType`. Class must define at least
`= + & ++ (prefix) == < != > % >> << - *` operators, with the same
behavior they have with standard unsigned integer types and must be
interoperable with standard unsigned integer types. All library
functions have been tested with GNU MP Bignum Library's `mpz_class`.


* * * * *

NAME
----

PrimeGen::Generators

SYNOPSIS
--------

**Functions**

template\<class UIntType , size\_t w, uint\_fast32\_t accuracy\> UIntType **random\_prime** (const std::string &token=’default’)
*Random prime generator.*

template\<class UIntType , size\_t w, uint\_fast32\_t accuracy\> UIntType **pseudo\_random\_prime** (const uint\_fast32\_t &seed)
*Pseudorandom prime generator.*

template\<class UIntType , uint\_fast32\_t accuracy\> UIntType **next\_prime** (UIntType n)
*Generates next prime greater than* `n`*.*

Detailed Description
--------------------

Prime generators.

Function Documentation
----------------------

**template\<class UIntType , uint\_fast32\_t accuracy\> UIntType PrimeGen::Generators::next\_prime (UIntType n)**
 Generates next prime greater than `n`.

**Template Parameters:**

*UIntType* Unsigned integer type. Must be able to hold 2 times size of `result`. Too bad no theory can estimate how exactly this prime will be big. From probabilistic theory you are pretty safe if `UIntType` can hold \$ 3 imes (n + ) \$.

*accuracy* Since probabilistic test is used for primarity testing, this parameter determines accuracy of the test. Reasonable values are **25** â 50 which gives probability of false-positive composite lower than \$ ac{1}{4\^{25}} \$ while test is still reasonably fast.

**See Also:**

**Tests::miller\_rabin**

**Parameters:**

*n* Generated prime will be greater than `n`. `n` must be greater than 3.

**Returns:**

Prime greater than `n`. There should be no other primes between `n` and generated prime (see `accuracy`).

**template\<class UIntType , size\_t w, uint\_fast32\_t accuracy\> UIntType PrimeGen::Generators::pseudo\_random\_prime (const uint\_fast32\_t &seed)**
 Pseudorandom prime generator. Pseudorandom prime will be generated using `std::minstd_rand`.

**Template Parameters:**

*UIntType* Unsigned integer type. Must be able to hold 2 times maximum of `w`. (If `w` is 32 `UIntType` must be able to hold 64b numbers.)

*w* Size of number to generate in bits. Generated number will be alway greater than \$ 2\^{w-1} \$. `w` must be greater than 2.

*accuracy* Since probabilistic test is used for primarity testing, this parameter determines accuracy of the test. Reasonable values are **25** - 50 which gives probability of false-positive composite lower than \$ ac{1}{4\^{25}} \$ while test is still reasonably fast.

**See Also:**

**Tests::miller\_rabin**

**Parameters:**

*seed* Initial seed passed to random engine.

**Returns:**

Pseudorandom prime number.

**template\<class UIntType , size\_t w, uint\_fast32\_t accuracy\> UIntType PrimeGen::Generators::random\_prime (const std::string &token =** `’default’`**)**
 Random prime generator. Random prime will be generated using `std::random_device`.

**Template Parameters:**

*UIntType* Unsigned integer type. Must be able to hold 2 times maximum of `w`. (If `w` is 32 `UIntType` must be able to hold 64b numbers.)

*w* Size of number to generate in bits. Generated number will be alway greater than \$ 2\^{w-1} \$. `w` must be greater than 2.

*accuracy* Since probabilistic test is used for primarity testing, this parameter determines accuracy of the test. Reasonable values are **25** â 50 which gives probability of false-positive composite lower than \$ ac{1}{4\^{25}} \$ while test is still reasonably fast.

**See Also:**

**Tests::miller\_rabin**

**Parameters:**

*token* Token passed to `std::random_device`. This parameter is implementation-defined. Typical implementation on a Linux system, for example, expects token to be the name of a character device that produces random numbers when read from, with the default value `’/dev/urandom’`. If nothing provided `’default’` is used which should represent system-valuable source of randomness.

**Returns:**

Randomly (randomness depends on random device represented by provided `token`) generated prime number.

NAME
----

PrimeGen::Tests

SYNOPSIS
--------

**Functions**

template\<class UIntType \> bool **miller\_rabin** (const UIntType &n, const uint\_fast32\_t &accuracy)
*Miller-Rabin probabilistic primality test.*

template\<class UIntType \> bool **f100\_prime\_factors** (const UIntType &n)
*Quick test, testing only first 100 prime factors.*

template\<class UIntType \> bool **f1000\_prime\_factors** (const UIntType &n)
*Quick test, testing only first 1000 prime factors.*

Detailed Description
--------------------

Primality tests.

Function Documentation
----------------------

**template\<class UIntType \> bool PrimeGen::Tests::f1000\_prime\_factors (const UIntType &n)**
 Quick test, testing only first 1000 prime factors.

**Template Parameters:**

*UIntType* Unsigned integer type.

**Parameters:**

*n* number to be tested for primarity

**Returns:**

`true` if no prime factor was found, `false` otherwise. This test does not guarantee number to be prime, it should be used only together with other tests or for testing very small numbers.

**template\<class UIntType \> bool PrimeGen::Tests::f100\_prime\_factors (const UIntType &n)**
 Quick test, testing only first 100 prime factors.

**Template Parameters:**

*UIntType* Unsigned integer type.

**Parameters:**

*n* number to be tested for primality

**Returns:**

`true` if no prime factor was found, `false` otherwise. This test does not guarantee number to be prime, it should be used only together with other tests or for testing very small numbers.

**template\<class UIntType \> bool PrimeGen::Tests::miller\_rabin (const UIntType &n, const uint\_fast32\_t &accuracy)**
 Miller-Rabin probabilistic primality test.

**Template Parameters:**

*UIntType* Unsigned integer type. Must be able to hold 2 times size of `n`. (Even if `n` would fit in 32b type `UIntType` must be able to hold 64b number.)

**Parameters:**

*n* Number to be tested for primality. Must be greater than 3.

*accuracy* Since this is only probabilistic test, test has its accuracy determined by this parameter. Probability of false-positive match is only \$ ac{1}{4\^{accuracy}} \$. Prime will be always determined as prime. Reasonable values are 25 â 50 which gives probability of false-positive composite lower than \$ ac{1}{4\^{25}} \$ while test is still reasonably fast.

**Returns:**

`true` if number is probable prime, `false` if number is definitely composite.

NAME
----

PrimeGen::Utils

SYNOPSIS
--------

**Functions**

template\<class UIntType \> std::pair\< UIntType, UIntType \> **fac\_2\_powers** (const UIntType &n)

*Factorize powers of 2 from n.*
 template\<class UIntType \> UIntType **pow\_mod** (UIntType base, UIntType exp, const UIntType &mod)

*Exponentiation over a modulo. Exponentiation will be done by repeated squaring.*
 template\<class UIntType , class EngineType , size\_t w\> UIntType **independent\_bits\_generator** (EngineType &\_32b\_generator)

*Generates random number using provided engine. Randomness of generated number depends on randomness of provided engine.*

Detailed Description
--------------------

Various arithmetic functions used in library algorithms.

Function Documentation
----------------------

**template\<class UIntType \> std::pair\<UIntType, UIntType\> PrimeGen::Utils::fac\_2\_powers (const UIntType &n)**
 Factorize powers of 2 from n.

**Template Parameters:**

*UIntType* Unsigned integer type.

**Parameters:**

*n* number to be factorized

**Returns:**

std::pair (s, d) where s, d holds \$ n = 2\^{s} imes d \$

**template\<class UIntType , class EngineType , size\_t w\> UIntType PrimeGen::Utils::independent\_bits\_generator (EngineType &\_32b\_generator)**
 Generates random number using provided engine. Randomness of generated number depends on randomness of provided engine.

**Template Parameters:**

*UIntType* Unsigned integer type. Must be able to hold `w` long numbers

*EngineType* Function support all standard engine types defined in `<random>`, including `std::random_device`. (Hence all classes generating 32b numbers with () operator should work). Internal state of engine will be modified. Engine must be initialized and provide () operator generating 32b numbers.

*w* size of number to generate in bits

**Parameters:**

*\_32b\_generator* Initialized number generator

**Returns:**

std::pair (s, d) where s, d holds \$ n = 2\^{s} imes d \$

**template\<class UIntType \> UIntType PrimeGen::Utils::pow\_mod (UIntTypebase, UIntTypeexp, const UIntType &mod)**
 Exponentiation over a modulo. Exponentiation will be done by repeated squaring.

**Template Parameters:**

*UIntType* Unsigned integer type. Must be able to hold 2 times size of `base` and `mod`. (Even if `base` would fit in 32b type `UIntType` must be able to hold 64b number.)

**Parameters:**

*base*

*exp* exponent

*mod* modulo

**Returns:**

$ ({base}\^{exponent}) modulo $
