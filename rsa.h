#ifndef RSA_H
#define RSA_H

#include "lib.h"
#include "vdf.h"

class RSA_VDF : public VDF {
public:
    mpz_t N; // order of group

    RSA_VDF ();

    void computeY(mpz_t &x);
    void setup(int _lambda, long _T);
    virtual void eval(mpz_t &x) = 0;
    virtual bool verify(mpz_t &x) = 0;
};
#endif
