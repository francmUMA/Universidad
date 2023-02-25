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
#include <string.h>
#include "memory_manager.c"



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

void exec_op(int opcion, int op1, int op2, unsigned char format, Lista *memory){

    //Se opera normal
    int res = -1;
    char res_string[32];
    
    switch (opcion) {
        case 1:
            res = op1 | op2;         //OR
            add_node("OR", memory, 0);
            break;
        case 2:
            res = op1 & op2;
            add_node("AND", memory, 0);
            break;
        case 3:
            res = op1 ^ op2;
            add_node("^", memory, 0);
            break;
        case 4:
            res = op1 << op2;
            add_node("<<", memory, 0);
            break;
        case 5:
            res = op1 >> op2;
            add_node(">>", memory, 0);
            break;
        default: 
            break;
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
    add_node(res_string, memory, 1);
}

void read_operand(int *operand, unsigned char format, Lista *memory){
    char res_read[32];
    char *aux;

    fgets(res_read, 32, stdin);
    add_node(res_read, memory, 1);

    if (format == '1'){
       *operand = strtol(res_read, &aux, 16); 
    } else {
       *operand = strtol(res_read, &aux, 2);
    }

    printf("El operando leido es %i\n", *operand);
}

int main(){
    unsigned char format = '0'; 
    char read_opcion[4];
    int opcion = -1;
    int op1, op2;
    int allow_memory = 0;

    Lista memory;
    create_list(&memory);
    
    while (opcion != 0) {

        //Muestra el modo en el que se trabaja
        if (format == '0') printf("MODO BINARIO");
        else printf("MODO HEXADECIMAL");
        
        //Muestra todas las opciones y lee de teclado la que el usuario haya escrito
        printf("\n1.- OR\n2.- AND\n3.- XOR\n4.- <<\n5.- >>\n6.- Cambio de base\n7.- Habilitar memoria\n8.- Deshabilitar memoria\n9.- Borrar memoria\n10.- Mostrar memoria\n0.- SALIR\nElige una opción: ");
        fgets(read_opcion, 4, stdin); 
        opcion = atoi(read_opcion);
        

        //Lectura de operandos y ejecucion de una operacion
        if (opcion == 1 || opcion == 2 || opcion == 3|| opcion == 4 || opcion == 5){
            printf("\nIntroduce el primer operando: ");
            read_operand(&op1, format, &memory);
            printf("Introduce el segundo operando: ");
            read_operand(&op2, format, &memory);
            exec_op(opcion, op1, op2, format, &memory);

        } else if (opcion == 6){
            if (format == '1') {
                format = '0';
                if (allow_memory) add_node("Cambio(0)", &memory, '0');
            } else {
                format = '1';
                if (allow_memory) add_node("Cambio(1)", &memory, '0'); 
            }

        }

        else if (opcion == 10) print_memory(memory);
        else if (opcion == 7 ) memory_available(&allow_memory);
        else if (opcion == 8 ) memory_unavailable(&allow_memory);
        else if (opcion == 9 ) delete_memory(&memory);
        
        printf("\n");
    }
    delete_memory(&memory);
    printf("Hasta la proxima!!!"); 
}
