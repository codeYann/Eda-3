#include "./lib/rb_tree.h"
#include <stdio.h>

int main(int argc, char **argv) 
{

  rb_tree* tree = create_tree();
  insert_tree(tree, 10);
  pre_order(tree);
  return 0;
}

