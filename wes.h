#ifndef WES_H
#define WES_H

#include "rsa.h"

class Wes_VDF : public RSA_VDF{
public:
    mpz_t gq;
    mpz_t l;

    Wes_VDF();

    void eval(mpz_t &x);
    bool verify(mpz_t& x);
};
#endif
