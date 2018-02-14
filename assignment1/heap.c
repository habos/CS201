#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "bst.h"
#include "queue.h"
#include "stack.h"
#include "integer.h"
/*
 * @author Harry Bos
 */
//Define heap struct
typedef struct heap{
        BST *bst;
        int size;
	QUEUE *queue;
	STACK *stack;
	void (*display)(void *, FILE *);
	int (*compare)(void *, void *);
	void (*free)(void *);
}HEAP;//end bstnode struct

static void heapify(HEAP *h, BSTNODE *n);
static bool isLeaf(BSTNODE *n);

HEAP *newHEAP(void (*display)(void *, FILE *), int (*compare)(void *, void *), void (*free)(void *)){
	HEAP *newHeap = malloc(sizeof(HEAP));
	newHeap->bst = newBST(display, compare, 0, free);
	newHeap->queue = newQUEUE(display, free);
	newHeap->stack = newSTACK(display, free);
	newHeap->size = 0;
	newHeap->display = display;
	newHeap->free = free;
	newHeap->compare = compare;
	return newHeap;
}//end constructor

void insertHEAP(HEAP *h, void *value){
	BSTNODE *newNode = newBSTNODE(value);
	BSTNODE *insertNode = 0;
	if(getBSTroot(h->bst) == 0){
		setBSTroot(h->bst, newNode);
		enqueue(h->queue, newNode);
		h->size++;
		setBSTsize(h->bst, h->size);
		return;	
	}
	while(true){
		insertNode = peekQUEUE(h->queue);
		if(getBSTNODEleft(insertNode) == 0){
			setBSTNODEleft(insertNode, newNode);
			setBSTNODEparent(newNode, insertNode);
			enqueue(h->queue, newNode);
			push(h->stack, insertNode);
			break;
		}
		if(getBSTNODEright(insertNode) == 0){
			setBSTNODEright(insertNode, newNode);
			setBSTNODEparent(newNode, insertNode);
			enqueue(h->queue, newNode);
			break;
		}
		dequeue(h->queue);
	}
	h->size++;
	setBSTsize(h->bst, h->size);
}//end insertHEAP

void buildHEAP(HEAP *h){
	if(getBSTroot(h->bst) == 0 || isLeaf(getBSTroot(h->bst))) return;
	BSTNODE *curNode = 0;
	while(sizeSTACK(h->stack) > 0){
		curNode = pop(h->stack);
		heapify(h, curNode);
	}
}//end buildHEAP

void *peekHEAP(HEAP *h){
	return getBSTNODEvalue(getBSTroot(h->bst));
}

void *extractHEAP(HEAP *h){
	printf("djfkal");
	STACK *tempStack = newSTACK(h->display, h->free);
	printf("fdfffff");
	if(getBSTroot(h->bst) == 0) return 0;
	void *temp = getBSTNODEvalue(getBSTroot(h->bst));
	printf("fdsafds");
	BSTNODE *curNode = getBSTroot(h->bst);
	int n = h->size;
	printf("fdsafs");
	while(n > 0){
		push(tempStack, newINTEGER(n%2));
		printf("fdsafdsss");
		n = n/2;
	}
	printf("%d", sizeSTACK(tempStack));
	while(sizeSTACK(tempStack) > 0){
		if(0 == getINTEGER(pop(tempStack))){
			curNode = getBSTNODEleft(curNode);
		}
		if(1 == getINTEGER(pop(tempStack)))
			curNode = getBSTNODEright(curNode);
	} 
	setBSTNODEvalue(getBSTroot(h->bst), getBSTNODEvalue(curNode));
	freeBSTNODE(curNode, h->free);
	h->size--;
	setBSTsize(h->bst, h->size);
	heapify(h, getBSTroot(h->bst));
	return temp;
}

int sizeHEAP(HEAP *h){
	return h->size;
}

void displayHEAP(HEAP *h, FILE *fp){
	displayBST(h->bst, fp);
}

void displayHEAPdebug(HEAP *h, FILE *fp){
	fprintf(fp, "heap size: %d\n", h->size);
	fprintf(fp, "bst size: %d\n", sizeBST(h->bst));
	displayBSTdebug(h->bst, fp);
}//end displayHEAPdebug

void freeHEAP(HEAP *h){
	freeBST(h->bst);
	freeQUEUE(h->queue);
	free(h);
}

static void heapify(HEAP *h, BSTNODE *n){
	BSTNODE *left = getBSTNODEleft(n);
	BSTNODE *right = getBSTNODEright(n);
	BSTNODE *largest = 0;
	if(left != 0 && h->compare(getBSTNODEvalue(left), getBSTNODEvalue(n)) < 0){
		largest = left;
	}
	else largest = n;
	if(right != 0 && h->compare(getBSTNODEvalue(right), getBSTNODEvalue(largest)) < 0){
		largest = right;
	}
	if(h->compare(getBSTNODEvalue(largest), getBSTNODEvalue(n)) != 0){
		void *temp = getBSTNODEvalue(largest);
		setBSTNODEvalue(largest, getBSTNODEvalue(n));
		setBSTNODEvalue(n, temp);
		heapify(h, largest);
	}
}//end heapify

static bool isLeaf(BSTNODE *n){
	if(n == 0) return true;
	BSTNODE *left = getBSTNODEleft(n);
	BSTNODE *right = getBSTNODEright(n);
	return left == 0 && right == 0;
}//end isLeaf

