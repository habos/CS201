#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "bst.h"
#include "queue.h"
/*
 * @author Harry Bos
 */
//Define node struct
typedef struct bstnode{
	void *value;
	struct bstnode *left;
	struct bstnode *right;
	struct bstnode *parent;
}BSTNODE;//end bstnode struct

//Define BST struct
typedef struct bst{
	BSTNODE *root;
	int size;
	void (*display)(void *, FILE *);
	void (*free)(void *);
	void (*swapper)(BSTNODE *,BSTNODE *);
	int (*comparator)(void *, void *);
}BST;//end BST struct

static void genericSwap(BSTNODE *a, BSTNODE *b);
static int minDepth(BSTNODE *n);
static int maxDepth(BSTNODE *n);
static bool isLeaf(BSTNODE *n);
static BSTNODE *predecessor(BSTNODE *n);
static BSTNODE *successor(BSTNODE *n);
static BSTNODE *treeMin(BSTNODE *n);
static BSTNODE *treeMax(BSTNODE *n);
static void printPreOrder(BSTNODE *n, BST *t, FILE *fp);
static void freeBSTNodes(BSTNODE *n, BST *t);

BSTNODE *newBSTNODE(void *v){
	BSTNODE *newNode = malloc(sizeof(BSTNODE));
	newNode->value = v;
	newNode->left = 0;
	newNode->right = 0;
	newNode->parent = 0;
	return newNode;
}//end BSTNODE constructor

void *getBSTNODEvalue(BSTNODE *n){
	return n->value;
}//end getBSTNODEvalue 

void setBSTNODEvalue(BSTNODE *n, void *value){
	n->value = value;
}//end setBSTNODEvalue

BSTNODE *getBSTNODEleft(BSTNODE *n){
	return n->left;
}//end getBSTNODEleft

void setBSTNODEleft(BSTNODE *n, BSTNODE *replacement){
	n->left = replacement;
}//end setBSTNODEleft

BSTNODE *getBSTNODEright(BSTNODE *n){
	return n->right;
}//end getBSTNODEright

void setBSTNODEright(BSTNODE *n, BSTNODE *replacement){
	n->right = replacement;
}//end setBSTNODEright

BSTNODE *getBSTNODEparent(BSTNODE *n){
	return n->parent;
}//end getBSTNODEparent

void setBSTNODEparent(BSTNODE *n, BSTNODE *replacement){
	n->parent = replacement;
}//end setBSTNODEparent

void freeBSTNODE(BSTNODE *n, void (*free)(void *)){
	if(free != 0)
		free(n->value);
	free(n);
}//end freeBSTNODE

//START BST FUNCTIONS

BST *newBST(void (*d)(void *, FILE *), int (*c)(void *, void *), void (*s)(BSTNODE *, BSTNODE *), void (*f)(void *)){
	BST *newBST = malloc(sizeof(BST));
	assert(newBST != 0);
	newBST->root = 0;
	newBST->size = 0;
	newBST->free = f;
	newBST->display = d;
	if(s == 0)
		newBST->swapper = genericSwap;
	else newBST->swapper = s;
	newBST->comparator = c;
	return newBST;
}//end BST constructor

BSTNODE *getBSTroot(BST *t){
	return t->root;
}//end getBSTroot

void setBSTroot(BST *t, BSTNODE *replacement){
	t->root = replacement;
}//end setBSTroot

void setBSTsize(BST *t, int size){
	t->size = size;
}//end setBSTsize

BSTNODE *insertBST(BST *t, void *value){
	BSTNODE *searchNode = t->root;
	BSTNODE *prevNode = 0;
	BSTNODE *newNode = newBSTNODE(value);
	while(searchNode != 0){
		prevNode = searchNode;
		if(t->comparator(newNode->value, searchNode->value) < 0)
			searchNode = searchNode->left;
		else searchNode = searchNode->right;
	}
	newNode->parent = prevNode;
	if(prevNode == 0){
		t->root = newNode;
		newNode->parent = newNode;
	}
	else if(t->comparator(newNode->value, prevNode->value) < 0)
		prevNode->left = newNode;
	else prevNode->right = newNode;
	t->size++;
	return newNode;
}//end insertBST

BSTNODE *findBST(BST *t, void *value){
	BSTNODE *searchNode = t->root;
	while(searchNode != 0 && t->comparator(value, searchNode->value) != 0){
		if(t->comparator(value, searchNode->value) < 0)
			searchNode = searchNode->left;
		else searchNode = searchNode->right;
	}
	return searchNode;
}//end findBST

BSTNODE *deleteBST(BST *t, void *value){
	BSTNODE *searchNode = findBST(t, value);
	if(searchNode == 0) return 0;
	BSTNODE *leaf = swapToLeafBST(t, searchNode);
	pruneLeafBST(t, leaf);
	return leaf;
}//end deleteBST

