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
	int endereco; 		// endereco do comeco do bloco da memorio
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




int main(){
	MemCache cache[TCACHE];
	MemPrincipal memoria[TMEM];

	iniciaCache(cache);
	populaMem(memoria);

	return 0;
}
