#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define DEBUG

#define MAX_STR_LENGTH 50
#define MAX_SYMBOL_SEQUENCE_LENGTH 250
#define MAX_SINGLE_TOKEN_LENGTH 5
#define MAX_NODE_CHILDREN 10

#include "tree.h"
#include "Header.h"

int main(int argc, char** argv) {

	char* raw_input = calloc(MAX_STR_LENGTH);

	printf("Enter expression: \n");

	fgets(raw_input, MAX_STR_LENGTH, stdin);

	int parsed_symbols;
	char** parsed_symbols_array;
	if ((parsed_symbols_array = parse_input_string(raw_input, strlen(raw_input), &parsed_symbols)) == -1)
		return -1;

	printf("----%d\n", sizeof(node));

	if (lexer(parsed_symbols_array, parsed_symbols) == -1)
		return -1;

	node root;


	return 0;
}
