#include<stdio.h>
#include<stdlib.h>
#include<string.h>


/* Grupos 5: IVAIR PUERARI, JEFERSON AUGUSTO SCHEIN e GABRIEL FERNANDO CASAGRANDE
Politica de Mapeamento: Totalmente associativo
Politica de Troca: Aleatório
Politica de escrita:  Write - Through */ 


typedef struct MemCahe{
	int valBit;  		// se 0 sem informacao, 1 informacao presente
	int deslocamento;	// deslocamento dentro do bloco da memoria
	int endereco; 		// endereco do comeco do bloco da memorio
	char info[50]
}MemCahe;
 
typedef struct MemPrincipal{
	char info[50];
}MemPrincipal;


int main(){

	MemCache cache[16];
	MemPrincipal principal[256];


	return 0;
};
