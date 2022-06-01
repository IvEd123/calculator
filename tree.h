#ifndef TREE_H
#define TREE_H

#include "functions.h"
#include "defines.h"
#include <stdio.h>

enum NODE_CHILD {
	nc_LEFT, 
	nc_RIGHT
};

enum NODE_TYPE {
	n_OPERATOR,
	n_NUMBER,
	n_VARIABLE
};

typedef struct node {
	enum NODE_TYPE m_type;
	struct node* m_child_left;
	struct node* m_child_right;
	struct node* m_parent;
	_Bool m_has_variable_bellow;
	union container{
		enum operators m_operator;
		float m_number;
		char m_variable;
	};
	
} node;

node* add_child(node* parent, enum NODE_TYPE type, enum NODE_CHILD child_dest);

node* add_child_ptr(node* parent, node* child, enum NODE_CHILD child_dest);

void delete_node(node* _node);

void replace_node(node* source_node, node* dst_node, enum NODE_CHILD dst_branch, enum NODE_CHILD source_branch);

void switch_children(node* _node);

void print_tree(node* _node);

#endif // !TREE_H