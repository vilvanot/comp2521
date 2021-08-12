// COMP2521 21T2 Assignment 1
// Dict.c ... implementation of the Dictionary ADT

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Dict.h"
#include "WFreq.h"

// you may define your own structs here
typedef struct node *Node;

struct node {
	WFreq data;
	Node left, right;
};

struct DictRep {
	Node root;
};

// add function prototypes for your helper functions here
void NodeFree(Node n);
static Node NodeCreate(char *word);
void NodeShow(Node n);
int NodeFind(Node n, char *word);

// Creates a new Dictionary
Dict DictNew(void) {
	Dict d = malloc(sizeof(Dict));
	if (d == NULL) {
		fprintf(stderr, "couldn't allocate dict\n");
		exit(EXIT_FAILURE);
	}

	d->root = NULL;

	return d;
}

// Frees the given Dictionary
void DictFree(Dict d) {
	Node n = d->root;
	NodeFree(n);
	free(d);
}

void NodeFree(Node n) {
	if (n != NULL) {
		NodeFree(n->left);
		NodeFree(n->right);
		free(n->data.word);
		free(n);
	}
}

// Inserts an occurrence of the given word into the Dictionary
void DictInsert(Dict d, char *word) {
	Node n = NULL;
	Node next = NULL;
	Node prev = NULL;

	if (d->root == NULL) {
		n = NodeCreate(word);
		d->root = n;
	} else {
		next = d->root;
		while (next != NULL) {
			prev = next;
			if (strcmp(word, next->data.word) < 0) {
				next = next->left;
			} else if (strcmp(word, next->data.word) > 0) {
				next = next->right;
			} else {
				next->data.freq++;
				return;
			}
		}
		n = NodeCreate(word);
		if (strcmp(word, prev->data.word) < 0) {
			prev->left = n;
		} else if (strcmp(word, prev->data.word) > 0) {
			prev->right = n;
		}
	}
}

static Node NodeCreate(char *word) {
	Node n = malloc(sizeof(*n));
	if (n == NULL) {
		fprintf(stderr, "couldn't allocate Node\n");
		exit(EXIT_FAILURE);
	}
	char *w = malloc(strlen(word) + 1);
	if (w == NULL) {
		fprintf(stderr, "couldn't allocate word\n");
		exit(EXIT_FAILURE);
	}
	strcpy(w, word);
	n->data.word = w;
	n->data.freq = 1;
	n->left = NULL;
	n->right = NULL;
	return n;
}

// Returns the occurrence count of the given word. Returns 0 if the word
// is not in the Dictionary.
int DictFind(Dict d, char *word) {
	Node n = d->root;

	return NodeFind(n, word);
}

int NodeFind(Node n, char *word) {
	if(n != NULL) {

		while(n && (strcmp(n->data.word, word) != 0) && n != NULL) {

			if(strcmp(word, n->data.word) > 0) {
				if(n->right == NULL) {
					return 0;
				}
				n = n->right;
			} else {
				if (n->left == NULL) {
					return 0;
				}
				n = n->left;
			}
		}
		return n->data.freq;
	}
	return 0;
}

// Finds  the top `n` frequently occurring words in the given Dictionary
// and stores them in the given  `wfs`  array  in  decreasing  order  of
// frequency,  and then in increasing lexicographic order for words with
// the same frequency. Returns the number of WFreq's stored in the given
// array (this will be min(`n`, #words in the Dictionary)) in  case  the
// Dictionary  does  not  contain enough words to fill the entire array.
// Assumes that the `wfs` array has size `n`.
int DictFindTopN(Dict d, WFreq *wfs, int n) {
	//int top[n] = {0};
	return 0;
}

// Displays the given Dictionary. This is purely for debugging purposes,
// so  you  may  display the Dictionary in any format you want.  You may
// choose not to implement this.
void DictShow(Dict d) {
	Node n = d->root;
	NodeShow(n);
}

void NodeShow(Node n) {
	if (n != NULL) {
		printf("%s(%d)\n", n->data.word, n->data.freq);
		NodeShow(n->left);
		NodeShow(n->right);
	}
}
