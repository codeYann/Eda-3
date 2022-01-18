#include "./rb_tree.h";
#include <stdio.h>
#include <stdlib.h>

#define INT_MAX 2147483647

Node *create_t_nil() 
{
  Node *t_nil = (Node*) malloc(sizeof(Node));
  t_nil->key = INT_MAX;
  t_nil->color = 'B';
  t_nil->left = t_nil->right = t_nil->parent = NULL;
  return t_nil;
}

Node *create_Node(int key)
{
  Node *new_node = (Node *) malloc(sizeof(Node));
  new_node->key = key;
  new_node->color = 'R';
  new_node->left = new_node->right = NULL;
  new_node->parent = NULL;
  return new_node;
}

Node *insert_rb_tree_rec(Node *root, Node *z, Node *t_nil)
{
  
}
