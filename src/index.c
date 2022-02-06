#include <stdio.h>
#include "./lib/red_tree.h"

int main(int argc, char **argv)
{
  Node *tnil = create_tnil();
  Node *root = tnil;

  

  insert_tree(&root, create_node(38), tnil);
  insert_tree(&root, create_node(44), tnil);
  insert_tree(&root, create_node(66), tnil);
  insert_tree(&root, create_node(51), tnil);
  insert_tree(&root, create_node(17), tnil);
  insert_tree(&root, create_node(3), tnil);
  insert_tree(&root, create_node(22), tnil);
  insert_tree(&root, create_node(25), tnil);

  pre_order(root, tnil);
  return 0;
}
