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

rb_tree *create_tree();
void insert_tree(rb_tree *tree, int key);
void pre_order(rb_tree *tree);

#endif
