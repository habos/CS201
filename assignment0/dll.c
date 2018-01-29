#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dll.h"

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
	//Create new SLL node with value
	int i;
	NODE *newNode = (NODE*)malloc(sizeof(NODE));
	newNode->value = value;
	//Set new node next to null
	newNode->next = 0;
	newNode->prev = 0;
	//Check if adding first node to DLL
	if(items->size == 0){
		items->head = newNode;
		items->tail = newNode;
		items->size++;
		return;
	}
	if(index == 0){
		newNode->next = items->head;
		items->head->prev = newNode;
		items->head = newNode;
		items->size++;
		return;
	}
	if(index == items->size){
		items->tail->next = newNode;
		newNode->prev = items->tail;
		items->tail = newNode;
		items->size++;
		return;
	}
	NODE *curNode = items->head;
	if(index <= items->size/2){
		for(i = 0; i < index-1; i++){
			curNode = curNode->next;
		}
		newNode->next = curNode->next;
		newNode->prev = curNode;
		curNode->next->prev = newNode;
		curNode->next = newNode;
		items->size++;
	}else{
		curNode = items->tail;
		for(i = items->size; i > index; i--){
			curNode = curNode->prev;
		}
		newNode->prev = curNode->prev;
		newNode->next = curNode;
		curNode->prev->next = newNode;
		curNode->prev = newNode;
		items->size++;
	}
}

void *removeDLL(DLL *items, int index){
	void *temp;
	if(items->size == 0 || index >= items->size) {return 0;}
	NODE *curNode = items->head;
	int i = 0;
	//Delete at beginning
	if(index == 0){
		items->head = items->head->next;
		items->head->prev = 0;
		temp = curNode->value;
		items->free(curNode->value);
		free(curNode);
		items->size--;
		return temp;
	}
	if(index == items->size-1){
		curNode = items->tail;
		temp = curNode->value;
		items->tail = curNode->prev;
		items->tail->next = 0;
		items->free(curNode->value);
		free(curNode);
		items->size--;
		return temp;
	}
	if(index <= items->size/2){
		for(i = 0; i < index; i++){
			curNode = curNode->next;
		}
		curNode->prev->next = curNode->next;
		curNode->next->prev = curNode->prev;
	}else{
		curNode = items->tail;
		for(i = items->size; i > index; i--){
			curNode = curNode->prev;
		}
		curNode->prev->next = curNode->next;
		curNode->next->prev = curNode->prev;
	}
	temp = curNode->value;
	items->free(curNode->value);
	free(curNode);
	items->size--;
	return temp;
}

void unionDLL(DLL *recipient, DLL *donor){
	//Check if DLL is empty
	if(donor->size == 0) {return;}
	//Make tail of recipient point to head of donor
	if(recipient->size == 0){
		recipient->head = donor->head;
	}else{
		recipient->tail->next = donor->head;
		donor->head->prev = recipient->tail;
	}
	recipient->tail = donor->tail;
	recipient->size += donor->size;
	int i;
	void *temp;
	for(i = 0; i < donor->size; i++){
		temp = removeDLL(donor, i);
	}
}

void *getDLL(DLL *items, int index){
	int i;
	NODE *curNode = items->head;
	//Check if index is valid
	if(index >= items->size || items->size == 0) {return 0;}
	//Get value from list
	if(index <= items->size/2){
		for(i = 0; i < index; i++){
			curNode = curNode->next;
		}
	}else{
		curNode = items->tail;
		for(i = items->size; i > index; i--){
			curNode = curNode->prev;
		}
	}
	return curNode->value;
}

void *setDLL(DLL *items, int index, void *value){
	int i;
	void *temp;
	NODE *curNode = items->head;
	//Check if index is valid
	if(index > items->size || index->size == 0) {return 0;}
	//Check if value needs to be comments
	if(index == items->size){
		NODE *newNode = (NODE*)malloc(sizeof(NODE));
		newNode->value = value;
		items->tail->next = newNode;
		newNode->next = 0;
		newNode->prev = items->tail;
		items->tail = newNode;
		items->size++;
	}
	//Set node in list
	if(index <= items->size/2){
		for(i = 0; i < index; i++){
			curNode = curNode->next;
		}	
	}else{
		curNode = items->tail;
		for(i = items->size; i > index; i--){
			curNode = curNode->prev;
		}
	}
	temp = curNode->value;
	curNode->value = value;
	return temp;
}

int sizeDLL(DLL *items){
	return items->size;
}

void displayDLL(DLL *items, FILE *p){
	int i;
	NODE *curNode = items->head;
	fprintf(p, "{{");
	if(items->size != 0){
}













