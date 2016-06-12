#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>


#define TCACHE 16
#define TMEM 256
#define TBLOCO 5
#define TDESLOCAMENTO 3

/* Grupos 5: IVAIR PUERARI, JEFERSON AUGUSTO SCHEIN
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
	int i, j;
	for(i = 0; i < TCACHE; i ++){
		cache[i].valBit = 0;
		cache[i].info = 0;	
		for(j = 0; j < TBLOCO; j++){
			cache[i].blocoBin[j] = 0;
		}
		for(j = 0; j < TDESLOCAMENTO; j++){
			cache[i].deslocamentoBin[j] = 0;
		}
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

void mostraCache(MemCache cache[TCACHE]){
	int i, j;

	printf("*******************************************************************************************\n");
	printf("| bloco%10s| deslocamento%10s| bit de validade%10s| informacao%10s|\n", "  ","  ","  ","  ");
	printf("*******************************************************************************************\n");
	
	for( i = 0; i < TCACHE; i++){
		printf("| ");
		for(j = 0; j < TBLOCO; j++){
			printf("%d", cache[i].blocoBin[j]);
		}
		printf("%10s| ", "  ");
		
		for(j = 0; j < TDESLOCAMENTO; j++){
			printf("%d", cache[i].deslocamentoBin[j]);
		}
		printf("%19s| ", "  ");
		printf("%d", cache[i].valBit);
		printf("%24s| ", "  ");
		printf("%d \n", cache[i].info);	
		printf("-------------------------------------------------------------------------------------------\n");
	}
}

void LerMem(int endereco, MemPrincipal memoria[TMEM], MemCache cache[TCACHE]){
	leitura++;
	int d = 0, b = 0, i, p = 0, z;
	
	if(endereco >= 256 || endereco < 0){
		printf("Endereco informado nao existe!!\n Digite 0 para voltar ao menu ");
		scanf("%d", &d);
		return;
	}


	d = endereco % 8;
	b = endereco / 8;

	for(i = 0; i < TCACHE; i ++){
		if(cache[i].valBit !=0){
			if(cache[i].bloco == b && cache[i].deslocamento == d){
				acerto++;
				aLeitura++;
				printf("\n");	
				printf("%d\n\n", cache[i].info);
				mostraCache(cache);
				printf("Informacao lida com SUCESSO\n");
				printf("Digite 0 para voltar ao menu   ");
				scanf("%d", &z);
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
	binBloco(cache[p].blocoBin, b);
	printf("\n");
	printf("Informacao do endereco %d: %d\n\n", endereco, cache[p].info);
	printf("Bloco: %d \n", b);
	printf("Deslocamento:%d \n", d);
	mostraCache(cache);
	printf("Digite 0 para voltar ao menu   ");
	scanf("%d", &d);

	return;
}

void EscreverMem(int info, int endereco, MemPrincipal memoria[TMEM], MemCache cache[TCACHE]){
	escrita++;
	int d = 0, b = 0, i, p = 0, z;

	if(endereco >= 256 || endereco < 0){
		printf("Endereco informado nao existe!!\n Digite 0 para voltar ao menu ");
		scanf("%d", &z);
		return;
	}
	
	d = endereco % 8;
	b = endereco / 8;
	
	for(i = 0; i < TCACHE; i ++){
		if(cache[i].valBit !=0){
			if(cache[i].bloco == b && cache[i].deslocamento == d){
				acerto++;
				aEscrita++;
				cache[i].info = info;
				memoria[endereco].info = info;
				printf("\n");	
				printf("%d\n\n", cache[i].info);
				mostraCache(cache);
				printf("Informacao gravada com SUCESSO\n");
				printf("Digite 0 para voltar ao menu   ");
				scanf("%d", &z);
				return;
			}			
		}
	}
	falta++;
	fEscrita++;
	p = rand() % 16;
	cache[p].valBit = 1;
	cache[p].info = info;
	memoria[endereco].info = info;
	cache[p].bloco = b;
	cache[p].deslocamento = d;
	binDeslocamento(cache[p].deslocamentoBin, d);
	binBloco(cache[p].blocoBin, b);
	printf("\n");
	printf("Informacao do endereco %d: %d\n\n", endereco, cache[p].info);
	printf("Bloco: %d \n", b);
	printf("Deslocamento:%d \n", d);
	mostraCache(cache);
	printf("Digite 0 para voltar ao menu   ");
	scanf("%d", &z);
}

int main(){
	srand(time(NULL));
	
	MemCache cache[TCACHE];
	MemPrincipal memoria[TMEM];

	iniciaCache(cache);
	populaMem(memoria);

	int menu = 100, sub = 100, endereco = 0, info, l;
	
	while(menu){
		system("clear");
		printf("=========================================================================\n");
		printf("|		SIMULADOR DE MEMORIA					|\n");
		printf("|-----------------------------------------------------------------------|\n");
		printf("| 	MENU								|\n");
		printf("| 1 - Ler da Memoria							|\n");
		printf("| 2 - Escerver na Memoria						|\n");
		printf("| 3 - Estatisticas							|\n");
		printf("| 0 - Finalizar Programa						|\n");
		printf("=========================================================================\n");
		printf("Digite a Opcao desejada: ");
		scanf("%d", &menu);
		system("clear");
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
				while(sub){
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
					printf("| 10 - Todas as Estatisticas						|\n");
					printf("=========================================================================\n");
					printf("Digite a Opcao desejada: ");
					scanf("%d", &sub);
					system("clear");	
					switch(sub){
						case 1:
							printf("Numero toltal de acessos (leitura e escrita): %d\nDigite 0 para voltar para o menu\n", acesso);
							scanf("%d", &l);
							break;

						case 2:
							printf("Numero toltal de acertos (leitura e escrita): %d\nDigite 0 para voltar para o menu\n", acerto);
							scanf("%d", &l);
							break;

						case 3:
							printf("Numero toltal de faltas (leitura e escrita): %d\nDigite 0 para voltar para o menu\n", falta);
							scanf("%d", &l);
							break;

						case 4:
							printf("Numero toltal de Leituras: %d\nDigite 0 para voltar para o menu\n", leitura);
							scanf("%d", &l);
							break;

						case 5:
							printf("Numero toltal de escritas: %d\nDigite 0 para voltar para o menu\n", escrita);
							scanf("%d", &l);
							break;

						case 6:
							printf("Numero toltal de acerto de leitura: %d\nDigite 0 para voltar para o menu\n", aLeitura);
							scanf("%d", &l);
							break;

						case 7:
							printf("Numero toltal de acertos de escrita: %d\nDigite 0 para voltar para o menu\n", aEscrita);
							scanf("%d", &l);
							break;

						case 8:
							printf("Numero toltal de faltas de leitura: %d\nDigite 0 para voltar para o menu\n", fLeitura);
							scanf("%d", &l);
							break;

						case 9:
							printf("Numero toltal de faltas de escrita: %d\nDigite 0 para voltar para o menu\n", fEscrita);
							scanf("%d", &l);
							break;

						case 10:
							printf("Total de Acessos: %d\n", acesso);
							printf("Total de Acertos: %d\n", acerto);
							printf("Total de Faltas: %d\n", falta);
							printf("Total de Leituras: %d\n", leitura);
							printf("Total de Escritas: %d\n", escrita);
							printf("Total de Acertos de Leitura: %d\n", aLeitura);
							printf("Total de Acertos de Escrita: %d\n", aEscrita);
							printf("Total de Faltas de Leitura: %d\n", fLeitura);
							printf("Total de Faltas de Escrita: %d\n", fEscrita);
							scanf("%d", &l);
							break;
					
					}
				}
				sub = 100;
				break;
		}
		
	}

	printf("\n");
	return 0;
}
