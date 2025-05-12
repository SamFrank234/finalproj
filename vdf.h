#ifndef VDF_H
#define VDF_H

#include <gmp.h>
#include "proof.h"
// Result of VDF eval()
// output (y) and proof (pi)
typedef struct vdf_result {
    mpz_t y;
    Proof pi;
} vdf_result;

class VDF {
    int lambda;
    long T;
    virtual void computeY(mpz_t x) = 0;
public: 
    VDF ();

    virtual void setup(int _lambda, long _T) = 0;
    virtual vdf_result eval(mpz_t x) = 0;
    virtual bool verify(mpz_t x, mpz_t y, mpz_t pi) = 0;
};


#endif
