#include "tree_functions.h"


static void configure_node(node* _node, char symbol[], token token) {
#ifdef DEBUG
	printf("%s\n", symbol);
#endif // DEBUG

	switch (token)	{
	case t_VARIABLE:
		_node->m_child_left = NULL;
		_node->m_child_right = NULL;
		_node->m_has_variable_bellow = 1;
		_node->m_type = n_VARIABLE;
		_node->m_variable = symbol;
		break;
	case t_NUMBER:
		_node->m_child_left = NULL;
		_node->m_child_right = NULL;
		_node->m_has_variable_bellow = 0;
		_node->m_type = n_NUMBER;
		_node->m_number = (float)atof(symbol);
		break;
	case t_ADDITION:
		_node->m_type = n_OPERATOR;
		_node->m_operator = op_ADD;
		break;
	case t_MULIPLICATION:
		_node->m_type = n_OPERATOR;
		_node->m_operator = op_MULIPLY;
		break;
	case t_SUBSTRACTION:
		_node->m_type = n_OPERATOR;
		_node->m_operator = op_SUBSTRACT;
		break;
	case t_DIVISION:
		_node->m_type = n_OPERATOR;
		_node->m_operator = op_DEVIDE;
		break;
	case t_EQUALS:
		_node->m_type = n_OPERATOR;
		_node->m_operator = op_EQUALS;
		break;
	default:
		break;
	}
}

static node* create_node_from_break(token* token_array, char** symbols, int* priority_map, int length) {
	node* _node = (node*)malloc(sizeof(node));
	_node->m_child_left = (node*)malloc(sizeof(node));
	_node->m_child_right = (node*)malloc(sizeof(node));

	if (token_array[0] == t_PARENTHESE_OPEN && token_array[length-1] == t_PARENTHESE_CLOSE) {
		token_array++;
		symbols++;
		priority_map++;
		length-=2;
	}

	if (length == 1) {
		configure_node(_node, *symbols, token_array[0]);
		return _node;
	}

	int max_priority = 1000;
	int id[MAX_NODE_CHILDREN];
	int children_num = 0;
	for (int i = 0; i < length; i++) {
		int cur_p = priority_map[i] + t_priority[token_array[i]];
		if (cur_p < max_priority) {
			memset(id, 0, MAX_NODE_CHILDREN);
			children_num = 0;
			id[children_num] = i;
			max_priority = cur_p;
			children_num++;
		}
		else if (cur_p == max_priority) {
			id[children_num] = i;
			children_num++;
		}
	}

	if (children_num > 0) {
		node* child_l = create_node_from_break(token_array, symbols, priority_map, id[children_num-1]);
		add_child_ptr(_node, child_l, nc_LEFT);
		child_l->m_parent = _node;
		
		node* child_r = create_node_from_break(token_array+ id[children_num-1]+1, symbols+id[children_num-1]+1, priority_map+ id[children_num-1]+1, length - id[children_num-1]-1);
		add_child_ptr(_node, child_r, nc_RIGHT);
		child_r->m_parent = _node;

		configure_node(_node, symbols[id[children_num-1]], token_array[id[children_num-1]]);

	}
	return _node;
}

node* build_tree(token* token_array, char** symbols, int length) {


	int* priority_map;
	priority_map = (int*)malloc(length * sizeof(int));
	memset(priority_map, 0, sizeof(int));
	int level = 0;
	int* mult_ops_array = malloc(length);
	int mult_ops_num = 0;
	
	// set higher priority for parenthesized expressions
	for (int i = 0; i < length; i++) {
		if (token_array[i] == t_PARENTHESE_OPEN) 
			level+=4;
		else if (token_array[i-1] == t_PARENTHESE_CLOSE)
			level-=4;
		priority_map[i] = level;
		if (token_array[i] == t_MULIPLICATION || token_array[i] == t_DIVISION) {
			mult_ops_array[mult_ops_num] = i;
			mult_ops_num++;
		}
	}
	
#ifdef DEBUG
	for (int i = 0; i < length; i++) 
		printf("%c", symbols[i][0]);
	printf("\n");
	for (int i = 0; i < length; i++) 
		printf("%d", priority_map[i]);
	printf("\n");
#endif // DEBUG

	node* node = create_node_from_break(token_array, symbols, priority_map, length);
	node->m_parent = NULL;
	has_variables(node);
	return node;
}

static bool has_variables(node* _node) {
	_Bool res = false;
	if (_node->m_type == n_OPERATOR) {
		_Bool left =  has_variables(_node->m_child_left);
		_Bool right =  has_variables(_node->m_child_right);
		res = left || right;
		if (left && right && (_node->m_operator == op_MULIPLY || _node->m_operator == op_DEVIDE)) {
			printf("Not a linear equation\n");
		}
	}
	else {
		if (_node->m_type == n_VARIABLE)
			res = true;
		else if (_node->m_type == n_NUMBER)
			res = false;
	}
	_node->m_has_variable_bellow = res;
	return res;
}

