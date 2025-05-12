#ifndef LIB_H
#define LIB_H

#include <gmp.h>

void gen_prime(mpz_t& rop, const mp_bitcnt_t& n);
void gen_input(mpz_t& dest, mpz_t& N);
void hash(void *input, unsigned char hash[SHA256_DIGEST_LENGTH]);
void hash_prime(mpz_t& input, mpz_t& rop, const mp_bitcnt_t& n);
void cantor_modN(mpz_t& rop, mpz_t& a, mpz_t& b, mpz_t& N);

#endif
