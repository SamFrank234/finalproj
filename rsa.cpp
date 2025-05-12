#include "rsa.h"
#include "lib.h"

RSA_VDF::RSA_VDF(){}

void RSA_VDF::computeY(mpz_t &x){
    
    //H(x): {0,1}^* -> [0, N-1]
    mpz_t hx;
    mpz_init(hx);
    hash_modN(x, hx, N);

    //repeated squares
    mpz_t exp;
    mpz_init(exp);
    mpz_ui_pow_ui(exp, 2, T);
    mpz_init(y);
    mpz_powm(y, hx, exp, N);
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


/*
 * evaluate the VDF:
 * 1) calculate repeated squares of hashed input
 * i.e. H(x)^2^T where H: {0,1}^* -> [0, N-1]
 * 2) generate Wesolowski proof
 */
Proof RSA_VDF::eval(mpz_t &x){
   
    computeY(x); 

    mpz_t xyT;
    mpz_init(xyT);
    triple_cantor_modN(xyT, x, y, T, N);

    // l = H(x+y+T) in Primes(lambda)
    mpz_t l;
    mpz_init(l);
    hash_prime(xyT, l, lambda);

    mpz_t exp;
    mpz_init(exp);
    mpz_ui_pow_ui(exp, 2, T);

    mpz_t q;
    mpz_init(q);
    mpz_tdiv_q(q, exp, l);
    
    WesProof pi;
    mpz_init(pi.xq);
    mpz_powm(pi.xq, x, q, N);
    mpz_add_ui(pi.l, l, 0);
    gmp_printf("VDF Wesolowski proof:\n\tx^q=%Zd\n\tl=%Zd\n", pi.xq, pi.l);
    return pi;
}

bool RSA_VDF::verify(mpz_t& x, mpz_t& y, mpz_t& pi){
    
    return false;
}



