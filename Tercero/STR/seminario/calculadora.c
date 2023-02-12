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

typedef struct node {
    union { int dato;               // operando o resultado para hexadecimal
            char dato_binario[9];   // cadena para almacenar el operando/resultado binario
            char operacion[10];     // cadena descriptiva de la operacion
          } contenido;
    void * siguiente;
} node;

int exec_op(int opcion, int op1, int op2){
    if(opcion == 1){        //OR
        return 0;

    } else if(opcion == 2){ //AND
        return 0;

    } else if(opcion == 3){ //XOR
        return 0;

    } else if(opcion == 4){ //<<
        return 0;

    } else if(opcion == 5){ //>>
        return 0;

    } else if(opcion == 6){ //Cambio de base - 0 -> binario, 1 -> hexadecimal
        return 0;

    } else {
        return 0;
    }
}

int main(){
    int opcion, op1, op2;
    printf("1.- OR\n2.- AND\n3.- XOR\n4.- <<\n5.- >>\n6.- Cambio de base (0 -> binario, 1 -> hexadecimal)\n0.- SALIR\nElige una opción: ");
    scanf("%d", &opcion);
    if (opcion != 0){
        printf("\nIntroduce los operandos: ");
        scanf("%d %d", &op1, &op2);
        printf("El resultado es: %d", exec_op(opcion, op1, op2));   
    } else {
        printf("Hasta la proxima!!!");
    }
}
