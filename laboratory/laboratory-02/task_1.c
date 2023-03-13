#include<stdio.h>
#include<stdlib.h>
#include<openssl/bn.h>

#define NBITS 256

void print_bn(char* msg, BIGNUM* a);
void calculate_z(BIGNUM* z, BIGNUM* p, BIGNUM* q, BN_CTX* ctx);

int main(char** argv, int argc) {
  BN_CTX* ctx = BN_CTX_new();
  BIGNUM* p = BN_new();
  BIGNUM* q = BN_new();
  BIGNUM* e = BN_new();
  BIGNUM* n = BN_new();
  BIGNUM* d = BN_new();
  BIGNUM* z = BN_new();
  BIGNUM* e_d = BN_new();

  // Initialize p, q, e
  BN_hex2bn(&p, "F7E75FDC469067FFDC4E847C51F452DF");
  BN_hex2bn(&q, "E85CED54AF57E53E092113E62F436F4F");
  BN_hex2bn(&e, "0D88C3");
  
  // n = p * q
  BN_mul(n, p, q, ctx);
  calculate_z(z, p, q, ctx);
  BN_mod_inverse(d, e, z, ctx);
  BN_mod_mul(e_d, e, d, z, ctx);

  print_bn("n = ", n);
  print_bn("z = ", z);
  print_bn("d = ", d);
  print_bn("e * d (mod n) = ", e_d);

  return EXIT_SUCCESS;
}

void print_bn(char* msg, BIGNUM* a) {
  char* number_str = BN_bn2hex(a);
  printf("%s %s\n", msg, number_str);
  OPENSSL_free(number_str);
}

// z = (p - 1) * (q - 1)
// z = pq - p - q - 1
void calculate_z(BIGNUM* z, BIGNUM* p, BIGNUM* q, BN_CTX* ctx) {
  // BIGNUM* res_1 = BN_new();
  // BIGNUM* res_2 = BN_new();
  // BIGNUM* res_3 = BN_new();
  // BIGNUM* num_1 = BN_new();

  // BN_dec2bn(&num_1, "1");

  // BN_mul(res_1, p, q, ctx);
  // BN_sub(res_2, res_1, p);
  // BN_sub(res_3, res_2, q);
  // BN_sub(z, res_3, num_1);

  BIGNUM* res_1 = BN_new();
  BIGNUM* res_2 = BN_new();
  BIGNUM* res_3 = BN_new();
  BIGNUM* num_1 = BN_new();

  BN_dec2bn(&num_1, "1");

  BN_sub(res_1, p, num_1);
  BN_sub(res_2, q, num_1);
  BN_mul(z, res_1, res_2, ctx);
}