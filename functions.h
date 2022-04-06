#pragma once
#ifndef HEADER
#define HEADER
#include <stdlib.h>
#include <string.h>

typedef enum tokens {
	t_VARIABLE,
	t_NUMBER,
	t_EQUALS, 
	t_PARENTHESE_OPEN,
	t_PARENTHESE_CLOSE, 
	t_ADDITION, 
	t_SUBSTRACTION, 
	t_MULIPLICATION, 
	t_DIVISION
}token;


enum operators {
	op_SUBSTRACT,
	op_ADD,
	op_DEVIDE,
	op_MULIPLY, 
	op_EQUALS
};

typedef struct variable {
	int id;
	char* name;
} variable;



enum mapped {
	m_SPACE,
	m_POINT,
	m_OPERATOR,
	m_EQUALS,
	m_DIGIT,
	m_LATIC_CHAR,
	m_UNKNOWN
};

char** parse_input_string(char* raw_string, int str_len, int* num_of_parsed_symbols_out);

token* lexer(char** symbols, int symbol_num);

//check if there's more or less than one '=' or parenthesis aren't closed
int check_syntax_errors(token* token_array, int token_num);



#endif // !1