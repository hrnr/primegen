PrimeGen – Library for generating prime numbers {#index}
===============================================

<span>Author</span> Jiri Horner

<span>Version</span> 1.0

<span>Date</span> 2014

<span>Copyright</span> MIT License

Template library providing functions for prime numbers generation.

Working with big numbers {#index_bignums}
------------------------

Instead of standard unsigned integer types, any user-defined class may
be used for <span>UIntType</span>. Class must define at least <span>= +
& ++ (prefix) == $<$ != $>$ % $>$$>$ $<$$<$ - $\ast$</span> operators,
with the same behavior they have with standard unsigned integer types
and must be interoperable with standard unsigned integer types. All
library functions have been tested with GNU MP Bignum Library’s
<span>mpz\_class</span>.

Namespace Index
===============

Namespace List
--------------

Here is a list of all documented namespaces with brief descriptions:

Namespace Documentation
=======================

Prime generators.

### Functions {#functions .unnumbered}

<span>template$<$class UIntType , size\_t w, uint\_fast32\_t accuracy$>$
</span>\
UIntType (const std::string &token=\`"default\`")

*Random prime generator. *

<span>template$<$class UIntType , size\_t w, uint\_fast32\_t accuracy$>$
</span>\
UIntType (const uint\_fast32\_t &seed)

*Pseudorandom prime generator. *

<span>template$<$class UIntType , uint\_fast32\_t accuracy$>$ </span>\
UIntType (UIntType n)

*Generates next prime greater than <span>n</span>. *

### Detailed Description

Prime generators.

### Function Documentation

[namespace~p~rime~g~en~11g~enerators~a~873d71df2a6aa5006ef2be655b0e96bd]

Generates next prime greater than <span>n</span>.

<span>Template Parameters</span> <span>*UIntType*</span> & Unsigned
integer type. Must be able to hold 2 times size of <span>result</span>.
Too bad no theory can estimate how exactly this prime will be big. From
probabilistic theory you are pretty safe if <span>UIntType</span> can
hold $ 3 \times (n + \ln(n)) $.\
 & Since probabilistic test is used for primarity testing, this
parameter determines accuracy of the test. Reasonable values are
<span>**25**</span> – 50 which gives probability of false-positive
composite lower than $ \frac{1}{4^{25}} $ while test is still reasonably
fast.\

<span>See Also</span>

<span>Parameters</span> <span>*n*</span> & Generated prime will be
greater than <span>n</span>. <span>n</span> must be greater than 3.\

<span>Returns</span> Prime greater than <span>n</span>. There should be
no other primes between <span>n</span> and generated prime (see
<span>accuracy</span>).

[namespace~p~rime~g~en~11g~enerators~a~d1e01a21e488dd5c0b668e972238ec6b]

Pseudorandom prime generator.

Pseudorandom prime will be generated using
<span>std::minstd\_rand</span>.

<span>Template Parameters</span> <span>*UIntType*</span> & Unsigned
integer type. Must be able to hold 2 times maximum of <span>w</span>.
(If <span>w</span> is 32 <span>UIntType</span> must be able to hold 64b
numbers.)\
 & Size of number to generate in bits. Generated number will be alway
greater than $ 2^{w-1} $. <span>w</span> must be greater than 2.\
 & Since probabilistic test is used for primarity testing, this
parameter determines accuracy of the test. Reasonable values are
<span>**25**</span> – 50 which gives probability of false-positive
composite lower than $ \frac{1}{4^{25}} $ while test is still reasonably
fast.\

<span>See Also</span>

<span>Parameters</span> <span>*seed*</span> & Initial seed passed to
random engine.\

<span>Returns</span> Pseudorandom prime number.

[namespace~p~rime~g~en~11g~enerators~a~8a8f4b71177d1af319d557d752a5f5f2]

Random prime generator.

Random prime will be generated using <span>std::random\_device</span>.

<span>Template Parameters</span> <span>*UIntType*</span> & Unsigned
integer type. Must be able to hold 2 times maximum of <span>w</span>.
(If <span>w</span> is 32 <span>UIntType</span> must be able to hold 64b
numbers.)\
 & Size of number to generate in bits. Generated number will be alway
greater than $ 2^{w-1} $. <span>w</span> must be greater than 2.\
 & Since probabilistic test is used for primarity testing, this
parameter determines accuracy of the test. Reasonable values are
<span>**25**</span> – 50 which gives probability of false-positive
composite lower than $ \frac{1}{4^{25}} $ while test is still reasonably
fast.\

<span>See Also</span>

<span>Parameters</span> <span>*token*</span> & Token passed to
<span>std::random\_device</span>. This parameter is
implementation-defined. Typical implementation on a Linux system, for
example, expects token to be the name of a character device that
produces random numbers when read from, with the default value
<span>\`"/dev/urandom\`"</span>. If nothing provided
<span>\`"default\`"</span> is used which should represent
system-valuable source of randomness.\

<span>Returns</span> Randomly (randomness depends on random device
represented by provided <span>token</span>) generated prime number.

Primality tests.

### Functions {#functions-1 .unnumbered}

<span>template$<$class UIntType $>$ </span>\
bool (const UIntType &n, const uint\_fast32\_t &accuracy)

*Miller-Rabin probabilistic primality test. *

<span>template$<$class UIntType $>$ </span>\
bool (const UIntType &n)

*Quick test, testing only first 100 prime factors. *

<span>template$<$class UIntType $>$ </span>\
bool (const UIntType &n)

*Quick test, testing only first 1000 prime factors. *

### Detailed Description

Primality tests.

### Function Documentation

[namespace~p~rime~g~en~11t~ests~a~ffb664bd1da7fcf28787172279145d4a]

Quick test, testing only first 1000 prime factors.

<span>Template Parameters</span> <span>*UIntType*</span> & Unsigned
integer type.\

<span>Parameters</span> <span>*n*</span> & number to be tested for
primarity\

<span>Returns</span> <span>true</span> if no prime factor was found,
<span>false</span> otherwise. This test does not guarantee number to be
prime, it should be used only together with other tests or for testing
very small numbers.

[namespace~p~rime~g~en~11t~ests~a~c7142f51753981c6ae4ca9c87413ab76]

Quick test, testing only first 100 prime factors.

<span>Template Parameters</span> <span>*UIntType*</span> & Unsigned
integer type.\

<span>Parameters</span> <span>*n*</span> & number to be tested for
primality\

<span>Returns</span> <span>true</span> if no prime factor was found,
<span>false</span> otherwise. This test does not guarantee number to be
prime, it should be used only together with other tests or for testing
very small numbers.

[namespace~p~rime~g~en~11t~ests~a~4ef151cd54b58df3b5c96195497e3ac2]

Miller-Rabin probabilistic primality test.

<span>Template Parameters</span> <span>*UIntType*</span> & Unsigned
integer type. Must be able to hold 2 times size of <span>n</span>. (Even
if <span>n</span> would fit in 32b type <span>UIntType</span> must be
able to hold 64b number.)\

<span>Parameters</span> <span>*n*</span> & Number to be tested for
primality. Must be greater than 3.\
 & Since this is only probabilistic test, test has its accuracy
determined by this parameter. Probability of false-positive match is
only $ \frac{1}{4^{accuracy}} $. Prime will be always determined as
prime. Reasonable values are 25 – 50 which gives probability of
false-positive composite lower than $ \frac{1}{4^{25}} $ while test is
still reasonably fast.\

<span>Returns</span> <span>true</span> if number is probable prime,
<span>false</span> if number is definitely composite.

Various arithmetic functions used in library algorithms.

### Functions {#functions-2 .unnumbered}

<span>template$<$class UIntType $>$ </span>\
std::pair$<$ UIntType, UIntType $>$ (const UIntType &n)

*Factorize powers of 2 from n. *

<span>template$<$class UIntType $>$ </span>\
UIntType (UIntType base, UIntType exp, const UIntType &mod)

*Exponentiation over a modulo. Exponentiation will be done by repeated
squaring. *

<span>template$<$class UIntType , class EngineType , size\_t w$>$
</span>\
UIntType (EngineType &\_32b\_generator)

*Generates random number using provided engine. Randomness of generated
number depends on randomness of provided engine. *

### Detailed Description

Various arithmetic functions used in library algorithms.

### Function Documentation

[namespace~p~rime~g~en~11u~tils~a~9d2674731aefc0e54322e023c1629a14]

Factorize powers of 2 from n.

<span>Template Parameters</span> <span>*UIntType*</span> & Unsigned
integer type.\

<span>Parameters</span> <span>*n*</span> & number to be factorized\

<span>Returns</span> std::pair (s, d) where s, d holds
$ n = 2^{s} \times d $

[namespace~p~rime~g~en~11u~tils~a~279cd6b89aca43a9597f58aa4a7b5807]

Generates random number using provided engine. Randomness of generated
number depends on randomness of provided engine.

<span>Template Parameters</span> <span>*UIntType*</span> & Unsigned
integer type. Must be able to hold <span>w</span> long numbers\
 & Function support all standard engine types defined in
<span>$<$random$>$</span>, including <span>std::random\_device</span>.
(Hence all classes generating 32b numbers with () operator should work).
Internal state of engine will be modified. Engine must be initialized
and provide () operator generating 32b numbers.\
 & size of number to generate in bits\

<span>Parameters</span> <span>*\_32b\_generator*</span> & Initialized
number generator\

<span>Returns</span> std::pair (s, d) where s, d holds
$ n = 2^{s} \times d $

[namespace~p~rime~g~en~11u~tils~a~640cffdfe9303cbe0eb0205165c3161e]

Exponentiation over a modulo. Exponentiation will be done by repeated
squaring.

<span>Template Parameters</span> <span>*UIntType*</span> & Unsigned
integer type. Must be able to hold 2 times size of <span>base</span> and
<span>mod</span>. (Even if <span>base</span> would fit in 32b type
<span>UIntType</span> must be able to hold 64b number.)\

<span>Parameters</span> <span>*base*</span> &\
 & exponent\
 & modulo\

<span>Returns</span> $ ({base}^{exponent}) \% modulo $
