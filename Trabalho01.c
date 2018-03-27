#include <stdio.h>
#include <string.h>

typedef struct _Endereco Endereco;

struct _Endereco {
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};

int main(int argc, char **argv) {
	FILE *f;
	Endereco e;
	int cont = 1;
    long posicao, primeiro, ultimo, meio;

	if(argc != 2) {
        fprintf(stderr,"Erro na chamada do programa.\n");
		fprintf(stderr, "Aceito Somente 1 argumento: [CEP] \n");
		return 1;
	}
	f = fopen("cep_ordenado.dat","r");
    if(!f) {
		fprintf(stderr,"Arquivo não pode ser aberto para leitura\n");
		return 1;
	}

	fseek(f,0,SEEK_END);
	posicao = ftell(f);

	primeiro = 0;
	ultimo = (posicao/sizeof(Endereco))-1;
	meio = (primeiro+ultimo)/2;

	rewind(f);

    fseek(f, meio * sizeof(Endereco), SEEK_SET);
    fread(&e, sizeof(Endereco), 1, f);

    if(strncmp(argv[1],e.cep,8) == 0){
        cont = 1;
        ultimo = primeiro - 1;
    }

    while(primeiro <= ultimo ){
        cont++;
        meio = (primeiro+ultimo)/2;

        fseek(f, meio * sizeof(Endereco), SEEK_SET);
        fread(&e, sizeof(Endereco), 1, f);

        if (strncmp(argv[1],e.cep,8) == 0){
            break;
        }

        if(strncmp(argv[1],e.cep,8) > 0){
            primeiro = meio + 1;
        }else{
            ultimo = meio - 1;
        }

    }
    if(strncmp(argv[1],e.cep,8) == 0){
        printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);
    }
	printf("Contador: %d \n", cont);
	fclose(f);
	return 0;
}
