#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include "options.h"
#include "scanner.h"

ConfigOpts *getOptions(int argc, char **argv){
	ConfigOpts *config = (ConfigOpts*)malloc(sizeof(ConfigOpts));
	config->vflag = config->rflag = config->sflag = config->dflag = 0;
	config->fname = 0;
	int num;
	while((num = getopt(argc, argv, "vrsd")) != -1) {
		switch(num){
			case 'v':
				config->vflag = 1;
				break;
			case 'r':
				config->rflag = 1;
				break;
			case 'p':
				config->sflag = 1;
				break;
			case 'd':
				config->dflag = 1;
				break;
		}
	}
	config->optind = optind;
	return config;
}

void getFilename(ConfigOpts *config, int argc, char **argv) {
	if (config->optind == argc) {
		printf("Error: No filename supplied.\n");
		exit(1);
	}
	int len = strlen(argv[config->optind]) + 1;
	config->fname = (char *)malloc(len * sizeof(char));
	strcpy(config->fname, argv[config->optind]);
}
