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

Node *create_t_nil();
Node *create_node(int key);
void insert_tree(Node **root, int key, Node **t_nil);
void in_order(Node *root, Node *t_nil);
#endif
