#include <stdio.h>
#include <string.h>
/*
En este ejercicio vamos a explorar como los arrays se pasan como parámetros y como estos se pueden devolver en una función.

1.- Copia estos dos procedimientos
*/
/*
void encriptar_y_mostrar(char * entrada){
  printf("\n----Encriptar\n");
  for (size_t i = 0; i < strlen(entrada); i++)
  {
    printf("%c",entrada[i] + 1);
  }
  printf("\n");
}

void desencriptar_y_mostrar(char * entrada){
  printf("\n----Desencriptar\n");
  for (size_t i = 0; i < strlen(entrada); i++)
  {
    printf("%c",entrada[i] - 1);
  }
  printf("\n");
}

int main()
{
    char encriptar[11]="Hola mundo";
    char desencriptar[11]="Ipmb!nvoep";
    encriptar_y_mostrar(encriptar);
    desencriptar_y_mostrar(desencriptar);
}
*/
/*
En el main declara dos cadenas:

char encriptar[11]="Hola mundo";
char desencriptar[11]="Ipmb!nvoep";

Y llama a encriptar_y_mostrar con la cadena encriptar y a desencriptar_y_mostrar con la cadena desencriptar.

¿Funciona correctamente?
¿Las cadenas encriptar y desencriptar se modifican tras la llamada al procedimiento? Usa el debug.
/



/ 
2.- Usa ahora const 
void encriptar_y_mostrar(const char * entrada)
void desencriptar_y_mostrar(const char * entrada)

¿Funciona correctamente? Arregla el código para que lo muestre sin modificar.


/

/ 
3.- Vamos ahora redefinir el concepto a encriptar_fun y desencriptar_fun. Vamos a crear dos funciones que tienen como entrada una cadena (que deben modificar) y además, la misma cadena la van a devolver como salida. Crea dos nuevas cadenas para ver los resultados de estas nuevas funciones e invócalas.
¿Qué ocurre con las cuatro cadenas?


*/
#include <stdio.h>
#include <string.h>
/*
En este ejercicio vamos a explorar como los arrays se pasan como parámetros y como estos se pueden devolver en una función.

1.- Copia estos dos procedimientos

void encriptar_y_mostrar(char * entrada){
  printf("\n----Encriptar\n");
  for (size_t i = 0; i < strlen(entrada); i++)
  {
    entrada[i]++;
    printf("%c",entrada[i]);
  }
  printf("\n");
}

void desencriptar_y_mostrar(char * entrada){
  printf("\n----Desencriptar\n");
  for (size_t i = 0; i < strlen(entrada); i++)
  {
    entrada[i]--;
    printf("%c",entrada[i]);
  }
  printf("\n");
}

En el main declara dos cadenas:

char encriptar[11]="Hola mundo";
char desencriptar[11]="Ipmb!nvoep";

Y llama a encriptar_y_mostrar con la cadena encriptar y a desencriptar_y_mostrar con la cadena desencriptar.

¿Funciona correctamente?
¿Las cadenas encriptar y desencriptar se modifican tras la llamada al procedimiento? Usa el debug.
*/



/* 
2.- Usa ahora const 
void encriptar_y_mostrar(const char * entrada)
void desencriptar_y_mostrar(const char * entrada)

¿Funciona correctamente? Arregla el código para que lo muestre sin modificar.


*/

/* 
3.- Vamos ahora redefinir el concepto a encriptar_fun y desencriptar_fun. Vamos a crear dos funciones que tienen como entrada una cadena (que deben modificar) y además, la misma cadena la van a devolver como salida. Crea dos nuevas cadenas para ver los resultados de estas nuevas funciones e invócalas.
¿Qué ocurre con las cuatro cadenas?


*/