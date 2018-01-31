#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "sll.h"

//Define node struct
typedef struct node{
	void *value;
        struct node *next;
}NODE;//end node stru

typedef struct sll{
	NODE *head;
	NODE *tail;
	int size;
	void (*display)(void *, FILE *);
	void (*free)(void *);
}SLL;//end SLL struct

SLL *newSLL(void (*d)(void *,FILE *),void (*f)(void *)){
	SLL *items = malloc(sizeof(SLL));
	assert(items != 0);
	items->head = 0;
	items->tail = 0;
	items->size = 0;
	items->display = d;
	items->free = f;
	return items;
}//end constructor

void insertSLL(SLL *items, int index, void *value){
	//Create new SLL node with value
	int i;
	NODE *newNode = (NODE*)malloc(sizeof(NODE));
	newNode->value = value;
	//Set new node next to null
	newNode->next = 0;
	//Check if adding first node to SLL
	if(items->size == 0){
		items->head = newNode;
		items->tail = newNode;
		items->size++;
		return;
	}
	//Check if adding new head node (insert front)
	if(index == 0 && items->size > 0){
		newNode->next = items->head;
		items->head = newNode;
		items->size++;
		return;
	}
	//Check if adding new tail node (insert end)
	if(index == items->size && items->size > 0){
		items->tail->next = newNode;
		items->tail = newNode;
		items->size++;
		return;
	}
	//Add node to SLL if in middle
	NODE *curNode = items->head;
	for(i = 0; i < index-1; i++) {
		curNode = curNode->next;
	}
	newNode->next = curNode->next;
	curNode->next = newNode;
	items->size++;
}//end insertSLL

void *removeSLL(SLL *items, int index){
	//Check if SLL is empty
	void *temp;
	if(items->size == 0) {return 0;}
	NODE *curNode = items->head;
	NODE *prevNode = 0;
	int i = 0;
	//Check in node to be removed is head node
	if(items->size == 1){
		temp = curNode->value;
		free(curNode);	
		items->head = 0;
		items->tail = 0;
		items->size = 0;
		return temp;
	}
	if(index == 0){
		items->head = items->head->next;
		temp = curNode->value;
		//items->free(curNode->value);
		free(curNode);
		items->size--;
		return temp;
	}
	//Check for removal of end node
	if(index == items->size-1){
		while(curNode->next != 0){
			prevNode = curNode;
			curNode = curNode->next;
		}
		items->tail = prevNode;
		prevNode->next = 0;
		temp = curNode->value;
		//items->free(curNode->value);
		free(curNode);
		items->size--;
		return temp;
	}
	//Delete node in position
	for(i = 0; i < index; i++){
		prevNode = curNode;
		curNode = curNode->next;
	}
	prevNode->next = curNode->next;
	temp = curNode->value;
	//items->free(curNode->value);
	free(curNode);
	items->size--;
	return temp;
}//end removeSLL

void unionSLL(SLL *recipient, SLL *donor){
	//Check if either SLL is empty
	if(donor->size == 0){return;}
	//Make tail of recipient point to head of donor
	if(recipient->size == 0){
		recipient->head = donor->head;
	}else{
		recipient->tail->next = donor->head;
	}
	//Set new tail and size
	recipient->tail = donor->tail;
	recipient->size += donor->size;
	//Remove all the nodes from the donor
	donor->head = 0;
	donor->tail = 0;
	donor->size = 0;
}

void *getSLL(SLL *items, int index){
	int i;
	NODE *curNode = items->head;
	//Check if index is valid
	if(index >= items->size || items->size == 0){return 0;};
	//Check if item is in back of list
	if(index == items->size-1){return items->tail->value;}
	//Find item
	for(i = 0; i < index; i++){
		curNode = curNode->next;	
	}
	//Return value
	return curNode->value;
}

void *setSLL(SLL *items, int index, void *value){
	int i;
	void *temp;
	NODE *curNode = items->head;
	//Check if index is valid
	if(index > items->size || items->size == 0){return 0;}
	//Check if index is equal to size and needs to be appended
	if(index == items->size){
		insertSLL(items, items->size, value);
	/*
		NODE *newNode = (NODE*)malloc(sizeof(NODE));
		newNode->value = value;
                items->tail->next = newNode;
                items->tail = newNode;
		newNode->next = 0;
                items->size++;
	*/
                return 0;
        }
	//Check if index is the tail
	if(index == items->size-1){
		temp = items->tail->value;
		items->tail->value = value;
		return temp;
	}
	//Find node and replace value
	for(i = 0; i < index; i++){
		curNode = curNode->next;
	}
	temp = curNode->value;
	curNode->value = value;
	return temp;
}

int sizeSLL(SLL *items){
	return items->size;
}

void displaySLL(SLL *items, FILE *p){
	int i;
	NODE *curNode = items->head;
	fprintf(p, "{");
	if(items->size != 0){
		for(i = 0; i < items->size; i++){
			items->display(curNode->value, p);
			if(i < items->size-1)
				fprintf(p, ",");
			curNode = curNode->next;
		}
	}
	fprintf(p, "}");
}

void displaySLLdebug(SLL *items,FILE *p){
	int i;
	NODE *curNode = items->head;
	fprintf(p, "head->{");
	if(items->size != 0){
		for(i = 0; i < items->size; i++){
			items->display(curNode->value, p);
			if(i < items->size-1)
				fprintf(p, ",");
			curNode = curNode->next;
		}
	}
	fprintf(p, "},tail->{");
        if(items->size != 0){
		items->display(items->tail->value, p);
	}
	fprintf(p, "}");
}

void freeSLL(SLL *items){
	if(items->size == 0){
		free(items->head);
		free(items);
		return;
	}
	NODE *tempNode = 0;
	while(items->head != 0){
		tempNode = items->head;
		items->head = items->head->next;
		items->free(tempNode->value);
		free(tempNode);	
	}
	free(items);
}













