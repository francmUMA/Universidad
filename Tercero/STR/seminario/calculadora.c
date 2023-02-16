/*
 
 En esta práctica vamos a implementar una calculadora básica de operaciones binarias. El
 programa mostrará un menú con las operaciones disponibles y una vez seleccionada la opción
 deseada, pedirá por teclado que se introduzcan los operandos, para luego mostrar el resultado
 y nuevamente el menú. Las opciones son:

 1.- OR lógico
 2.- AND lógico
 3.- XOR lógico
 4.- << (desplazamiento a la izquierda)
 5.- >> (desplazamiento a la derecha)
 6.- Cambio de formato (0→ binario, 1→ hexadecimal). Una vez seleccionado un formato
 determinado, los operandos se interpretarán en ese nuevo formato, al igual que los resultados.
 0.- SALIR

 Adicionalmente se desea implementar una funcionalidad de memoria o log de las operaciones
 realizadas. Para ello se añade la siguiente funcionalidad al menú:

 7.- Habilitar memoria
 8.- Deshabilitar memoria
 9.- Borrar memoria
 10.- Mostrar el contenido de la memoria

*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node* Lista;

struct node {
    union { int dato;               // operando o resultado para hexadecimal
            char dato_binario[9];   // cadena para almacenar el operando/resultado binario
            char operacion[10];     // cadena descriptiva de la operacion
          } contenido;
    Lista siguiente;
} node;


//Implementacion de la funcion itoa
char* itoa(int value, char* result, int base) {
    // check that the base if valid
    if (base < 2 || base > 36) { *result = '\0'; return result; }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while(ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}

void exec_op(char *opcion, int op1, int op2, unsigned char format){

    //Se opera normal
    int res = -1;
    char res_string[32];

    if(opcion[0] == '1'){        //OR
        res = op1 | op2;

    } else if(opcion[0] == '2'){ //AND
        res = op1 & op2;

    } else if(opcion[0] == '3'){ //XOR
        res = op1 ^ op2;

    } else if(opcion[0] == '4'){ //<<
        res = op1 << op2;

    } else if(opcion[0] == '5'){ //>>
        res = op1 >> op2;
    }
    
    //Se transforma al formato correspondiente
    if (res == -1) {
        printf("ERROR al OPERAR!!\n");
    } else {
        if (format == '0'){
            itoa(res, res_string, 2);
        } else {
            itoa(res, res_string, 16);
        }
        printf("El resultado es: %s\n", res_string);
    }
}

void memory_manager(Lista *list){

}

void read_operand(int *operand, unsigned char format){
    char res_read[32];
    char *aux;
    scanf("%s", res_read);
    if (format == '1'){
       *operand = strtol(res_read, &aux, 16); 
    } else {
       *operand = strtol(res_read, &aux, 2);
    } 
    printf("El operando leido es %i\n", *operand);
}

int main(){
    unsigned char format = '0'; 
    char opcion[2];
    int op1, op2;
    while (opcion[0] != '0') {

        //Muestra el modo en el que se trabaja
        if (format == '0') printf("MODO BINARIO");
        else printf("MODO HEXADECIMAL");
        
        //Muestra todas las opciones y lee de teclado la que el usuario haya escrito
        printf("\n1.- OR\n2.- AND\n3.- XOR\n4.- <<\n5.- >>\n6.- Cambio de base\n0.- SALIR\nElige una opción: ");
        fgets(opcion, 2, stdin);
        printf("Opcion escogida: %s", opcion); 

        //Lectura de operandos y ejecucion de una operacion
        if (opcion[0] == '1' || opcion[0] == '2' || opcion[0] == '3' || opcion[0] == '4' || opcion[0] == '5'){
            printf("\nIntroduce el primer operando: ");
            read_operand(&op1, format);
            printf("Introduce el segundo operando: ");
            read_operand(&op2, format);
            exec_op(opcion, op1, op2, format);
        } else if (opcion[0] == '6'){
            format = '1';
        }        
        printf("\n");
    }
    printf("Hasta la proxima!!!"); 
}
