#ifndef TREE_FUNCTIONS_H
#define TREE_FUNCTIONS_H


#include "tree.h"
#include "functions.h"

#include <stdlib.h>
#include <stdbool.h>

static const enum operators op_priority[] = {
	op_EQUALS,
	op_ADD,
	op_MULIPLY
};

static const int t_priority[] = {
	1000,	//t_VARIABLE,
	1000,	//t_NUMBER,
	0,		//t_EQUALS,
	2000,	//t_PARENTHESE_OPEN,
	2000,	//t_PARENTHESE_CLOSE,
	2,		//t_ADDITION,
	1,		//t_SUBSTRACTION,
	4,		//t_MULIPLICATION,
	3		//t_DIVISION
};

static void configure_node(node* _node, char symbol[], token token);

static node* create_node_from_break(token* token_array, char** symbols, int* priority_map, int length);

node* build_tree(token* token_array, char** symbols, int length);

static bool has_variables(node*);

float solve(node* root);

#endif // !TREE_FUNCTIONS_H