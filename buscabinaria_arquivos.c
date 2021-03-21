#include <stdio.h>
#include <string.h>

typedef struct _Endereco Endereco;

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};

int main(int argc, char**argv) { 
  FILE *f;
	Endereco e;
	long tamanhoArquivo, posicao, inicio, fim, meio;
  int contador = 0;
  int achei = 0;

  if(argc != 2){
		fprintf(stderr, "USO: %s [CEP]", argv[0]);
		return 1;
	}

  f=fopen("cep_ordenado.dat","r");
  
  // definindo o inicio, meio e fim
  fseek(f,0,SEEK_END);
	tamanhoArquivo = ftell(f);
	rewind(f); // f volta ao início
	printf("Tamanho do Arquivo: %ld\n", tamanhoArquivo);
	printf("Tamanho do Registro: %ld\n", sizeof(Endereco));
	printf("Tamanho do Arquivo em Registros: %ld\n", tamanhoArquivo/sizeof(Endereco));
	inicio = 1;
	fim = (tamanhoArquivo/sizeof(Endereco));

  //busca binária
  while (inicio <= fim && achei != 1 && contador < 20) {
    
    contador++;
    meio = (inicio+fim)/2;

    fseek(f, meio * sizeof(Endereco),SEEK_SET);
    fread(&e, sizeof(Endereco), 1, f);
    printf("O CEP: %.8s \n", e.cep);

    if (strncmp(argv[1], e.cep, 8)==0) {
      achei = 1;
      printf("\n%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);;
      break;
    } else if (strncmp(argv[1], e.cep, 8)>0) {
      inicio = meio + 1;
    } else if (strncmp(argv[1], e.cep, 8)<0) {
      fim = meio - 1;
    }
  }

  printf("Número de buscas: %d", contador);

  fclose(f);

  return 0;
}
