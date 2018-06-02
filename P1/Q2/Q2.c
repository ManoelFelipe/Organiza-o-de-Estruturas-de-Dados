/*
    Correção da Prova 2018/1
    Questão 2
    Seja "arq1.dat" um arquivo de Registros desordenado.
    Gerar um arquivo "arq2.dat" com os registros cujo email termine com
    "gmail.com". Use uma funlção hipotétcia terminaCom(a,b) que retorna
    verdadeiro se a string a termina com a string b ou falso caso contrário.
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

Registro re;

int terminarCom(char *registro_email, char *str) {
    int cont1 = 0;

    printf("Chave %.8s Nome %.8s" "Email %.15s\n", re.chave, re.nome, re.email);

    while (registro_email[cont1] != ' ') {
        cont1++;
    }

    for (int i = 0; i < strlen(str); i++) {

        if (registro_email[ i + (cont1 - strlen(str)) ] != str[i]) {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char **argv) {
    FILE *entrada, *saida;

    long posicao, ultimo;

    entrada = fopen("arq1.dat", "r");
    saida = fopen("arq2.dat", "w");

    rewind(entrada);
    posicao = ftell(entrada);

    while ( !feof(entrada) ) {
        char str[] = "gmail.com";
        fseek(entrada, posicao * sizeof(Registro), SEEK_SET);
        fread(&re, sizeof(Registro), 1, entrada);

        if (terminarCom(re.email, str)) {
            fwrite(&re, sizeof(Registro), 1, saida);
        }
        posicao = posicao + 1;

    }

    fclose(entrada); fclose(saida);
    return 0;
}
