#include "rsa.h"
#include "lib.h"

int main(int argc, char *argv[]){
    RSA_VDF vdf = RSA_VDF();
    int lambda = 1000;
    long T = 35;
    vdf.setup(lambda, T);
   
    gmp_printf("Wes VDF created with RSA group mod %Zd\n", vdf.N);

    mpz_t x;
    mpz_init(x);
    gen_input(x, vdf.N);
    gmp_printf("Providing input %Zd to VDF\n", x);
    Proof pi = vdf.eval(x);

    gmp_printf("Output of VDF: %Zd\n", vdf.y);
//    gmp_printf("VDF Wesolowski proof:\n\tx^q=%Zd\n\tl=%Zd\n", pi.xq, pi.l);

    return 0;
}
