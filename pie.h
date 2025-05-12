#ifndef PIE_H
#define PIE_H

#include "rsa.h"
#include <vector>
#include <gmpxx.h>

class Pie_VDF : public RSA_VDF{
public:
    
    std::vector<mpz_class> pi;

    Pie_VDF();

    void eval(mpz_t &x);
    bool verify(mpz_t& x);
};
#endif
