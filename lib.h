#ifndef LIB_H
#define LIB_H

#include <gmp.h>

void gen_prime(mpz_t& rop, const mp_bitcnt_t& n);
void gen_input(mpz_t& dest, mpz_t& N);
void hash_modN(mpz_t& input, mpz_t& output, mpz_t& N);
void hash_prime(mpz_t& input, mpz_t& rop, long n);
void triple_cantor_modN(mpz_t& rop, mpz_t& a, mpz_t& b, long c, mpz_t& N);

#endif
