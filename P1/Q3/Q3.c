/*
    Correção da Prova 2018/1
    Questão 3
    Seja "arq1.dat" um arquivo de Registros desordenado e arq2.dat um arquivo ordenado
    por chave. Gerar um arquivo "arq3.dat" com os registros que estejam ao mesmo
    tempo (mesma chave) em arq1.dat e arq2.dat. Os arquivos não tem chaves repetidas,
    por isso você não precisa se preocupar com repetições. Escreva de forma eficiente
    o seu código. Indeque a complexidade em número de acessos a registro (justifque.)
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

Registro re1;
Registro re2;

int main() {

	FILE *entrada1, *entrada2, *saida ;

    entrada1 = fopen("arq1.dat", "r");
    entrada2 = fopen("arq2.dat", "r");
    saida = fopen("arq3.dat", "w");

	int achou = 1;
	int cont2 = 0;
    long posicao1, posicao2, primeiro, ultimo, meio;

    rewind(entrada1);
    posicao1 = ftell(entrada1);

    while ( !feof(entrada1) ) {
        int cont1 = 0;
        achou = 1;

        fseek(entrada1, posicao1 * sizeof(Registro), SEEK_SET);
        fread(&re1, sizeof(Registro), 1, entrada1);


        fseek(entrada2,0,SEEK_END);
    	posicao2 = ftell(entrada2);

    	primeiro = 0;
    	ultimo = ( posicao2 / sizeof(Registro) ) - 1;
    	meio = ( primeiro + ultimo ) / 2 ;

    	rewind(entrada2);
        fseek(entrada2, meio * sizeof(Registro), SEEK_SET);
        fread(&re2, sizeof(Registro), 1, entrada2);

        while((primeiro <= ultimo) && achou == 1 ){
            cont1++;
            meio = (primeiro+ultimo)/2;

            fseek(entrada2, meio * sizeof(Registro), SEEK_SET);
            fread(&re2, sizeof(Registro), 1, entrada2);

            if (strncmp(re1.chave,re2.chave,8) == 0){
                printf("Chave1 %.8s Chave2 %.8s\n", re1.chave, re2.chave);
                printf("Contador: %.2d\n", cont1);
                cont2++;
                achou = 0;
            }

            if (achou == 1) {
                if(strncmp(re1.chave,re2.chave,8) > 0){
                    primeiro = meio + 1;
                }else {
                    ultimo = meio - 1;
                }
            }
        }
        posicao1 = posicao1 + 1;
        if(achou == 0) {
            fwrite(&re1, sizeof(Registro), 1, saida);
        }
    }
    printf("Foi encontrado: %.2d", cont2);
    printf(" Tuplas.\n");
    fclose(entrada1);fclose(entrada2); fclose(saida);
    return 0;
}
