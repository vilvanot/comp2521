// COMP2521 21T2 Assignment 1
// tw.c ... compute top N most frequent words in file F
// Usage: ./tw [Nwords] File

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Dict.h"
#include "stemmer.h"
#include "WFreq.h"

#define MAXLINE 1000
#define MAXWORD 100

#define isWordChar(c) (isalnum(c) || (c) == '\'' || (c) == '-')

// add function prototypes for your own functions here

int main(int argc, char *argv[]) {
	int   nWords;    // number of top frequency words to show
	char *fileName;  // name of file containing book text

	// process command-line args
	switch (argc) {
		case 2:
			nWords = 10;
			fileName = argv[1];
			break;
		case 3:
			nWords = atoi(argv[1]);
			if (nWords < 10) nWords = 10;
			fileName = argv[2];
			break;
		default:
			fprintf(stderr,"Usage: %s [Nwords] File\n", argv[0]);
			exit(EXIT_FAILURE);
	}

	printf("nWords: %d, fileName: %s\n", nWords, fileName); // Delete this when you start
}

// add your own functions here

