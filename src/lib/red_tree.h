#ifndef RTREE
#define RTREE

typedef struct node
{
  struct node *left;
  struct node *right;
  struct node *parent;
  int key;
  char color;
} Node;

Node *create_node(int key);
Node *create_tnil();
void pre_order(Node *root, Node *tnil);
int tree_size(Node *root, Node *tnil);
void insert_tree(Node **root, Node *z, Node *tnil);

#endif
