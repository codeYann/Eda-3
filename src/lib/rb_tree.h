#ifndef RB_TREE
#define RB_TREE

typedef struct node
{
  int key;
  char color;
  struct node *left;
  struct node *right;
  struct node *parent;
} Node;

typedef struct
{
  Node *node;
} Rb_tree;

void Insert(Rb_tree *tree, int key);

#endif
