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

struct DictRep {
	// add fields to this struct
	// you can add whatever fields you want
};

// add function prototypes for your helper functions here

// Creates a new Dictionary
Dict DictNew(void) {
	return NULL;
}

// Frees the given Dictionary
void DictFree(Dict d) {

}

// Inserts an occurrence of the given word into the Dictionary
void DictInsert(Dict d, char *word) {

}

// Returns the occurrence count of the given word. Returns 0 if the word
// is not in the Dictionary.
int DictFind(Dict d, char *word) {
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
	return 0;
}

// Displays the given Dictionary. This is purely for debugging purposes,
// so  you  may  display the Dictionary in any format you want.  You may
// choose not to implement this.
void DictShow(Dict d) {

}

