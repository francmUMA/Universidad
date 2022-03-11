/*
 ============================================================================
 Name        : Practica2B.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : 
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include "arbolbb.h"

/**
 * Recibe un número "tam" del usuario, y
 * crea un fichero binario para escritura con el nombre "nfichero"
 * en que escribe "tam" numeros (unsigned int) aleatorios
 * Se utiliza srand(time(NULL)) para establecer la semilla (de la libreria time.h)
 * y rand()%100 para crear un n�mero aleatorio entre 0 y 99.
 */
void creafichero_tam_random(char* nfichero, unsigned tam){
	FILE *f = fopen(nfichero, "wb");
	if (f == NULL){
		perror("No se ha podido abrir el fichero \n");
	} else {
		srand(time(NULL));
		unsigned int array_rand[tam];
		for(int i = 0; i < tam; i++){
			unsigned int num = rand()%tam;
			array_rand[i];
		}
		fwrite(array_rand,sizeof(unsigned),tam,f);
		fclose(f);
	}
}
/**
 * Muestra por pantalla la lista de números (unsigned int) almacenada
 * en el fichero binario "nfichero"
 */
void muestrafichero(char* nfichero){
	FILE *f = fopen(nfichero, "rb");
	if(f == NULL){
		perror("No se ha podido abrir el fichero");
	} else {
		unsigned int basura;
		while (!feof(f)){
			fread(&basura, sizeof(unsigned), 1, f);
			printf("%u \n", basura);
		}
		fclose(f);
	}
}

/**
 * Guarda en el arbol "*miarbol" los números almacenados en el fichero binario "nfichero"
 */

void cargaFichero(char* nfichero, T_Arbol* miarbol){
	
}

int main(void) {
	char nfichero[50];
	unsigned num_random;

	printf ("Introduce el nombre del fichero binario:\n");
	scanf ("%s",nfichero);

	printf ("Introduce el número de elementos a crear:\n");
	scanf ("%i",&num_random);

	creafichero_tam_random(nfichero, num_random);

	printf("\nAhora lo leemos y mostramos\n");
	muestrafichero(nfichero);

	printf ("\nAhora lo cargamos en el arbol\n");
	T_Arbol miarbol;
	Crear (&miarbol);
	cargaFichero(nfichero,&miarbol);

	printf ("\nY lo mostramos ordenado\n");
	Mostrar(miarbol);
	

	printf("\nAhora lo guardamos ordenado\n");
	FILE * fich;
	fich = fopen (nfichero, "wb"); //al abrir con w se borra el contenido
	if(fich != NULL){
		Salvar (miarbol, fich);
		fclose (fich);
	}
	printf("\nY lo mostramos ordenado\n");
	muestrafichero(nfichero);
	Destruir (&miarbol);

	return EXIT_SUCCESS;
}
