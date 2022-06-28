#include "Tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Inicializa un árbol a vacío.
// 0.25 pts.
void inicializarArbol(Tree *ptrTree){
    *ptrTree = NULL;
}

// Asumiendo que el árbol está ordenado (Binary Search Tree),
// se inserta un nuevo nodo ordenado por nombre con los datos
// pasados como parámetros
// El BST está ordenado por name
// 1.75 pts.
void insertarComisaria(Tree *ptrTree, char *name, double lat, double lon){
    Tree newNode = malloc(sizeof(Node));
    newNode -> name = malloc (strlen(name) + 1);
    strcpy(newNode -> name, name);
    newNode -> lat = lat;
    newNode -> lon = lon;
    if (*ptrTree == NULL){
        newNode->left = NULL;
        newNode->right = NULL;
        *ptrTree = newNode;
    }
    else if (strcmp(name, (*ptrTree)->name) < 0){
        insertarComisaria(&(*ptrTree)->left, name, lat, lon);
    }
    else if (strcmp(name, (*ptrTree)->name) > 0){
        insertarComisaria(&(*ptrTree)->right, name, lat, lon);
    }
    else{
        printf("Error: Comisaria ya existe\n");
    }
}

// Muestra el árbol en orden, es decir, recorrido infijo.
// 1.0 pt.
void mostrarArbol(Tree t){
    if (t != NULL){
        mostrarArbol(t->left);
        printf("%s\n", t->name);
        mostrarArbol(t->right);
    } else {
        printf("Arbol vacio\n");
    }
}

// Libera toda la memoria y deja el árbol vacío.
// 1.25 pts.
void destruirArbol(Tree *ptrTree){
    if (*ptrTree != NULL){
        destruirArbol(&(*ptrTree)->left);
        destruirArbol(&(*ptrTree)->right);
        free((*ptrTree)->name);
        free(*ptrTree);
        *ptrTree = NULL;
    }
}

Tree localizarNodoComisariaCercana(Tree t, double lat, double lon){
    if (t == NULL){
        return NULL;
    } else {
        if (t -> left == NULL && t -> right == NULL){
            return t;
        } else if (t -> left == NULL){
            int res_this, res_right;
            res_this = distancia(lat, lon, t -> lat, t -> lon);
            Tree right = localizarNodoComisariaCercana(t -> right, lat, lon);
            res_right = distancia(lat, lon, right -> lat, right -> lon);
            if (res_this < res_right){
                return t;
            } else {
                return right;
            }
        } else if (t -> right == NULL){
            int res_this, res_left;
            res_this = distancia(lat, lon, t -> lat, t -> lon);
            Tree left = localizarNodoComisariaCercana(t -> left, lat, lon);
            res_left = distancia(lat, lon, left -> lat, left -> lon);
            if (res_this < res_left){
                return t;
            } else {
                return left;
            }
        } else {
            int res_this, res_left, res_right;
            res_this = distancia(lat, lon, t -> lat, t -> lon);
            Tree left = localizarNodoComisariaCercana(t -> left, lat, lon);
            res_left = distancia(lat, lon, left -> lat, left -> lon);
            Tree right = localizarNodoComisariaCercana(t -> right, lat, lon);
            res_right = distancia(lat, lon, right -> lat, right -> lon);
            if (res_this < res_left && res_this < res_right){
                return t;
            } else if (res_left < res_right){
                return left;
            } else {
                return right;
            }
        }
    }
}

int distancia(double lat1, double lon1, double lat2, double lon2){
    return abs(lat1 - lat2) + abs(lon1 - lon2);
}

// Devuelve el nombre de la comisaría más cercana dada una latitud y longitud.
// Si el árbol está vacío, se devuelve NULL.
// Para saber la cercania nos basamos en la formula 𝑑𝑖𝑠𝑡 = |𝑙𝑎𝑡 − 𝑙𝑎𝑡′| + |𝑙𝑜𝑛 − 𝑙𝑜𝑛′|.
// 2.0 pt.
char *localizarComisariaCercana(Tree t, double lat, double lon){
    Tree res = localizarNodoComisariaCercana(t, lat, lon);
    if (res == NULL){
        return NULL;
    } else {
        return res->name;
    }
}

// Carga el fichero de texto que tiene la siguiente estructura:
// nombre comisaria 1; latitude1; longitude1;
// nombre comisaria 2; latitude2; longitude2;
// …
// y crea un árbol con un nodo por cada línea en ptrTree.
//
// 1.75 pts.
void cargarComisarias(char *filename, Tree *ptrTree){
    FILE *file = fopen(filename, "r");
    if (file == NULL){
        printf("Error: No se pudo abrir el archivo\n");
    } else {
        char *line = malloc(sizeof(char) * 100);
        while (fgets(line, 100, file) != NULL){
            //La primera parte de line hace referencia a la comisaria, la segunda a la latitud y la tercera a la longitud
            char *name = malloc(sizeof(char)*100);
            strcpy(name, strtok(line, ";"));
            double lat = strtod(strtok(NULL, ";"), NULL);
            double lon = strtod(strtok(NULL, ";"), NULL);
            insertarComisaria(ptrTree, name, lat, lon);
        }
        free(line);
        fclose(file);
    }
}

// Guarda el arbol ordenador en un fichero binario.
// Cada nodo será almacenado en el fichero con la siguiente estructura:
// - Un entero con la longitude del campo name.
// - Los carácteres del campo name.
// - Un double con la latitud.
// - Un double con la longitud.
//
// 2.0 pts.
void guardarBinario(char *filename, Tree tree){
    if (tree != NULL){
        guardarBinario(filename, tree->left);
        FILE *file = fopen(filename, "ab");
        size_t len = strlen(tree->name);
        fwrite(&len, sizeof(size_t), 1, file);
        fwrite(tree->name, sizeof(char), strlen(tree->name), file);
        fwrite(&tree->lat, sizeof(double), 1, file);
        fwrite(&tree->lon, sizeof(double), 1, file);
        fclose(file);
        guardarBinario(filename, tree->right);
    }
}


