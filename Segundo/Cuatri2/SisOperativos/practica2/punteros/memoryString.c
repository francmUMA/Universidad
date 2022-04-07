#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LONGITUD1 35
#define LONGITUD2 15

int main()
{
  char buffer1[LONGITUD1] = "Cadena original en buffer";
  char buffer2[LONGITUD2] = "Añadimos esto"; 
  char *p_cadena = NULL;
  int i, l_cadena;

  /* Determinamos la longitud de la cadena recibida */

  l_cadena = strlen(buffer1);
  printf("\n");
  printf("La cadena original tiene %d caracteres de longitud\n\n", l_cadena);
  l_cadena = strlen(buffer2);
  printf("La cadena a añadir tiene %d caracteres de longitud\n\n", l_cadena);
 
  /* Ahora, hacemos la concatenación de las dos cadenas */ 
  p_cadena = malloc((LONGITUD1 + LONGITUD2) * sizeof(char));
  strcpy(p_cadena, buffer1);
  strcat(p_cadena, buffer2); 
   
  /* Comprobamos el resultado */
   
  printf("La cadena resultante de la concatenación es = %s\n", p_cadena);
  l_cadena = strlen(p_cadena);
  printf("\n");
  printf("La cadena resultante de la concatenación tiene %d caracteres de longitud\n\n", l_cadena);
  
}
