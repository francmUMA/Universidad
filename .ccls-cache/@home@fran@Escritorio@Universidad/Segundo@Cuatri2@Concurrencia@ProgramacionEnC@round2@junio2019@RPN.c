/*
 ============================================================================
 Name        : RPN.c
 Author      : SGR
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Stack.h"

int process(char * filename);

int main(void) {
	T_Stack q;
	int ok, result;
	q = create();
	if (isEmpty(q)) puts("Now the queue is empty.");
	else puts("Now the queue contains something.");
	push(&q, 3);
	if (isEmpty(q)) puts("Now the queue is empty.");
	else puts("Now the queue contains something.");
	push(&q, 4);
	push(&q, 5);
	ok = pushOperator(&q, '*');
	if (!ok) puts("* cannot operate");
	ok = pushOperator(&q, '+');
	if (!ok) puts("* cannot operate");
	push(&q, 6);
	ok = pushOperator(&q, '+');
	if (!ok) puts("+ cannot operate");
	ok = pop(&q, &result);
	if (!ok) puts("Cannot pop");
	printf("The result is %d.\n", result);
	if (isEmpty(q)) puts("Now the queue is empty.");
	else puts("Now the queue contains something.");

    result = process("source.calc");
    printf("The result from the file is %d.\n", result);
	return EXIT_SUCCESS;
}

int text2Int(char * text) {
	int value=0, i=0;
	while(isdigit(text[i]))
		value = (value*10)+(text[i++]-'0');
	return value;
}

int isOperator(char * text){
	return !isdigit(text[0]);
}

#define MAX_LENGTH 1024
int process(char * filename) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Error: file not found.\n");
        return -1;
    }
    T_Stack stack = create();
    char c[MAX_LENGTH];
    //Save data from the file to the stack
    while (fgets(c, MAX_LENGTH, f) != NULL) {
        if (isOperator(c)) {
            pushOperator(&stack, c[0]);
        } else {
            push(&stack, text2Int(c));
        }
    }
    int result;
    if (pop(&stack, &result)){
        return result;
    } else {
        printf("Error: stack is empty.\n");
        return -1;
    }
}
