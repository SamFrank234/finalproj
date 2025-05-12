#ifndef RSA_H
#define RSA_H

#include "lib.h"
#include "vdf.h"

class RSA_VDF : public VDF {
    mpz_t N; // order of group
    void computeY(mpz_t x);
public:
    void setup(int _lambda, long _T);
    vdf_result eval(mpz_t x);
    bool verify(mpz_t x, mpz_t y, mpz_t pi);
};
#endif
