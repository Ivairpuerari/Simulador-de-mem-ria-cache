#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>


#define TCACHE 16
#define TMEM 256
#define TBLOCO 5
#define TDESLOCAMENTO 3

/* Grupos 5: IVAIR PUERARI, JEFERSON AUGUSTO SCHEIN e GABRIEL FERNANDO CASAGRANDE
Politica de Mapeamento: Totalmente associativo
Politica de Troca: Aleatório
Politica de escrita:  Write - Through */ 

typedef struct MemCache{
	int valBit;  		// se 0 sem informacao, 1 informacao presente
	int deslocamento;	// deslocamento dentro do bloco da memoria
	int deslocamentoBin[3];	// deslocamento em binario
	int bloco; 		// endereco do comeco do bloco da memorio
	int blocoBin[5];	// endereco em binario 	
	int info;
	
}MemCache;
 
typedef struct MemPrincipal{
	int info;
}MemPrincipal;

int acesso = 0, acerto = 0, falta = 0;
int leitura = 0, escrita = 0;
int aLeitura = 0, fLeitura = 0;
int aEscrita = 0,fEscrita = 0;

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

void binBloco( int d[TBLOCO], int x ){
	int i;
	int r[TBLOCO];

	for(i = 0; i < TBLOCO; i ++){
		r[i] = 0;
	}	

	for(i = 0; x != 0 && i < TBLOCO; i++){
		if(x == 0){				
			r[i] = 1;
		}else if((x % 2) == 0){
			r[i] = 0;		
		}else if((x % 2) == 1){
			r[i] = 1;		
		}
		x = x / 2;
	}
	x = 4;
	for(i = 0; i < TBLOCO; i ++){
		d[i] = r[x--];
	}
}

void binDeslocamento( int d[TBLOCO], int x ){
	int i;
	int r[TDESLOCAMENTO];

	for(i = 0; i < TDESLOCAMENTO; i ++){
		r[i] = 0;
	}	

	for(i = 0; x != 0 && i < TDESLOCAMENTO; i++){
		if(x == 0){				
			r[i] = 1;
		}else if((x % 2) == 0){
			r[i] = 0;		
		}else if((x % 2) == 1){
			r[i] = 1;		
		}
		x = x / 2;
	}
	x = 2;
	for(i = 0; i < TDESLOCAMENTO; i ++){
		d[i] = r[x--];
	}	

}

void LerMem(int endereco, MemPrincipal memoria[TMEM], MemCache cache[TCACHE]){
	leitura++;
	int d = 0, b = 0, i, p = 0;

	d = endereco % 8;
	b = endereco / 8;

/*
	printf("Bloco: %d\n", b);
	binBloco(cache[0].enderecoBin, b);

	for(i = 0; i < TBLOCO; i ++){
		printf("%d", cache[0].enderecoBin[i]);
	}
	printf("\n");
	printf("Deslocamento: %d\n", d);
	binDeslocamento(cache[0].deslocamentoBin, d);
	
	for(i = 0; i < TDESLOCAMENTO; i ++){
		printf("%d", cache[0].deslocamentoBin[i]);
	}
*/

	for(i = 0; i < TCACHE; i ++){
		if(cache[i].valBit !=0){
			if(cache[i].bloco == b && cache[i].deslocamento == d){
				acerto++;
				aLeitura++;
				printf("\n");	
				printf("%d\n\n", cache[i].info);
				return;
			}			
		}
	}
	falta++;
	fLeitura++;
	p = rand() % 16;
	cache[p].valBit = 1;
	cache[p].info = memoria[endereco].info;
	cache[p].bloco = b;
	cache[p].deslocamento = d;
	binDeslocamento(cache[p].deslocamentoBin, d);
	binBloco(cache[0].blocoBin, b);

	scanf("%d", &d);

	return;
}

void EscreverMem(int info, int endereco, MemPrincipal memoria[TMEM], MemCache cache[TCACHE]){

}

int main(){
	srand(time(NULL));
	
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
				acesso++;
				break;
			case 2:
				printf("Digite a informação a ser escrita na Memoria: ");
				scanf("%d", &info);
				printf("OBS: O endereco da memoria onde sera escrita a informação\n Endereco deve ser em decimal!\n Endereco: ");
				scanf("%d", &endereco);
				acesso++;
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
