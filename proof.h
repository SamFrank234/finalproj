#ifndef PROOF_H
#define PROOF_H
#include <gmp.h>

class Proof{
    public:
            Proof(){}

};

class WesProof : public Proof {
    mpz_t xq;
    mpz_t l;

public:
    WesProof(mpz_t& _xq, mpz_t& _l)
    : xq(_xq), l(+l)
    {
    }
}

#endif
