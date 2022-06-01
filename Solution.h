#ifndef SOLUTION_H
#define SOLUTION_H

#include "defines.h"
#include "tree.h"
#include "tree_functions.h"

float solve(node* root);

static int solve_consts(node* _node);

static int calculate_node(node* _node);

static void find_x(node* root);

static void operate_node(enum operators op, node* right_node, node* num_node);

static void solve_node_with_variables(node* _node);
#endif // SOLUTION_H