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
void insertWords(char *line, Dict sw, Dict bk);
void normaliseWords(char *word);
void rmNonAlphaNum(char *line);

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
	// Open book and stopwords files
	FILE *book = fopen(fileName, "r");
	if (book == NULL) {
		fprintf(stderr, "Can't open %s\n", fileName);
		exit(EXIT_FAILURE);
	}

	FILE *stopwords = fopen("stopwords", "r");
	if (stopwords == NULL) {
        fprintf(stderr, "Can't open stopwords\n");
        exit(EXIT_FAILURE);
	}

	// Create dictionary for book and stopwords
	Dict sw = DictNew();
	Dict bk = DictNew();
	char line[MAXLINE];
	char word[MAXWORD];
	char start[38] = "START OF THIS PROJECT GUTENBERG EBOOK";
	char end[36] = "END OF THIS PROJECT GUTENBERG EBOOK";
	int gutenberg = -1;

	// insert stopwords into dictionary
	// stopwords contains newline character which needs to be removed
	// one word per line
	while (fgets(word, MAXWORD, stopwords) != NULL) {
		strtok(word, "\n");
		DictInsert(sw, word);
		//printf("Line: %s", word);
	}
	fclose(stopwords);

	while (fgets(line, MAXLINE, book) != NULL) {
		if (gutenberg == 0) {
			if (strstr(line, end)) {
				gutenberg = 1;
				break;
			}
			insertWords(line, sw, bk);
		} else if (strstr(line, start)) {
			gutenberg = 0;
		}
	}
	fclose(book);

	if (gutenberg != 1) {
		fprintf(stderr, "Not a Project Gutenberg book\n");
		exit(EXIT_FAILURE);
	}
	DictShow(bk);
}

// add your own functions here
void insertWords(char *line, Dict sw, Dict bk) {
	char deliminators[34] = " \n\t!\"#$%%&()*+,./:;<=>?@[\\]^_`{|}~";
	char *token;

	token = strtok(line, deliminators);

	while (token != NULL) {
		if  (strlen(token) > 1) {
			rmNonAlphaNum(token);
			normaliseWords(token);
			if (DictFind(sw, token) == 0) {
				stem(token, 0, strlen(token) - 1);
				DictInsert(bk, token);
			}
		}
		token = strtok(NULL, deliminators);
	}
}

void normaliseWords(char *word) {
	for (int i = 0; word[i]; i++) {
		word[i] = tolower(word[i]);
	}
}

void rmNonAlphaNum(char *line) {
	char *dst = line;
    while(*line) {
        if (isalnum(*line) || ispunct(*line)) {
            *dst++ = *line;
        }
        line++;
    }
	*dst = '\0';
}
