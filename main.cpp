#include "lib.h"
#include "wes.h"
#include "pie.h"

int main(int argc, char *argv[]){
    Wes_VDF wes = Wes_VDF();
    int lambda = 1000;
    long T = 8;
    wes.setup(lambda, T);

    gmp_printf("Wes VDF created with RSA group mod %Zd\n", wes.N);

    mpz_t x;
    mpz_init(x);
    gen_input(x, wes.N);
    gmp_printf("Providing input %Zd to wes VDF\n", x);
    wes.eval(x);

    gmp_printf("Output of wes VDF: %Zd\n", wes.y);

    wes.verify(x);


    Pie_VDF pie = Pie_VDF();
    pie.setup(lambda, T);

    gmp_printf("Pie VDF created with RSA group mod %Zd\n", pie.N);
    
    gen_input(x, pie.N);
    gmp_printf("Providing input %Zd to pie VDF\n", x);
    pie.eval(x);

    gmp_printf("Output of pie VDF: %Zd\n", pie.y);

    pie.verify(x);
    return 0;
}
