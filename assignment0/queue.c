#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "sll.h"
#include "queue.h"

typedef struct queue{
        SLL *sll;
        void (*display)(void *, FILE *);
        void (*free)(void *);
}QUEUE;

QUEUE *newQUEUE(void (*d)(void *,FILE *),void (*f)(void *)){
        QUEUE *queue = malloc(sizeof(QUEUE));
        queue->sll = newSLL(d, f);
        queue->display = d;
        queue->free = f;
        return queue;
}

void enqueue(QUEUE *items, void *value){
        insertSLL(items->sll, sizeSLL(items->sll), value);
}

void *dequeue(QUEUE *items){
        return removeSLL(items->sll, 0);
}

void *peekQUEUE(QUEUE *items){
        return getSLL(items->sll, 0);
}
int sizeQUEUE(QUEUE *items){
        return sizeSLL(items->sll);
}

void displayQUEUE(QUEUE *items, FILE *p){
        int i;
        fprintf(p, "<");
        if(sizeSLL(items->sll) != 0){
                for(i = 0; i < sizeSLL(items->sll); i++){
                        items->display(getSLL(items->sll, i), p);
                        if(i < sizeSLL(items->sll)-1)
                                fprintf(p, ",");
                }
        }
        fprintf(p, ">");
}

void displayQUEUEdebug(QUEUE *items, FILE *p){
        displaySLLdebug(items->sll, p);
}

void freeQUEUE(QUEUE *items){
        freeSLL(items->sll);
        free(items);
}
