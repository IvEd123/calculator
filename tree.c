#include "tree.h"

node* add_child(node* parent, enum NODE_TYPE type, enum NODE_CHILD child_dest) {
	node* child = malloc(sizeof(node));
	if (child_dest == nc_LEFT)
		parent->m_child_left = child;
	else
		parent->m_child_right = child;
	child->m_type = type;
	child->m_parent = parent;

	return child;
}

node* add_child_ptr(node* parent, node* child, enum NODE_CHILD child_dest) {
	if (child_dest == nc_LEFT)
		parent->m_child_left = child;
	else
		parent->m_child_right = child;

	return child;
}


//delete node and all children
void delete_node(node* _node) {
	if (_node == NULL)
		return;
	delete_node(_node->m_child_left);
	delete_node(_node->m_child_right);
}


//delete node and move it's children to parent node
//example use cases are multiplying by 1 or addition 0

/*	replace -a- by -b- and delete -a- and -e-
*		   x			 x
		   |		     |
		   a			 b
		 /	\			/ \
		b	 e	->     c   d
	  /   \
	 c     d		               */
void replace_node(node* source_node, node* dst_node, enum NODE_CHILD dst_branch, enum NODE_CHILD source_branch) {

	node* dst_parent = dst_node->m_parent;
	node* removed_branch = source_branch == nc_LEFT ? dst_node->m_child_right : dst_node->m_child_left;

	source_node->m_parent = dst_parent;
	if (dst_branch == nc_LEFT)
		dst_parent->m_child_left = source_node;
	else
		dst_parent->m_child_right = source_node;

	//delete_node(removed_branch);
	//delete_node(dst_node);
	

}

/*
		|			|
		a			a
	  /   \	->	   / \
	  b   c		  c   b

*/

void switch_children(node* _node) {
	node* child_l = _node->m_child_left;
	node* child_r = _node->m_child_right;

	_node->m_child_left = child_r;
	_node->m_child_right = child_l;
}

void print_tree(node* _node) {
	switch (_node->m_type){
	case n_OPERATOR:
		printf("(");
		print_tree(_node->m_child_left);
		switch (_node->m_operator){
		case op_SUBSTRACT:
			printf("-");
			break;
		case op_ADD:
			printf("+");
			break;
		case op_DEVIDE:
			printf(":");
			break;
		case op_MULIPLY:
			printf("*");
			break;
		case op_EQUALS:
			printf("=");
			break;
		default:
			break;
		}
		print_tree(_node->m_child_right);
		printf(")");
		break;
	case n_NUMBER:
		printf("%f", _node->m_number);
		break;
	case n_VARIABLE:
		printf("x");
		break;
	default:
		break;
	}
}