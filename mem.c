#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>


#define TCACHE 16
#define TMEM 256

/* Grupos 5: IVAIR PUERARI, JEFERSON AUGUSTO SCHEIN e GABRIEL FERNANDO CASAGRANDE
Politica de Mapeamento: Totalmente associativo
Politica de Troca: Aleatório
Politica de escrita:  Write - Through */ 


typedef struct MemCache{
	int valBit;  		// se 0 sem informacao, 1 informacao presente
	int deslocamento;	// deslocamento dentro do bloco da memoria
	int deslocamentoBin[3];	// deslocamento em binario
	int endereco; 		// endereco do comeco do bloco da memorio
	int enderecoBin[5];	// endereco em binario 	
	int info;
	
}MemCache;
 
typedef struct MemPrincipal{
	int info;
}MemPrincipal;

void iniciaCache(MemCache cache[TCACHE]){
	int i;
	for(i = 0; i < TCACHE; i ++){
		cache[i].valBit = 0;
	}
}

void populaMem(MemPrincipal memoria[TMEM]){
	srand(time(NULL));
	int i;

	for(i = 0; i < TMEM; i++){
		memoria[i].info = rand() % 100000;
	}
}

void LerMem(int endereco, MemPrincipal memoria[TMEM], MemCache cache[TCACHE]){
	int d = 0, b = 0;

	return;
}

void EscreverMem(int info, int endereco, MemPrincipal memoria[TMEM], MemCache cache[TCACHE]){

}

int main(){
	MemCache cache[TCACHE];
	MemPrincipal memoria[TMEM];

	iniciaCache(cache);
	populaMem(memoria);

	int menu = 100, sub = 100, endereco = 0, info;

	while(menu){
		system("clear");
		printf("=========================================================================\n");
		printf("|		SIMULADOR DE MEMORIA					|\n");
		printf("|-----------------------------------------------------------------------|\n");
		printf("| 	MENU								|\n");
		printf("| 1 - Ler da Memoria							|\n");
		printf("| 2 - Escerver na Memoria						|\n");
		printf("| 3 - Estatisticas							|\n");
		printf("=========================================================================\n");
		printf("Digite a Opcao desejada: ");
		scanf("%d", &menu);

		switch(menu){
			case 1: 
				printf("OBS: O endereco da memoria que sera lido\n Endereco deve ser em decimal!\n Endereco: ");
				scanf("%d", &endereco);
				LerMem(endereco, memoria, cache);
				break;
			case 2:
				printf("Digite a informação a ser escrita na Memoria: ");
				scanf("%d", &info);
				printf("OBS: O endereco da memoria onde sera escrita a informação\n Endereco deve ser em decimal!\n Endereco: ");
				scanf("%d", &endereco);
				EscreverMem(info, endereco, memoria, cache);
				break;
			case 3: 
				system("clear");
				printf("=========================================================================\n");
				printf("|	SIMULADOR DE MEMORIA - ESTATISTICAS				|\n");
				printf("|-----------------------------------------------------------------------|\n");
				printf("|	MENU								|\n");
				printf("| 0 - Retornar ao menu anterior						|\n");
				printf("| 1 - Numero de Acessos							|\n");
				printf("| 2 - Numero de Acertos							|\n");
				printf("| 3 - Numero de Faltas							|\n");
				printf("| 4 - Numero de Leituras						|\n");
				printf("| 5 - Numero de Escritas						|\n");
				printf("| 6 - Numero de Acertos na Leitura					|\n");
				printf("| 7 - Numero de Acertos na Escrita					|\n");
				printf("| 8 - Numero de Faltas na Leitura					|\n");
				printf("| 9 - Numero de Faltas na Escrita					|\n");
				printf("=========================================================================\n");
				printf("Digite a Opcao desejada: ");
				scanf("%d", &sub);
				break;
		}
		
	}

	printf("\n");
	return 0;
}
