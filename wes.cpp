#include "wes.h"
#include "lib.h"

Wes_VDF::Wes_VDF(){
}

/*
 * evaluate the VDF:
 * 1) calculate repeated squares of hashed input
 * i.e. H(x)^2^T where H: {0,1}^* -> [0, N-1]
 * 2) generate Wesolowski proof
 */
void Wes_VDF::eval(mpz_t &x){

    mpz_t g;
    mpz_init(g);
    //g = H(x): {0,1}^* -> [0, N-1]
    hash_modN(x, g, N);
    computeY(g); 

    mpz_t gyT;
    mpz_init(gyT);
    triple_cantor_modN(gyT, g, y, T, N);

    // l = H(x+y+T) in Primes(lambda)
    mpz_init(l);
    hash_prime(gyT, l, lambda);

    mpz_t exp;
    mpz_init(exp);
    mpz_ui_pow_ui(exp, 2, T);

    mpz_t q;
    mpz_init(q);
    mpz_tdiv_q(q, exp, l);
    
    mpz_init(gq);
    mpz_powm(gq, g, q, N);
    gmp_printf("VDF Wesolowski proof:\n\tg^q=%Zd\n\tl=%Zd\n", gq, l);
}

bool Wes_VDF::verify(mpz_t& x){
    
    mpz_t g;
    mpz_init(g);
    hash_modN(x, g, N);
    
    mpz_t r;
    mpz_init(r);
    mpz_ui_pow_ui(r, 2, T);
    mpz_mod(r, r, l);
    
    mpz_t gyT;
    mpz_init(gyT);
    triple_cantor_modN(gyT, g, y, T, N);
    
    mpz_t _l;
    mpz_init(_l);
    hash_prime(gyT, _l, lambda);
    if(mpz_cmp(l, _l) !=0){
        gmp_printf("Verification failed step 0: check H(g,y,T)=l\n");
        return false;
    }
    gmp_printf("Verification step 0 done: H(g,y,T)=l\n");
    
    mpz_t _y, gr;
    mpz_init(_y);
    mpz_init(gr);
    mpz_powm(_y, gq, l, N);
    mpz_powm(gr, g, r, N);
    mpz_mul(_y, _y, gr);
    if(mpz_cmp(y, _y) !=0){
        gmp_printf("Verification failed step 1: check pi^l * g^r = y\n\t%Zd != %Zd", _y, y);
        return false;
    }
    gmp_printf("Verification step 1 done: pi^l * g^r = y\n");

    gmp_printf("Verification succeeded!\n");
    return true;
}



