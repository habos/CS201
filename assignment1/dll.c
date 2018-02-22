#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dll.h"
/**
 * Double Linked List class that includes a DLL and NODE struct.
 *
 * @author Harry Bos
 */
//Define node struct
typedef struct node{
        void *value;
        struct node *next;
	struct node *prev;
}NODE;//end node struct

//Define DLL struct
typedef struct dll{
        NODE *head;
        NODE *tail;
        int size;
        void (*display)(void *, FILE *);
        void (*free)(void *);
}DLL;//end DLL struct

/*
* NAME: newDLL
*
* PURPOSE : Construct DLL struct and difine variables
*
* RETURN :  DLL struct
*/
DLL *newDLL(void (*d)(void *,FILE *),void (*f)(void *)){
        DLL *items = malloc(sizeof(DLL));
        assert(items != 0);
        items->head = 0;
        items->tail = 0;
        items->size = 0;
        items->display = d;
        items->free = f;
        return items;
}//end DLL constructor

/*
* NAME: insertDLL
*
* PURPOSE : Insert a node into the SLL struct
*
* RETURN : void
*/
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
		for(i = items->size; i > index+1; i--){
			curNode = curNode->prev;
		}
		newNode->prev = curNode->prev;
		newNode->next = curNode;
		curNode->prev->next = newNode;
		curNode->prev = newNode;
		items->size++;
	}
}//end insertDLL

/*
* NAME: removeDLL
*
* PURPOSE : Remove a node from DLL
*
* RETURN :  void * = Value of removed node
*/
void *removeDLL(DLL *items, int index){
	void *temp;
	if(items->size == 0 || index >= items->size) {return 0;}
	NODE *curNode = items->head;
	int i = 0;
	//Delete at beginning
	if(items->size == 1){
		temp = curNode->value;
		items->head->next = 0;
		items->tail->prev = 0;
		items->head = 0;
		items->tail = 0;
		items->size = 0;
		free(curNode);
		return temp;
		
	}
	if(index == 0){
		items->head = items->head->next;
		items->head->prev = 0;
		temp = curNode->value;
		//items->free(curNode->value);
		free(curNode);
		items->size--;
		return temp;
	}
	if(index == items->size-1){
		curNode = items->tail;
		temp = curNode->value;
		items->tail = curNode->prev;
		items->tail->next = 0;
		//items->free(curNode->value);
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
		for(i = items->size; i > index+1; i--){
			curNode = curNode->prev;
		}
		curNode->prev->next = curNode->next;
		curNode->next->prev = curNode->prev;
	}
	temp = curNode->value;
	//items->free(curNode->value);
	free(curNode);
	items->size--;
	return temp;
}//end removeDLL

/*
* NAME: unionDLL
*
* PURPOSE : Add the donor to the recipient and empty the donor
*
* RETURN :  void
*/
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
	//Set donor to show no nodes
	donor->head = 0;
	donor->tail = 0;
	donor->size = 0;
}//end unionDLL

/*
* NAME: getDLL
*
* PURPOSE : Get the value of the node at the given index
*
* RETURN :  void *
*/
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
		for(i = items->size; i > index+1; i--){
			curNode = curNode->prev;
		}
	}
	return curNode->value;
}//end getDLL

/*
* NAME: setDLL
*
* PURPOSE : Set the value of the node at the given index with the given value
*
* RETURN :  void *
*/
void *setDLL(DLL *items, int index, void *value){
	int i;
	void *temp;
	NODE *curNode = items->head;
	//Check if index is valid
	if(index > items->size || items->size == 0) {return 0;}
	//Check if value needs to be comments
	if(index == items->size){
		insertDLL(items, items->size, value);
		return 0;
	}
	//Set node in list
	if(index <= items->size/2){
		for(i = 0; i < index; i++){
			curNode = curNode->next;
		}	
	}else{
		curNode = items->tail;
		for(i = items->size; i > index+1; i--){
			curNode = curNode->prev;
		}
	}
	temp = curNode->value;
	curNode->value = value;
	return temp;
}//end setDLL
/*
* NAME: sizeDLL
*
* PURPOSE : Returns the size of the DLL
*
* RETURN :  int
*/
int sizeDLL(DLL *items){
	return items->size;
}//end sizeDLL

/*
* NAME: displayDLL
*
* PURPOSE : Display the DLL
*
* RETURN :  void
*/
void displayDLL(DLL *items, FILE *p){
	int i;
	NODE *curNode = items->head;
	fprintf(p, "{{");
	if(items->size != 0){
		for(i = 0; i < items->size; i++){
			items->display(curNode->value, p);
			if(i < items->size-1)
				fprintf(p, ",");
			curNode = curNode->next;
		}
	}
	fprintf(p, "}}");
}//end displayDLL

/*
* NAME: displayDLLdebug
*
* PURPOSE : Display the DLL with head and tail shown
*
* RETURN :  void
*/
void displayDLLdebug(DLL *items, FILE *p){
	int i;
	NODE *curNode = items->head;
	fprintf(p, "head->{{");
	if(items->size != 0){
		for(i = 0; i < items->size; i++){
			items->display(curNode->value, p);
			if(i < items->size-1)
				fprintf(p, ",");
			curNode = curNode->next;
		}
	}
	fprintf(p, "}},tail->{{");
        if(items->size != 0){
		items->display(items->tail->value, p);
	}
	fprintf(p, "}}");
}//end displayDLLdebug

/*
* NAME: freeDLL
*
* PURPOSE : Free the DLL struct
*
* RETURN :  void
*/
void freeDLL(DLL *items){
	if(items->size == 0 || items->head == 0){
		free(items);
		return;
	}
	NODE *tempNode = items->head;
	while(items->head != 0){
		tempNode = items->head;
		items->head = items->head->next;
		if(items->free != 0)
			items->free(tempNode->value);
		free(tempNode);
	}
	free(items);
}//end freeDLL











