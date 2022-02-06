#include "./lib/rb_tree.h"
#include <stdio.h>

int main(int argc, char **argv) 
{

  Node *t_nil = create_t_nil();
  Node *root = t_nil;

  insert_tree(&root, 80, &t_nil);
  insert_tree(&root, 90, &t_nil);
  insert_tree(&root, 100, &t_nil);
  in_order(root, t_nil);
  return 0;
}

