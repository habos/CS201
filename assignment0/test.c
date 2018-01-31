#include <stdio.h>
#include <stdlib.h>
#include "sll.h"
#include "integer.h"
#include "dll.h"
#include "queue.h"
#include "stack.h" 

static void showItems(SLL *items){
       printf("The items are ");
       displaySLL(items,stdout);
       printf(".\n");
       printf("The items (debugged) are ");
       displaySLLdebug(items,stdout);
       printf(".\n");
}

int main(void){
	SLL *items = newSLL(displayINTEGER,freeINTEGER);
	showItems(items);
	insertSLL(items,0,newINTEGER(3));
	showItems(items);                //insert at front
	insertSLL(items,sizeSLL(items),newINTEGER(2));
	showItems(items); 	 //insert at back
	insertSLL(items,1,newINTEGER(1)); 
	insertSLL(items, sizeSLL(items), newINTEGER(5));
	insertSLL(items, 2, newINTEGER(9));
	insertSLL(items, 0, newINTEGER(89));          //insert at middle
 	showItems(items);
 	printf("The value ");
	INTEGER *i = removeSLL(items,0);                   //remove from front
	displayINTEGER(i,stdout);
 	printf(" was removed.\n");
	freeINTEGER(i);
	printf("The value ");
        INTEGER *j = removeSLL(items,3);                   //remove from front
        displayINTEGER(j,stdout);
        printf(" was removed.\n");
        freeINTEGER(j);
	printf("The value ");
        INTEGER *k = removeSLL(items,sizeSLL(items)-1);                   //remove from front
        displayINTEGER(k,stdout);
        printf(" was removed.\n");
        freeINTEGER(k);
	showItems(items);
	int x = getINTEGER((INTEGER *) getSLL(items,0));    //get the first item
	printf("The first item is %d.\n",x);
	printf("Freeing the list.\n");
	freeSLL(items);
	return 0;
}
