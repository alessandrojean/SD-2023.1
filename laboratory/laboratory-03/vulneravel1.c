#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* func contem vulnerabilidade para buffer overflow */
void func(int a, int b, char *str) {
  int c = 0xdeadbeef;
  char buf[4];
  strcpy(buf,str);
}

void outraFuncao() {
  printf("Entrou em OutraFuncao!!\n");
  exit(0);
}

/* executa um shell (linha de comando) */
void bar() {
  printf("Iniciando um shell! Assuma o controle!\n");
  system("/bin/sh");
}

int main(int argc, char**argv) {
  func(0xaaaaaaaa,0xbbbbbbbb,argv[1]);
  fprintf(stdout, "==== Retornou ao main corretamente! ====\n");
  return 0;
}
