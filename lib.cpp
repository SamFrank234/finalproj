#include "lib.h"

void gen_prime(mpz_t& rop, const mp_bitcnt_t& n){
    gmp_randstate_t state;
    gmp_randinit_default(state);
    mpz_urandomb(rop, state, n);
    mpz_nextprime(rop, rop);
}
void gen_input(mpz_t& dest, mpz_t& N){
        mpz_urandomm(dest, rstate, N);
}
void hash_modN(mpz_t& input, mpz_t& output, mpz_t& N){
    //convert input to byte array
    int count = (mpz_sizeinbase(input, 2) + 7) / 8;
    void* rop = malloc(count);
    mpz_export(rop, NULL, 1, count, 1, 0, 0, input);
    
    //hash the input
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(rop, count, hash);

    //convert digest back to multiple precision int
    mpz_import(output, 8, 1, 4, 0, 0, (void *) hash);
    mpz_mod(output, output, N); 

}
void hash_prime(mpz_t& input, mpz_t& rop, long bitcnt){
    mpz_t hashed;
    mpz_init(hashed);
    mpz_t N;
    mpz_init(N);
    mpz_ui_pow_ui(N, 2, bitcnt); 
    hash_modN(input, hashed, N);
    mpz_nextprime(rop, hashed);
}
void triple_cantor_modN(mpz_t& rop, mpz_t& a, mpz_t& b, long c, mpz_t& N){
    mpz_t ab;
    mpz_t_init(ab);
    mpz_t_add(ab, a, b);
    mpz_t ab1;
    mpz_t_init(ab1);
    mpz_t_add_ui(ab1, ab, 1);
    mpz_mul(ab1, ab1, ab);
    mpz_tdiv_q_ui(ab1, ab1, 2); 
    mpz_t_add(ab1, ab1, b);

    mpz_t_add(ab1, ab1, c);
    mpz_t ab2;
    mpz_init(ab2);
    mpz_add_ui(ab2, ab1, 1);
    mpz_mul(ab2, ab2, ab1);
    mpz_tdiv_q_ui(ab2, ab2, 2); 
    mpz_add_ui(ab2, ab2, c);

    mpz_mod(rop, ab2, c);
}


