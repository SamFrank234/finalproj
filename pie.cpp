#include "pie.h"
#include "lib.h"

Pie_VDF::Pie_VDF(){
}

/*
 * evaluate the VDF:
 * 1) calculate repeated squares of hashed input
 * i.e. H(x)^2^T where H: {0,1}^* -> [0, N-1]
 * 2) generate Pietrzak proof
 */
void Pie_VDF::eval(mpz_t &x){

    mpz_t g;
    mpz_init(g);
    //g = H(x): {0,1}^* -> [0, N-1]
    hash_modN(x, g, N);
    computeY(g); 

    
    long Ti = T;
    mpz_t exp, z, r, u, v;
    mpz_init(z);
    mpz_init(exp);
    mpz_init(r);
    mpz_init(u);
    mpz_set(u, g);
    mpz_init(v);
    mpz_set(v, y);
    int i=1;
    mpz_t two_lambda;
    mpz_init(two_lambda);
    mpz_ui_pow_ui(two_lambda, 2, 400);
    while(Ti>1){
        triple_cantor_modN(r, u, v, Ti, two_lambda);

        Ti /= 2;
        mpz_ui_pow_ui(exp, 2, Ti);
        mpz_powm(z, u, exp, two_lambda);
        pi.emplace_back(z); //creates mpz_class with a copy of the value from z

        cantor_modN(r, r, z, two_lambda);
        hash_modN(r, r, two_lambda);
        
        mpz_powm(u, u, r, two_lambda);
        mpz_mul(u, u, z);

        mpz_powm(z, z, r, two_lambda);
        mpz_mul(v, v, z);
        gmp_printf("Values %d: \n\t%lu \n\tz = %Zd\n\tr=%Zd\n\tu=%Zd\n\tv=%Zd\n", i, Ti, z, r, u, v);
        i++;
    }
}


bool Pie_VDF::verify(mpz_t& x){
  
    mpz_t two_lambda;
    mpz_init(two_lambda);
    mpz_ui_pow_ui(two_lambda, 2, 400);
    mpz_t g;
    mpz_init(g);
    hash_modN(x, g, two_lambda);
    
        
    long Ti = 16;
    mpz_t exp, z, r, u, v;
    mpz_init(z);
    mpz_init(exp);
    mpz_init(r);
    mpz_init(u);
    mpz_set(u, g);
    mpz_init(v);
    mpz_set(v, y);
   
    int i=1;
    while(Ti>4){
        mpz_set(z, pi[i-1].get_mpz_t());

        // r = Hash((u, T, v), z)
        triple_cantor_modN(r, u, v, Ti, two_lambda);
        Ti/=2;
        cantor_modN(r, r, z, two_lambda);
        hash_modN(r, r, two_lambda);

        // u = u^r * z
        mpz_powm(u, u, r, two_lambda);
        mpz_mul(u, u, z);

        // v = v * z^r
        mpz_powm(z, z, r, two_lambda);
        mpz_mul(v, v, z);
        gmp_printf("Values %d: \n\t%lu \n\tz = %Zd\n\tr=%Zd\n\tu=%Zd\n\tv=%Zd\n", i, Ti, z, r, u, v);
        i++; 
    }
    mpz_pow_ui(u, u, 2);
    if(mpz_cmp(u, v) != 0){
        gmp_printf("Verification failed\n");
        return false;
    }
    gmp_printf("Verification succeeded!\n");
    return true;
}



