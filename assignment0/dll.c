#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "sll.h"

//Define node struct
typedef struct node{
        void *value;
        struct node *next;
	struct node *prev;
}NODE;//end node stru

typedef struct dll{
        NODE *head;
        NODE *tail;
        int size;
        void (*display)(void *, FILE *);
        void (*free)(void *);
}DLL;//end SLL struct

DLL *newDLL(void (*d)(void *,FILE *),void (*f)(void *)){
        DLL *items = malloc(sizeof(DLL));
        assert(items != 0);
        items->head = 0;
        items->tail = 0;
        items->size = 0;
        items->display = d;
        items->free = f;
        return items;
}

void insertDLL(DLL *items, int index, void *value){

}

