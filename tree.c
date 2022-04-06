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
	delete_node(_node->m_child_left);
	delete_node(_node->m_child_right);
	free(_node->m_variable);
}


//delete node and move it's children to parent node
//example use cases are multiplying by 1 or addition 0
/*
		|				 |
		a			     a
		|				/ \
		b		->     c   d
	  /   \
	 c     d		               */
void remove_node(node* _node) {
	node* parent = _node->m_parent;

	node* children_left = _node->m_child_left;
	node* children_right = _node->m_child_right;
	free(_node);
		add_child_ptr(parent, children_left, nc_LEFT);
		add_child_ptr(parent, children_right, nc_RIGHT);
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