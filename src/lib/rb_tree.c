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
  Node *new_node = (Node*) malloc(sizeof(Node));
  new_node->key = key;
  new_node->color = 'R';
  new_node->left = new_node->right = NULL;
  new_node->parent = NULL;
  return new_node;
}

void left_rotate(Node *root, Node *x, Node *t_nil) 
{
  Node *y = x->right;
  x->right = y->left;
  if (y->left != t_nil)
    y->left->parent = x;
  y->parent = x->parent;
  if (x->parent == t_nil) {
    root = y;
  } else if (x == x->parent->left) {
    x->parent->left = y;
  } else { 
    x->parent->right = y;
  }
  y->left = x;
  x->parent = y;
}

void rb_fixed_up(Node *root, Node *z, Node *t_nil)
{
  while (z->parent->color == 'R') {
    if (z->parent == z->parent->parent->left) {
      Node *y = z->parent->parent->right;
      if (y->color == 'R') {
        z->parent->color = 'B';
        y->color = 'B';
        z->parent->parent->color = 'R';
        z = z->parent->parent;
      } else if (z == z->parent->right) {
        z = z->parent;
        left_rotate(root, z, t_nil);
      }

    } else {
    //
    }
  }
  root->color = 'B';
}

Node *insert_rb_tree_rec(Node *root, Node *z, Node *t_nil)
{
  Node *y = t_nil; 
  Node *x = root;
  while (x != t_nil) { // Caminhamos na árvore até achar o lugar que o node z se encaixa
    y = x;
    if (z->key < x->key)
      x = x->left;
    else
      x = x->right;
  }
  z->parent = y; // Setando o pai de z como Y, para que haja sempre a propriedade de ligação dos filhos
  if (y == t_nil) { // se a raiz é vazia setamos root como z
    root = z;
  } else if (z->key < x->key) { // caso z precise ficar a esquerda da árvore
    y->left = z;
  } else { // caso z precise ficar a direita da árvore 
    y->right = z;
  }
  z->right = t_nil; // Setando os valores dos ponteiros left e right desse novo vertice para t_nil
  z->left = t_nil; // Setando os valores dos ponteiros left e right desse novo vertice para t_nil
  z->color = 'R'; // Vertices sempre estão na cor vermelha
  rb_insert_fixup(root, z, t_nil);
}
