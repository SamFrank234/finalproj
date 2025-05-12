#ifndef VDF_H
#define VDF_H

#include <gmp.h>

class VDF {
public: 
    int lambda;
    long T;
    mpz_t y;
    virtual void computeY(mpz_t &x) = 0;
    VDF ();

    virtual void setup(int _lambda, long _T) = 0;
    virtual void eval(mpz_t &x) = 0;
    virtual bool verify(mpz_t &x) = 0;
};


#endif
