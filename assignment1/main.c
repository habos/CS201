#include <stdlib.h>
#include <stdbool.h>
#include "integer.h"
#include "string.h"
#include "real.h"
#include "bst.h"
#include "scanner.h"
#include "options.h"
#include "stack.h"
#include "heap.h"


int main(int argc, char **argv){
	ConfigOpts *config = getOptions(argc, argv);
	if(config->vflag == 1){
		printf("My heapsort runs in n log n time because it takes log n time to extract each element and n time to build the heap.  Therefore the combined run time is n log n.\n");
		return 0;
	}
	getFilename(config, argc, argv);
	FILE *fp = 0;
	if(config->fname != 0){
		fp = fopen(config->fname, "r");
	}
	else return 0;
	HEAP *h = 0;
	void *value = 0;
	if(config->rflag == 1){
		if(config->dflag == 1)
			h = newHEAP(displayREAL, compareREALdecr, freeREAL);
		else
			h = newHEAP(displayREAL, compareREAL, freeREAL);
		value = newREAL(readReal(fp));
		while(!feof(fp)){
			insertHEAP(h, value);
			value = newREAL(readReal(fp));
		}
	}
	else if(config->sflag == 1){
                if(config->dflag == 1)
                        h = newHEAP(displaySTRING, compareSTRINGdecr, freeSTRING);
                else
                        h = newHEAP(displaySTRING, compareSTRING, freeSTRING);
		int isString = stringPending(fp);
		if(isString){
			value = newSTRING(readString(fp));
		}
		else{
			value = newSTRING(readToken(fp));
		}
		isString = stringPending(fp);
		while(!feof(fp)){
			insertHEAP(h, value);
			if(isString){
				value = newSTRING(readString(fp));
			}
			else{
				value = newSTRING(readToken(fp));
			}
			isString = stringPending(fp);
		}
		insertHEAP(h, value);	
	}

	else{
                if(config->dflag == 1)
                        h = newHEAP(displayINTEGER, compareINTEGERdecr, freeINTEGER);
                else
                        h = newHEAP(displayINTEGER, compareINTEGER, freeINTEGER);
		value = newINTEGER(readInt(fp));
		while(!feof(fp)){
			insertHEAP(h, value);
			value = newINTEGER(readInt(fp));
		}
	}
	buildHEAP(h);
	void *val = 0;
	while(sizeHEAP(h) > 0){
		val = extractHEAP(h);
		if(config->rflag)
			displayREAL(val, stdout);
		else if(config->sflag == 1)
			displaySTRING(val, stdout);
		else
			displayINTEGER(val, stdout);
		if(sizeHEAP(h) != 0)
			printf(" ");
		free(val);
	}
	printf("\n");
}






