/*
    dsgsgsg
*/


#include <stdio.h>
#include <string.h>

#pragma pack(1)

typedef struct _Registro Registro;

struct _Registro {
	char chave[8];
	char nome[40];
	char email[40];
	char telefone[12];
	char lixo[2];
	// 8 + 40 + 40 + 12 = 100 --> Registro ocupa 100 bytes
	// lixo[2] --> \n
};

int main(int argc, char **argv) {
  FILE *entrada, *saida;
  Registro re

}
