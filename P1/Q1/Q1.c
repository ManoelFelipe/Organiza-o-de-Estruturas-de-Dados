/*
    Correção da Prova 2018/1
    Questão 1
    Seja "arq1.dat" um arquivo de Registros ordenado por chave em ordem crescente.
    Gerar um arquivo "arq2.dat" em ordem decrescente.
		Não precisa (nem pode) usar a função de ordenação.
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
  Registro re;
	long posicao, ultimo;

	entrada = fopen("arq1.dat", "r");
	saida = fopen("arq2.dat", "w");

	fread(&re, sizeof(Registro), 1, entrada);
	fseek(entrada, 0, SEEK_END);

	posicao = ftell(entrada);
	ultimo = (posicao/sizeof(Registro));

	while( ultimo >= 0	) {
		fseek(entrada, ultimo * sizeof(Registro), SEEK_SET);
		fread(&re, sizeof(Registro), 1, entrada);
		fwrite(&re, sizeof(Registro), 1, saida);
		ultimo = ultimo - 1;
	}

	fclose(entrada); fclose(saida);
	return 0;
}
