#ifndef VDF_H
#define VDF_H

#include <gmp.h>
#include "proof.h"

class VDF {
public: 
    int lambda;
    long T;
    mpz_t y;
    virtual void computeY(mpz_t &x) = 0;
    VDF ();

    virtual void setup(int _lambda, long _T) = 0;
    virtual Proof eval(mpz_t &x) = 0;
    virtual bool verify(mpz_t &x, mpz_t &y, mpz_t &pi) = 0;
};


#endif
