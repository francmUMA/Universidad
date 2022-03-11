/*
 ============================================================================
 Name        : PracticaListaOrdenada.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description :
 ============================================================================
 */

#include <stdlib.h>
#include <assert.h>
#include "gestion_lista.h"

int main(void) {
	Lista l;
	crearLista(&l);
	assert(listaVacia(l) == 0);
	insertarLista(&l, 5);
	insertarLista(&l, 6);
	insertarLista(&l, 4);
	recorrerLista(l);
	extraerLista(&l, 4);
	recorrerLista(l);
	borrarLista(&l);
	return EXIT_SUCCESS;
}
