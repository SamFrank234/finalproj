#ifndef PROOF_H
#define PROOF_H
#include <gmp.h>

typedef struct Proof {
    mpz_t xq;
    mpz_t l;
} Proof_t;

typedef struct WesProof : Proof {
    mpz_t xq;
    mpz_t l;
    
    WesProof (){

    }
} WesProof;

#endif
