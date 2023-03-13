#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<openssl/bn.h>

#define NBITS 256

void print_bn(char* msg, BIGNUM* a);
bool is_valid_signature(BIGNUM* hash, BIGNUM* expected_hash);

int main(char** argv, int argc) {
  BN_CTX* ctx = BN_CTX_new();
  BIGNUM* e = BN_new();
  BIGNUM* n = BN_new();
  BIGNUM* hash = BN_new();
  BIGNUM* signature = BN_new();
  BIGNUM* expected_hash = BN_new();

  // Initialize n, d, e

  // $ openssl x509 -in c2.pem -noout -modulus
  BN_hex2bn(&n, "A5F2D1A55214C1B80178122F9A039D43EA96CEF33DAD45BA29382AA4DF4936B3D50EEE70E2E5FBE9A0CBE6B442C34282E9D8DDF5D3C1698A3190018F8F8AE4E0B3C8D22E68065D1BB54DE3E7AE216AC74BA303C9CA51DF547FA33ED195ED1BC6FEE6BC45015E83FF50889C62E3378DEAC854283A32C7EF03D65FF7AC16F80CB9C049A61B086634B49350BC0A14B633AF13688AB01F81216A3AF792138B63AE916E22E6588FF139F3BB694F5E2C3E494AF22B9099B7DEDF625DB19F6450A8003A34E76851F74B5C5A28062C1C794E0257289DDD930E779301D53507A7EF7CA1DCF2559C18BD65BB36A05F2F28B683138CB2C020CBAC31E18B29C84FC14BC7CAB7");

  // $ openssl x509 -in c2.pem -text -noout
  BN_dec2bn(&e, "65537");

  // $ cat assinatura.txt | tr -d '[:space:]:'
  BN_hex2bn(&signature, "0fba80fc3010b2d01443c1fe17a08545801e548e9f6a1e20d2e3cffff437aa00f04c05af4f486d32e76ff1a7aea37653f7765e6cc88a7c55a7e78cf0661226478c78309f0e64d16fa7f1d816fb759f7a20a33433bdec77c665f0d997916185c030a0f0f7320b52ac9b99bebd1f3c906b25874cbdc63b4adbaa17b23986719c92eb095cd4d645b2a8ae4935eadd3502965809508e674057c85537d002a7566fee3866313712a586aec493349c55346d33b89ae39370e40ebbc5a993fa3d0afbbb16f5c87db015a6720f70057d128686b053fe384cc658df56cbf0b0ba13356c2e7c2f1f17293c6643bdafedae2a5cd9e95622df231d728fd04d9bbca6ca43d963");

  // $ sha256sum c0_body.bin
  BN_hex2bn(&expected_hash, "0645266e89d2f16c0828603f85cb3f4392c45bbac570991fc126f4eba102378a");

  // Hash: msg = msg_c ^ e mod n
  BN_mod_exp(hash, signature, e, n, ctx);

  print_bn("n = ", n);
  print_bn("e = ", e);
  print_bn("signature = ", signature);
  print_bn("hash = ", hash);
  print_bn("expected_hash = ", expected_hash);

  if (is_valid_signature(hash, expected_hash)) {
    printf("\nThe signatures match.\n");
  }

  return EXIT_SUCCESS;
}

void print_bn(char* msg, BIGNUM* a) {
  char* number_str = BN_bn2hex(a);
  printf("%s %s\n", msg, number_str);
  OPENSSL_free(number_str);
}

bool is_valid_signature(BIGNUM* hash, BIGNUM* expected_hash) {
  char* hash_str = BN_bn2hex(hash);
  char* expected_hash_str = BN_bn2hex(expected_hash);

  bool is_valid = strstr(hash_str, expected_hash_str) != NULL;

  OPENSSL_free(hash_str);
  OPENSSL_free(expected_hash_str);

  return is_valid;
}
