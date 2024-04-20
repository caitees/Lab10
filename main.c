// Caitlin Wallsmith
// 4.19.24
// Lab 10
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// In this lab, you are going to implement a trie data structure to count the
// number of occurrences of a word if it exists in the dictionary. Words will
// always be in lowercase. Please modify the following code template:

// Trie structure
struct Trie
{
	int word_count; // if end = 1, this is a word, if end = 0, this is not a word
	struct Trie* next[26]; // 26 children
};

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
	if (pTrie == NULL) {
		return NULL;
	}

	for (int i = 0; i < 26; i++) {
		if (pTrie->next[i] != NULL) {
			deallocateTrie(pTrie->next[i]);
		}
	}

	free(pTrie);
	return NULL;
}

// Initializes a trie structure
struct Trie* createTrie()
{
	struct Trie* new = (struct Trie*)malloc(sizeof(struct Trie));
	for (int i = 0; i < 26; i++) {
		new->next[i] = NULL;
	}
	new->word_count = 0;
	return new;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word) {
	struct Trie* node = pTrie;
	for (int i = 0; word[i] != '\0'; i++) {
		int index = word[i] - 'a';
		if (node->next[index] == NULL) {
			node->next[index] = createTrie();
		}
		node = node->next[index];
	}
	node->word_count += 1;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word) {
	struct Trie* node = pTrie;
	for (int i = 0; word[i] != '\0'; i++) {
		int index = word[i] - 'a';
		if (node->next[index] == NULL) {
			return 0;
		}
		node = node->next[index];
	}
	return node->word_count;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords) {
	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Error opening file %s\n", filename);
		return 0;
	}

	int num_lines;
	fscanf(fp, "%d", &num_lines);

	for (int i = 0; i < num_lines; i++) {
		char word[100];
		fscanf(fp, "%s", word);
		pInWords[i] = strdup(word);
	}

	fclose(fp);
	return num_lines;
}

int main(void) {
	char *inWords[256]; // create an array of strings

	// read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i = 0; i < numWords; ++i) {
		printf("%s\n", inWords[i]);
	}

	struct Trie *pTrie = createTrie();

	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}

	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}
