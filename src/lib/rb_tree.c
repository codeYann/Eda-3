#include "./rb_tree.h"
#include <stdio.h>
#include <stdlib.h>

const int INT_MAX = 2147483647;

Node *create_node(int key)
{
  Node *new_node = (Node*) malloc(sizeof(Node));
  new_node->key = key;
  new_node->color = 'R';
  new_node->left = new_node->right = NULL;
  new_node->parent = NULL;
  return new_node;
}

Node *create_t_nil()
{
  Node *t_nil = (Node*) malloc(sizeof(Node));
  t_nil->key = INT_MAX;
  t_nil->color = 'B';
  t_nil->left = t_nil->right = t_nil->parent = NULL;
  return t_nil;
}

void left_rotate(Node ***root, Node *x, Node ***t_nil)
{
  printf("Entrei");
  Node *y = x->right;
  x->right = y->left;
  printf("chave:%d", y->key);
  printf("chave:%d", x->key);
  // if (x->right != (**t_nil))
  //   x->right->parent = x;
  // y->parent = x->parent;
  // if (x->parent == (**t_nil)) {
  //   (**root) = y;
  // } else if (x == x->parent->left) {
  //   x->parent->left = y;
  // } else {
  //   x->parent->right = y;
  // }
  // y->left = x;
  // x->parent = y;
}

void right_rotate(Node ***root, Node *x, Node ***t_nil)
{
  printf("Entrei");
  Node *y = x->left;
  x->left = y->right;
  if (x->left != (**t_nil))
    x->left->parent = x;
  y->parent = x->parent;
  if (x->parent == (**t_nil)) {
    (**root) = y;
  } else if (x == x->parent->left) {
    x->parent->left = y;
  } else {
    x->parent->right = y;
  }
  y->right = x;
  x->parent = y;
}

void rb_insert_fixedup(Node ***root, Node **z, Node ***t_nil)
{
  while ((*z)->parent->color == 'R') {
    if ((*z)->parent == (*z)->parent->parent->left) {
      printf("Entrei1");
      Node *y = (*z)->parent->parent->right;
      if (y->color == 'R') {
        (*z)->parent->color = y->color = 'B';
        (*z)->parent->parent->color = 'R';
        (*z) = (*z)->parent->parent;
      } else {
        if ((*z) = (*z)->parent->right) {
          (*z) = (*z)->parent;
          left_rotate(root, *z, t_nil);
        }
        (*z)->parent->color = 'B';
        (*z)->parent->parent->color = 'R';
        right_rotate(root, ((*z)->parent->parent), t_nil);
      }
    } else {
      Node *y = (*z)->parent->parent->left;
      if (y->color == 'R') {
        (*z)->parent->color = 'B';
        y->color = 'B';
        (*z)->parent->parent->color = 'R';
        (*z) = (*z)->parent->parent;
      } else {
        printf("Entrei2");
        if ((*z) = (*z)->parent->left) {
          (*z) = (*z)->parent;
          right_rotate(root, *z, t_nil);
        }
        (*z)->parent->color = 'B';
        (*z)->parent->parent->color = 'R';
        left_rotate(root, ((*z)->parent->parent), t_nil);
      }
    }
  }
  (**root)->color = 'B';
}

void insert_rec(Node ***root, Node **z, Node ***t_nil)
{
  Node *y = (**t_nil);
  Node *temp = (**root);
  while (temp != (**t_nil)) {
    y = temp;
    if ((*z)->key == temp->key) {
      printf("Valor já encontrado");
      y = NULL;
      temp = (**t_nil);
    } else if ((*z)->key < temp->key) {
      temp = temp->left;
    } else {
      temp = temp->right;
    }
  }

  if (y != NULL) {
    (*z)->parent = y;
    if (y == (**t_nil)) {
      (**root) = (*z);
    } else {
      if ((*z)->key < y->key) {
        y->left = (*z);
      } else {
        y->right = (*z);
      }
    }
    (*z)->right = (*z)->left = (**t_nil);
    (*z)->color = 'R';
    rb_insert_fixedup(root, z, t_nil);
  }
}

void insert_tree(Node **root, int key, Node **t_nil) 
{
  Node* z = create_node(key);
  insert_rec(&root, &z, &t_nil);
}

void in_order(Node *root, Node *t_nil) {
  printf("key: %d, color: %c\n", root->key, root->color);
  if (root->left != t_nil) {
    in_order(root->left, t_nil);
  }
  if (root->right != t_nil) {
    in_order(root->right, t_nil);
  }
}

