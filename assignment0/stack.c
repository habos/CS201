#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dll.h"
#include "stack.h"

typedef struct stack{
	DLL *dll;
	void (*display)(void *, FILE *);
        void (*free)(void *);
}STACK;

STACK *newSTACK(void (*d)(void *,FILE *),void (*f)(void *)){
        STACK *stack = malloc(sizeof(STACK));
	stack->dll = newDLL(d, f);
        stack->display = d;
        stack->free = f;
        return stack;
}

void push(STACK *items, void *value){
	insertDLL(items->dll, 0, value);
}

void *pop(STACK *items){
	return removeDLL(items->dll, 0);
}

void *peekSTACK(STACK *items){
	return getDLL(items->dll, 0);
}
int sizeSTACK(STACK *items){
	return sizeDLL(items->dll);
}

void displaySTACK(STACK *items, FILE *p){
        int i;
        fprintf(p, "|");
        if(sizeDLL(items->dll) != 0){
                for(i = 0; i < sizeDLL(items->dll); i++){
                        items->display(getDLL(items->dll, i), p);
                        if(i < sizeDLL(items->dll)-1)
                                fprintf(p, ",");
                }
        }
        fprintf(p, "|");
}

void displaySTACKdebug(STACK *items, FILE *p){
	displayDLLdebug(items->dll, p);
}

void freeSTACK(STACK *items){
	freeDLL(items->dll);
	free(items);
}
