#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "defines.h"

#include "tree.h"
#include "functions.h"
#include "tree_functions.h"


int main(int argc, char** argv) {

	char* raw_input = (char*)malloc(MAX_STR_LENGTH);

	printf("Enter expression: \n");

	fgets(raw_input, MAX_STR_LENGTH, stdin);

	int parsed_symbols_num;
	char** parsed_symbols_array;
	token* token_array;

	if ((parsed_symbols_array = parse_input_string(raw_input, strlen(raw_input), &parsed_symbols_num)) == -1)
		return -1;

	if ((token_array = lexer(parsed_symbols_array, parsed_symbols_num)) == -1)
		return -1;

	int error_code = check_syntax_errors(token_array, parsed_symbols_num);
	if (error_code != 0)
		return -1;


	node* root = build_tree(token_array, parsed_symbols_array, parsed_symbols_num);

	float result = solve(root);

	printf("Result: %f", result);

	return 0;
}
