#pragma once
#include "functions.h"
#include "defines.h"

char** parse_input_string(char* raw_string, int str_len, int* num_of_parsed_symbols_out) {


	char* syntax_map;
	syntax_map = (char*)malloc(str_len - 1);
	for (int i = 0; i < str_len-1; i++) {
		char t = raw_string[i];
		
		if (t == 0x20) {
			syntax_map[i] = m_SPACE;													// ' ' - space 
		}
		else if (t == 0x2c || t == 0x2e) {
			syntax_map[i] = m_POINT;													// '.' or ',' - point
		}
		else if (t >= 0x21 && t <= 0x2f) {
			syntax_map[i] = m_OPERATOR;													// operators
		}
		else if (t == 0x3d) {
			syntax_map[i] = m_EQUALS;													// '=' - equals
		}
		else if (t >= 0x30 && t <= 0x39) {
			syntax_map[i] = m_DIGIT;													// digits
		}
		else if ((t >= 0x41 && t <= 0x5a) || (t >= 0x61 && t <= 0x7a)) {
			syntax_map[i] = m_LATIC_CHAR;												// latin characters 
		}
		else {
			syntax_map[i] = -1;															// unknown
			printf("Parsing Error: unknown symbol %d\n", t);
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
		if ((syntax_map[i] == m_OPERATOR && syntax_map[i - 1] == m_OPERATOR) || (syntax_map[i] == m_EQUALS && syntax_map[i - 1] == m_EQUALS)) { // split two operators
			symbols[symbol_pointer] = malloc(buffer_pointer);
			memcpy(symbols[symbol_pointer], buffer, buffer_pointer);
			symbols[symbol_pointer][buffer_pointer] = '\0';
			symbol_pointer++;
			memset(buffer, 0, MAX_SINGLE_TOKEN_LENGTH);
			buffer_pointer = 0;
		}
		else if (syntax_map[i] == m_POINT && syntax_map[i - 1] == m_POINT) {
			printf("Parsing Error: two points together\n");
			return -1;
		}
		else if (syntax_map[i] != syntax_map[i - 1] && (syntax_map[i] != m_POINT && syntax_map[i-1] != m_POINT)) { // points don't separate floats
			if (syntax_map[i] == m_LATIC_CHAR && syntax_map[i - 1] == m_DIGIT) { // number * variable (e.g. 5x => 5 * x)
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

 token* lexer(char** symbols, int symbol_num) {
	 token* token_array = malloc(sizeof( token) * symbol_num);
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
				printf("ERROR UNKNOWN SYMOBOL 0x%h\n", t);
				return -1;
				break;
			}
		}

	};

	return token_array;
}

//check if there's more or less than one '=' or parenthesis aren't closed
int check_syntax_errors( token* token_array, int token_num) {
	int equal_sym_num = 0,
		open_parenthesis_num = 0,
		close_parenthesis_num = 0;
	if (token_array[0] == t_EQUALS || token_array[token_num - 1] == t_EQUALS) {
		printf("Syntax Error: incorrect equation\n");
		return -1;
	}

	for (int i = 0; i < token_num; i++) {
		switch (token_array[i]){
		case t_EQUALS:
			equal_sym_num++;
			break;
		case t_PARENTHESE_OPEN:
			open_parenthesis_num++;
			break;
		case t_PARENTHESE_CLOSE:
			close_parenthesis_num++;
			break;
		default:
			break;
		}
	}
	if (equal_sym_num > 1) {
		printf("Syntax Error: more than one '='\n");
		return 1;
	}
	else if (open_parenthesis_num > close_parenthesis_num) {
		printf("Syntax Error: missing ')'\n");
		return 1;
	}
	else if (open_parenthesis_num < close_parenthesis_num) {
		printf("Syntax Error: unexpected ')'\n");
		return 1;
	}
	else if (equal_sym_num == 0) {
		printf("Syntax Error: no equal signs\n");
		return -1;
	}
	
	return 0;
}


