#include<stdio.h>
#include<stdlib.h>
#include<openssl/bn.h>

#define NBITS 256

void print_bn(char* msg, BIGNUM* a);

int main(char** argv, int argc) {
  BN_CTX* ctx = BN_CTX_new();
  BIGNUM* e = BN_new();
  BIGNUM* n = BN_new();
  BIGNUM* d = BN_new();
  BIGNUM* msg = BN_new();
  BIGNUM* msg_c = BN_new();

  // Initialize n, d, e
  BN_hex2bn(&n, "DCBFFE3E51F62E09CE7032E2677A78946A849DC4CDDE3A4D0CB81629242FB1A5");
  BN_hex2bn(&d, "74D806F9F3A62BAE331FFE3F0A68AFE35B3D2E4794148AACBC26AA381CD7D30D");
  BN_dec2bn(&e, "65537");
  BN_hex2bn(&msg, "4375696461646F3A2070726F6772616D6120696E73656775726F21");

  // msg_c = msg ^ e mod n
  BN_mod_exp(msg_c, msg, e, n, ctx);

  print_bn("n = ", n);
  print_bn("d = ", d);
  print_bn("e = ", e);
  print_bn("msg = ", msg);
  print_bn("msg_c = ", msg_c);

  return EXIT_SUCCESS;
}

void print_bn(char* msg, BIGNUM* a) {
  char* number_str = BN_bn2hex(a);
  printf("%s %s\n", msg, number_str);
  OPENSSL_free(number_str);
}
