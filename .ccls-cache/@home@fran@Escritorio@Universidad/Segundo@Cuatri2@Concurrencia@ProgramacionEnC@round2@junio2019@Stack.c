/*
 * Stack.c
 *
 *  Created on: 11 jun. 2019
 *      Author: galvez
 */
#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

// Creates an empty stack.
T_Stack create() {
    return NULL;
}

// Returns true if the stack is empty and false in other case.
int isEmpty(T_Stack q) {
    return q == NULL;
}

// Inserts a number into the stack.
void push(T_Stack * pq, int operand) {
    T_Stack new = malloc(sizeof(T_Node));
    if (new == NULL){
        printf("Error: no memory available.\n");
        exit(-1);
    }
    new->number = operand;
    new->next = (*pq);
    *pq = new;
}

// "Inserts" an operator into the stack and operates.
// Returns true if everything OK or false in other case.
int pushOperator(T_Stack * pq, char operator) {
    T_Stack new = malloc(sizeof(T_Node));
    if (new == NULL){
        printf("Error: no memory available.\n");
        exit(-1);
    }
    int value1, value2;
    if (pop(pq, &value1) && pop(pq, &value2)) {
        switch (operator) {
            case '+':
                new->number = value1 + value2;
                break;
            case '-':
                new->number = value1 - value2;
                break;
            case '*':
                new->number = value1 * value2;
                break;
            case '/':
                new->number = value1 / value2;
                break;
            default:
                return 0;
        }
    }
        new->next = (*pq);
        *pq = new;
        return 1;
}

// Puts into data the number on top of the stack, and removes the top.
// Returns true if everything OK or false in other case.
int pop(T_Stack * pq, int * data) {
    if (isEmpty((*pq))) {
        return 0;
    }
    T_Stack aux = (*pq);
    *data = aux->number;
    *pq = aux->next;
    free(aux);
    return 1;
}

// Frees the memory of a stack and sets it to empty.
void destroy(T_Stack * pq) {
    T_Stack aux;
    while ((*pq) != NULL) {
        aux = (*pq);
        free(aux);
        (*pq) = (*pq)->next;
    }
}
