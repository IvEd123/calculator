#pragma once
#ifndef HEADER
#define HEADER

enum tokens {
	t_VARIABLE,
	t_NUMBER,
	t_EQUALS, 
	t_PARENTHESE_OPEN,
	t_PARENTHESE_CLOSE, 
	t_ADDITION, 
	t_SUBSTRACTION, 
	t_MULIPLICATION, 
	t_DIVISION
};

enum operators {
	op_ADD,
	op_MULIPLY, 
	op_EQUALS
};

typedef struct variable {
	int id;
	char* name;
} variable;

static const enum operators op_priority[] = {
	op_EQUALS, 
	op_ADD, 
	op_MULIPLY
};

char** parse_input_string(char* raw_string, int str_len, int* num_of_parsed_symbols_out) {


	char* syntax_map = calloc(str_len-1);
	for (int i = 0; i < str_len-1; i++) {
		char t = raw_string[i];
		
		if (t == 0x20) {
			syntax_map[i] = 0;													// ' ' - space 
		}
		else if (t == 0x2c || t == 0x2e) {
			syntax_map[i] = 1;													// '.' or ',' - point
		}
		else if (t >= 0x21 && t <= 0x2f) {
			syntax_map[i] = 2;													// operators
		}
		else if (t == 0x3d) {
			syntax_map[i] = 3;													// '=' - equals
		}
		else if (t >= 0x30 && t <= 0x39) {
			syntax_map[i] = 4;													// digits
		}
		else if ((t >= 0x41 && t <= 0x5a) || (t >= 0x61 && t <= 0x7a)) {
			syntax_map[i] = 5;													// latin characters 
		}
		else {
			syntax_map[i] = -1;													// unknown
			printf("Error: unknown symbol %d", t);
			return -1;
		}
	}
	
#ifdef DEBUG
	printf("mapped string:\n");
	for (int i = 0; i < str_len-1; i++)
		printf("%d", syntax_map[i]);
	printf("\n");
#endif // DEBUG


	// devide string to separated symbols using spaces and syntax map

	char** symbols = malloc(sizeof(char*) * MAX_SYMBOL_SEQUENCE_LENGTH);// array of separated symbols
	int symbol_pointer = 0;

	char* buffer = malloc(MAX_SINGLE_TOKEN_LENGTH); // contains current string 
	int buffer_pointer = 0;	// pointer inside buffer
	
	buffer[0] = raw_string[0];
	buffer_pointer++;

	for (int i = 1; i < str_len; i++) {
		if (syntax_map[i] != syntax_map[i - 1] && (syntax_map[i] != 1 && syntax_map[i-1] != 1)) { // points don't separate floats
			if (syntax_map[i] == 5 && syntax_map[i - 1] == 4) { // number * variable (e.g. 5x => 5 * x)
				symbols[symbol_pointer] = malloc(buffer_pointer);
				memcpy(symbols[symbol_pointer], buffer, buffer_pointer);
				symbols[symbol_pointer][buffer_pointer] = '\0';
				symbol_pointer++;

				symbols[symbol_pointer] = malloc(2);
				symbols[symbol_pointer][0] = '*';
				symbols[symbol_pointer][1] = '\0';
				symbol_pointer++;

				memset(buffer, 0, MAX_SINGLE_TOKEN_LENGTH);
				buffer_pointer = 0;

			}
			else {
				if (buffer[0] != ' ') {
					symbols[symbol_pointer] = malloc(buffer_pointer);
					memcpy(symbols[symbol_pointer], buffer, buffer_pointer);
					symbols[symbol_pointer][buffer_pointer] = '\0';
					symbol_pointer++;
				}

				memset(buffer, 0, MAX_SINGLE_TOKEN_LENGTH);
				buffer_pointer = 0;
			}
		}
		buffer[buffer_pointer] = raw_string[i];
		buffer_pointer++;
	}

#ifdef DEBUG
	printf("separated symbols:\n");
	for (int i = 0; i < symbol_pointer; i++) {
		printf("%s\n", symbols[i]);
	}

#endif // DEBUG


	free(buffer);
	free(syntax_map);

	*num_of_parsed_symbols_out = symbol_pointer;
	return symbols;
}

enum tokens* lexer(char** symbols, int symbol_num) {
	enum tokens* token_array = malloc(sizeof(enum tokens) * symbol_num);
	for (int i = 0; i < symbol_num; i++) {
		char t = symbols[i][0];
		if (t >= 0x30 && t <= 0x39) {
		token_array[i] = t_NUMBER;
		}
		else if ((t >= 0x41 && t <= 0x5a) || (t >= 0x61 && t <= 0x7a)) {
			token_array[i] = t_VARIABLE;
		}
		else {
			switch (t){
			case '=':
				token_array[i] = t_EQUALS;
				for (int j = i+1; j < symbol_num; j++) { // check if there are more than one =
					if (symbols[i][0] == '=') {
						printf("Error: more than one '='\n");
						return -1;
					}
				}
				break;
			case '(':
				token_array[i] = t_PARENTHESE_OPEN;
				break;
			case ')':
				token_array[i] = t_PARENTHESE_CLOSE;
				break;
			case '+':
				token_array[i] = t_ADDITION;
				break;
			case '-':
				token_array[i] = t_SUBSTRACTION;
				break;
			case '*':
				token_array[i] = t_MULIPLICATION;
				break;
			case '/':
			case ':':
				token_array[i] = t_DIVISION;
				break;
			default:
				printf("ERROR UNKNOWN SYMOBOL %s\n", t);
				return -1;
				break;
			}
		}

	};

	return token_array;
}

/*node* build_tree() {
	node* root = malloc(sizeof(node));
	root->parent = NULL;
	

	return root;
}*/
#endif // !1