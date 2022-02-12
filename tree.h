#ifndef TREE_H
#define TREE_H

#include "Header.h"

enum NODE_TYPE {
	n_OPERATOR,
	n_NUMBER,
	n_VARIABLE
};

typedef struct  {
	enum NODE_TYPE type;
	struct node** children;
	struct node* parent;
	int children_num;
	union container{
		enum operators op;
		float number;
		variable* var;
	};
	
} node;

node* add_child(node* parent, enum NODE_TYPE type) {
	node* child =  malloc(sizeof(node));
	parent->children[parent->children_num] = child;
	child->type = type;
	parent->children_num++;
	child->parent = parent;

	return child;
}

//delete node and all children
void delete_node(node* _node) {
	for (int i = 0; i < _node->children_num; i++)
		delete_node(_node->children[i]);
	free(_node->var);
	free(_node->children);
}

//delete node and move it's children to parent node
//example use cases are multiplying by 1 or addition 0
/*
		|				 |
		a			     a
		|				/ \
		b		->     c   d
      /    \		
	  c    d		
*/

void remove_node(node* _node) {
	node* parent = _node->parent;

}

#endif // !TREE_H