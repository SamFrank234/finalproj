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
    Proof eval(mpz_t &x);
    bool verify(mpz_t &x, mpz_t &y, mpz_t &pi);
};
#endif
