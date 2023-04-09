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

    char str[32];
    FILE *badfile;

    badfile = fopen(argv[1], "r"); 
    if (!badfile) {
       perror("Erro ao abrir o arquivo"); exit(1);
    }

    int length = fread(str, sizeof(char), 32, badfile);
    printf("Tamanho da string: %d\n", length);

    func(0xaaaaaaaa,0xbbbbbbbb,str);

    fprintf(stdout, "==== Retornou ao main corretamente! ====\n");
    return 1;
}