BSTNODE *swapToLeafBST(BST *t, BSTNODE *node){
	BSTNODE *searchNode = node;
	while(!isLeaf(searchNode)){
		BSTNODE *suc = successor(searchNode);
		if(suc != 0){
			t->swapper(suc, searchNode);
			searchNode = suc;
		}
		else{
			BSTNODE *pre = predecessor(searchNode);
			t->swapper(pre, searchNode);
			searchNode = pre;
		}
	}
	return searchNode;
}//end swapToLeafBST

void pruneLeafBST(BST *t, BSTNODE *leaf){
	if(leaf == t->root)
		t->root = 0;
	else if(leaf == leaf->parent->left)
		leaf->parent->left = 0;
	else
		leaf->parent->right = 0;
	t->size--;
}//end pruneLeafBST

int sizeBST(BST *t){
	return t->size;
}//end sizeBST

void statisticsBST(BST *t, FILE *fp){
	fprintf(fp, "Nodes: %d\n", t->size);
	if(t->root == 0){
        fprintf(fp, "Minimum depth: %d\n", -1);
        fprintf(fp, "Maximum depth: %d\n", -1);
	}
	else{
	fprintf(fp, "Minimum depth: %d\n", minDepth(t->root));
	fprintf(fp, "Maximum depth: %d\n", maxDepth(t->root));
	}
}//end statisticsBST

void displayBST(BST *t, FILE *fp){
	BSTNODE *root = t->root;
	fprintf(fp, "[");
	printPreOrder(root, t, fp);
}//end diplsayBST

void displayBSTdebug(BST *t, FILE *fp){
	if(t->root == 0) return;
	QUEUE *q = newQUEUE(t->display, t->free);
	enqueue(q, t->root);
	while(true){
		int nodeCount = sizeQUEUE(q);
		if(nodeCount == 0) break;
		while(nodeCount > 0){
			BSTNODE *node = dequeue(q);
			t->display(node->value, fp);
			if(nodeCount > 1) fprintf(fp, " ");
			if(node->left != 0) enqueue(q, node->left);
			if(node->right != 0) enqueue(q, node->right);
			nodeCount--;
		}
		fprintf(fp, "\n");
	}
}//end displayBSTdebug

void freeBST(BST *t){
	BSTNODE *root = t->root;
	freeBSTNodes(root, t);
	free(t);
}//end freeBST


// BEGIN STATIC METHODS

static void genericSwap(BSTNODE *a, BSTNODE *b){
	void *temp = a->value;
	a->value = b->value;
	b->value = temp;
}

static int minDepth(BSTNODE *n) {
	if (n == NULL) return 0;
	if (n->left == NULL && n->right == NULL) return 1;
	if (!n->left) return minDepth(n->right) + 1;
	if (!n->right) return minDepth(n->left) + 1;
	if(minDepth(n->left) < minDepth(n->right))
		return minDepth(n->left) + 1;
	else return minDepth(n->right) +1;
}

static int maxDepth(BSTNODE *n) {
	if (n == NULL) return 0;
	int l = maxDepth(n->left);
	int r = maxDepth(n->right);
	return l > r ? l+1 : r+1;
}

static bool isLeaf(BSTNODE *n) {
	return n->left == NULL && n->right == NULL;
}

static BSTNODE *successor(BSTNODE *n){
	BSTNODE *x = n;
	if (x->right != NULL) return treeMin(x->right);
	return 0;
}

static BSTNODE *predecessor(BSTNODE *n) {
	BSTNODE *x = n;
	if (x->left != NULL) return treeMax(x->left);
	return 0;
}

static BSTNODE *treeMin(BSTNODE *n) {
	BSTNODE *x = n;
	while (x->left != NULL) x = x->left;
	return x;
}

static BSTNODE *treeMax(BSTNODE *n) {
	BSTNODE *x = n;
	while (x->right != NULL) x = x->right;
	return x;
}

static void printPreOrder(BSTNODE *n, BST *t, FILE *fp){
	BSTNODE *x = n;
	if(t->root == 0){
		fprintf(stdout, "]");
		return;
	}
	if(x != 0){
		if(x != t->root)
			fprintf(fp, " [");
		t->display(x->value, fp);
		printPreOrder(x->left, t, fp);
		printPreOrder(x->right, t, fp);
		fprintf(fp, "]");
	}
}//end printPreOrder	

static void freeBSTNodes(BSTNODE *n, BST *t){
	if(n == 0)
		return;
	freeBSTNodes(n->left, t);
	freeBSTNodes(n->right, t);
	freeBSTNODE(n, t->free);
}//end freeBSTNodes

// END STATIC METHODS
