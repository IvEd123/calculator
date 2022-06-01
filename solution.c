#include "Solution.h"

float solve(node* root) {
	float res = 0;

	int has_consts;
	do {
#ifdef DEBUG
	print_tree(root);
	printf("\n");
#endif // DEBUG
		has_consts = solve_consts(root);
	} while (has_consts);


	find_x(root);
	res = root->m_child_right->m_number;

	return res;
}

int solve_consts(node* _node){
	if (_node->m_type == n_OPERATOR) {
		int res = 0;	//returns 1 if found consts
		if (_node->m_child_left == NULL || _node->m_child_right == NULL) {
			printf("ERROR NODE PTR NULL\n");
			return 0;
		}
		if (_node->m_child_left->m_type == n_NUMBER
			&& _node->m_child_right->m_type == n_NUMBER) {
			res = calculate_node(_node);
		}
		else {
			if (_node->m_child_left->m_type == n_OPERATOR)
				res |= solve_consts(_node->m_child_left);

			if (_node->m_child_right->m_type == n_OPERATOR)
				res |= solve_consts(_node->m_child_right);
		}

		return res;
	}
}

int calculate_node(node* _node){
	float l_num = _node->m_child_left->m_number;
	float r_num = _node->m_child_right->m_number;
	float res = 0;

#ifdef DEBUG
	char op = 0;
	printf("%f ", l_num);
#endif // DEBUG


	switch (_node->m_operator){
	case op_SUBSTRACT:
		res = l_num - r_num;
#ifdef DEBUG
		op = '-';
#endif // DEBUG
		break;
	case op_ADD:
		res = l_num + r_num;
#ifdef DEBUG
		op = '+';
#endif // DEBUG
		break;
	case op_DEVIDE:
		res = l_num / r_num;
#ifdef DEBUG
		op = ':';
#endif // DEBUG
		break;
	case op_MULIPLY:
		res = l_num * r_num;
#ifdef DEBUG
		op = '*';
#endif // DEBUG
		break;
	default:
		break;
	}

#ifdef DEBUG
	printf("%c %f = %f\n ", op, r_num, res);
#endif // DEBUG
	
	delete_node(_node->m_child_left);
	delete_node(_node->m_child_right);
	_node->m_child_left = NULL;
	_node->m_child_right = NULL;
	_node->m_number = res;
	_node->m_type = n_NUMBER;

	return 1;
}

void find_x(node* _node) {
	if (_node->m_child_left->m_has_variable_bellow && _node->m_child_right->m_has_variable_bellow) {
		solve_node_with_variables(_node);
		return;
	}

	if (!_node->m_child_left->m_has_variable_bellow) 
		switch_children(_node);	//now we sure that variable is in l_value

	node** left_branch_ptr = &_node->m_child_left;
	node** right_branch_ptr = &_node->m_child_right;

	while ((*left_branch_ptr)->m_type != n_VARIABLE) {
		if (!(*left_branch_ptr)->m_child_left->m_has_variable_bellow)
			switch_children(*left_branch_ptr);		//variable is always in left branch
		
		operate_node((*left_branch_ptr)->m_operator, *right_branch_ptr, (*left_branch_ptr)->m_child_right);
		replace_node( (*left_branch_ptr)->m_child_left , *left_branch_ptr, nc_LEFT, nc_LEFT);
	}

}

void operate_node(enum operators op, node* right_node, node* num_node){
	switch (op)
	{
	case op_SUBSTRACT:
		right_node->m_number += num_node->m_number;
		break;
	case op_ADD:
		right_node->m_number -= num_node->m_number;
		break;
	case op_DEVIDE:
		right_node->m_number *= num_node->m_number;
		break;
	case op_MULIPLY:
		right_node->m_number /= num_node->m_number;
		break;
	default:
		break;
	}
}

void solve_node_with_variables(node* _node) {
	if (_node->m_type == n_OPERATOR && (_node->m_operator == op_MULIPLY || _node->m_operator == op_DEVIDE)) {
		
		return;
	}
}