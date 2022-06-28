/*
 ============================================================================
 Name        : Main2022.c
 Author      : JBG
 Version     :
 Copyright   : Your copyright notice
 Description :
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Tree.h"

int main(void)
{

	Tree t;
	inicializarArbol(&t);
	printf("Inicializado...\n");

	printf("Insertando tres ejemplos...\n");
	insertarComisaria(&t, "El Torcal", 36.7001727, -4.4473278);
	assert(strcmp(t->name, "El Torcal") == 0);
	assert(t->lat == 36.7001727);
	assert(t->lon == -4.4473278);
	assert(t->left == NULL);
	assert(t->right == NULL);
	printf("Primer elemento insertado\n");

	insertarComisaria(&t, "Distrito Malaga Centro", 36.7247075, -4.4186383);
	assert(strcmp(t->left->name, "Distrito Malaga Centro") == 0);
	assert(t->left->lat == 36.7247075);
	assert(t->left->lon == -4.4186383);
	assert(t->left->left == NULL);
	assert(t->left->right == NULL);
	printf("Segundo elemento a la izquierda insertado\n");

	insertarComisaria(&t, "Territorial Numero 3 Norte", 36.7337666, -4.4503579);
	assert(strcmp(t->right->name, "Territorial Numero 3 Norte") == 0);
	assert(t->right->lat == 36.7337666);
	assert(t->right->lon == -4.4503579);
	assert(t->right->left == NULL);
	assert(t->right->right == NULL);
	printf("Tercer elemento a la derecha insertado\n");

	printf("Mostramos arbol\n");
	mostrarArbol(t);

	char *resultado = localizarComisariaCercana(t, 36.734, -4.455);

	assert(strcmp(resultado, "Territorial Numero 3 Norte") == 0);

	destruirArbol(&t);
	assert(t == NULL);

	cargarComisarias("comisarias.txt", &t);
	assert(strcmp(t->name, "El Torcal") == 0);
	assert(t->lat == 36.7001727);
	assert(t->lon == -4.4473278);
	assert(strcmp(t->left->name, "Distrito Malaga Centro") == 0);
	assert(t->left->lat == 36.7247075);
	assert(t->left->lon == -4.4186383);
	assert(t->left->left == NULL);
	assert(t->left->right == NULL);
	assert(strcmp(t->right->name, "Territorial Numero 3 Norte") == 0);
	assert(t->right->lat == 36.7337666);
	assert(t->right->lon == -4.4503579);
	assert(t->right->left == NULL);
	assert(t->right->right == NULL);

	// Para implementar guardarBinario deberás hacer uso de alguna función auxiliar.
	// Llámala y crea el fichero! Si te sobra tiempo lee de el y mira que está bien.
	guardarBinario("comisariasBinario.bin", t);
	destruirArbol(&t);
	assert(t == NULL);
}
