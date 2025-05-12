#include "rsa.h"

RSA_VDF::RSA_VDF(){}

void RSA_VDF::computeY(mpz_t &x){
    //repeated squares
    mpz_t exp;
    mpz_init(exp);
    mpz_ui_pow_ui(exp, 2, T);
    mpz_init(y);
    mpz_powm(y, x, exp, N);
}

/*
 * Create RSA_VDF group G of order N,
 * where N=pq and p, q are large primes
 * (specifically, p and q are both randomly 
 * generated primes in [0, 2^(lambda) - 1] 
 * where lambda is the security paramter of the VDF)
 */
void RSA_VDF::setup(int _lambda, long _T){
    //save security params
    lambda = _lambda;
    T = _T;

    //generate primes p and q
    mpz_t p, q;
    mpz_init(p);
    mpz_init(q);

    gen_prime(p, lambda/2);
    gen_prime(q, lambda/2);

    //calculate N=pq to give us a group modulus N
    mpz_init(N);
    mpz_mul(N, p, q);
}
