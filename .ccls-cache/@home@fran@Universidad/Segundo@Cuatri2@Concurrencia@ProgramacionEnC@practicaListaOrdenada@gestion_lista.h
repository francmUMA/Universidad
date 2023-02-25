/*
============================================================================
 Name        : gestion_lista.h
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description :
 ============================================================================
 */

#ifndef _GESTION_LISTAORDENADA_
#define _GESTION_LISTAORDENADA_

typedef struct NodoLista* Lista;

struct NodoLista{

	int elem;

	Lista sig;

};

void crearLista(Lista *l); //crea una lista vacía

void recorrerLista(Lista l); //escribe en la pantalla los elementos de la lista

int listaVacia(Lista l); //devuelve 0 sii la lista está vacía

void insertarLista(Lista *l,int elem); // inserta el elemento elem en la lista l de forma que quede ordenada de forma creciente

int extraerLista(Lista *l,int elem); // elimina de la lista el elemento elem. Devuelve 1 si se ha podido eliminar y 0, si elem no estaba en la lista.

void borrarLista(Lista *l); //elimina todos los nodos de la lista y la deja vacía


#endif
