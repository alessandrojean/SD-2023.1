#include<stdio.h>
#include<stdlib.h>
#include<openssl/bn.h>

#define NBITS 256

void print_bn(char* msg, BIGNUM* a);

int main(char** argv, int argc) {
  BN_CTX* ctx = BN_CTX_new();
  BIGNUM* a = BN_new();
  BIGNUM* b = BN_new();
  BIGNUM* n = BN_new();
  BIGNUM* res = BN_new();

  // Initialize a, b, n
  BN_generate_prime_ex(a, NBITS, 1, NULL, NULL, NULL);
  BN_dec2bn(&b, "273489463796838501848592769467194369268");
  BN_rand(n, NBITS, 0, 0);
  
  // res = a * b
  BN_mul(res, a, b, ctx);
  print_bn("a * b = ", res);

  // res = a ^ b mod n
  BN_mod_exp(res, a, b, n, ctx);
  print_bn("a ^ b mod n = ", res);

  return EXIT_SUCCESS;
}

void print_bn(char* msg, BIGNUM* a) {
  char* number_str = BN_bn2hex(a);
  printf("%s %s\n", msg, number_str);
  OPENSSL_free(number_str);
}


