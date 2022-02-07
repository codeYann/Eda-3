#include "./red_tree.h"
#include <stdio.h>
#include <stdlib.h>

const int max_int = 2147483647;

Node *create_node(int key)
{
  Node *node = (Node*) malloc(sizeof(Node));
  node->color = 'R';
  node->key = key;
  node->left = NULL;
  node->right = NULL;
  node->parent = NULL;
  return node;
}

Node *create_tnil()
{
  Node *tnil = (Node*) malloc(sizeof(Node));
  tnil->color = 'B';
  tnil->left = NULL;
  tnil->right = NULL;
  tnil->parent = NULL;
  tnil->key = max_int;
}

void tree_size_rec(Node *root, Node *tnil, int *size)
{
  (*size) += 1;
  if (root->left != tnil) {
    tree_size_rec(root->left, tnil, size);
  }
  if (root->right != tnil) {
    tree_size_rec(root->right, tnil, size);
  }
}

int tree_size(Node *root, Node *tnil) 
{
  int size = 0;
  tree_size_rec(root, tnil, &size);
  return size;
}

void pre_order(Node *root, Node *tnil)
{
  printf("Key: %03d, color: %c\n", root->key, root->color);
  if (root->left != tnil) {
    pre_order(root->left, tnil);
  }
  if (root->right != tnil) {
    pre_order(root->right, tnil);
  }
}

void left_rotate(Node **root, Node *z, Node *tnil)
{
  Node *y = z->right;
  z->right = y->left;

  if (z->right != tnil) {
    z->right->parent = y;
  }
  y->parent = z->parent;

  if (z->parent == tnil) {
    (*root) = y;
  } else if (z == z->parent->left) {
    z->parent->left = y;
  } else {
    z->parent->right = y;
  }
  y->left = z;
  z->parent = y;
}

void right_rotate(Node **root, Node *z, Node *tnil) {
 
  Node *y = z->left;
  z->left = y->right;

  if (z->left != tnil){
    z->left->parent = z;
  }

  y->parent = z->parent;

  if (z->parent == tnil) {
    (*root) = y;
  } else if (z == z->parent->left) {
    z->parent->left = y;
  } else {
    z->parent->right = y;
  }

  y->right = z;
  z->parent = y;
}

void red_black_fixed(Node **root, Node *z, Node *tnil)
{
  while (z->parent->color == 'R') {
    if (z->parent == z->parent->parent->left) {
      Node *uncle = z->parent->parent->right;
      if (uncle->color == 'R') {
        z->parent->color = uncle->color = 'B';
        z->parent->parent->color = 'R';
        z = z->parent->parent;
      } else {
        if (z == z->parent->right) {
          z = z->parent;
          left_rotate(root, z, tnil);
        }
        z->parent->color = 'B';
        z->parent->parent->color = 'R';
        right_rotate(root, z->parent->parent, tnil);
      }
    } else {
      Node *uncle = z->parent->parent->left;
      if (uncle->color == 'R') {
        z->parent->color = uncle->color = 'B';
        z->parent->parent->color = 'R';
        z = z->parent->parent;
      } else {
        if (z == z->parent->left) {
          z = z->parent;
          right_rotate(root, z, tnil);
        }
        z->parent->color = 'B';
        z->parent->parent->color = 'R';
        left_rotate(root, z->parent->parent, tnil);
      }
    }
  }
  (*root)->color = 'B';
}

void insert_tree(Node **root, Node *z, Node *tnil)
{
  Node *temp = (*root);
  Node *y = tnil;

  while (temp != tnil) {
    y = temp;
    if (z->key == temp->key) {
      printf("Key already exists\n");
      y = NULL;
      temp = tnil;
    } else if (z->key < temp->key) {
      temp = temp->left;
    } else {
      temp = temp->right;
    }
  }

  if (y != NULL) {
    z->parent = y;
    if (y == tnil) {
      (*root) = z;
    } else if (z->key < y->key) {
      y->left = z;
    } else {
      y->right = z;
    }
    z->left = z->right = tnil;
    z->color = 'R';
    red_black_fixed(root, z, tnil);
  }
}
