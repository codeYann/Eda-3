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

Node *find(Node **root, int key, Node *tnil)
{
  if ((*root) != tnil) {
    Node *temp = (*root);
    Node *pointer = tnil;
    pointer->key = -1;

    while (temp != tnil) {
      if (temp->key == key) {
        pointer = temp;
        temp = tnil;
      } else if (key < temp->key) {
        temp = temp->left;
      } else {
        temp = temp->right;
      }
    }
    return pointer;
  }
}

void left_rotate(Node **root, Node *z, Node *tnil)
{
  Node *y = z->right;
  z->right = y->left;

  if (y->left != tnil) {
    y->left->parent = z;
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

  if (y->right != tnil){
    y->right->parent = z;
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

void insert_fixedup(Node **root, Node *z, Node *tnil)
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
      // printf("Key already exists\n");
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
    insert_fixedup(root, z, tnil);
  }
}

void move_parent(Node **root, Node *tnil, Node *u, Node *v)
{
  if (u->parent == tnil) {
    (*root) = v;
  } else {
    if (u == u->parent->left)
      u->parent->left = v;
    else
      u->parent->right = v;
  }
  v->parent = u->parent;
}

Node *successor(Node *z, Node *tnil) {
  Node *temp = z;
  while (temp->left != tnil) {
    temp = temp->left;
  }
  return temp;
}

void remove_fixed(Node **root, Node *x, Node *tnil)
{
  while (x != (*root) && x->color != 'R') {
    if (x == x->parent->left) {
      Node *w = x->parent->right;
      if (w->color == 'R') {
        w->color = 'B';
        x->parent->color = 'R';
        left_rotate(root, x->parent, tnil);
        w = x->parent->right;
      }
      if (w->left->color == 'B' && w->right->color == 'B') {
        w->color = 'R';
        x = x->parent;
      } else {
        if (w->right->color == 'B') {
          w->left->color = 'B';
          w->color = 'R';
          right_rotate(root, w, tnil);
          w = x->parent->right;
        }
        w->color = x->parent->color;
        x->parent->color = 'B';
        w->right->color = 'B';
        left_rotate(root, x->parent, tnil);
        x = (*root);
      }
    } else {
      Node *w = x->parent->left;
      if (w->color == 'R') {
        x->parent->color = 'R';
        w->color = 'B';
        right_rotate(root, x->parent, tnil);
        w = x->parent->left;
      }
      if (w->right->color == 'B' && w->left->color == 'B') {
        w->color = 'R';
        x = x->parent;
      } else {
        if (w->left->color == 'B') {
          w->right->color = 'B';
          w->color = 'R';
          left_rotate(root, w, tnil);
          w = x->parent->left;
        }
        w->color = x->parent->color;
        x->parent->color = 'B';
        w->left->color = 'B';
        right_rotate(root, x->parent, tnil);
        x = (*root);
      }
    }
  }
  x->color = 'B';
}

void remove_tree(Node **root, Node *z, Node *tnil)
{
  Node *y = z;
  Node *x;
  char first_color = y->color;
  if (y->left == tnil) {
    x = z->right;
    move_parent(root, tnil, z, z->right);
  } else {
    if (y->right == tnil) {
      x = z->left;
      move_parent(root, tnil, z, z->left);
    } else {
      y = successor(z, tnil);
      first_color = y->color;
      x = y->right;
      if (y->parent == z) {
        move_parent(root, tnil, y, x);
        y->right = z->right;
        y->parent->right = y;
      }
      move_parent(root, tnil, z, y);
      y->left = z->left;
      y->left->parent = y;
    }
  }
  if (first_color == 'B')
    remove_fixed(root, x, tnil);
}

void clean_nodes_rec(Node *root, Node *tnil) 
{
  if (root->left != tnil) {
    clean_nodes_rec(root->left, tnil);
  }
  if (root->right != tnil) {
    clean_nodes_rec(root->right, tnil);
  }
  free(root);
}

void clean_nodes(Node **root, Node *tnil) 
{
  clean_nodes_rec((*root), tnil);
  (*root) = tnil;
}