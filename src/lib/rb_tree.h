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
  Node *root;
  Node *t_nil;
} rb_tree;

void Insert(rb_tree *tree, int key);

#endif
