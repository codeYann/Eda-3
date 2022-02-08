#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./lib/red_tree.h"

const int TREES = 1000;
const int LIST_SIZE = 100000;
const int UPPER_BOUND = 10000;

int *create_list(int size)
{
  srand(time(NULL));
  int *list = malloc(sizeof(int) * size);
  for (int i = 0; i < size; i++) {
    list[i] = rand() % UPPER_BOUND;
  }
  return list;
}

int main(int argc, char **argv)
{
  int *list;
  Node *tnil = create_tnil();
  Node *root = tnil;

  for (int i = 0; i < TREES; i++) {
    list = create_list(LIST_SIZE);
    for (int j = 0; j < LIST_SIZE; j++) {
      insert_tree(&root, create_node(list[j]), tnil);
      if (tree_size(root, tnil) != 100000) {
        int diff = (LIST_SIZE - tree_size(root, tnil));
        int repeat = 100000;
        for (int k = 0; k < diff; k++) {
          repeat += 1;
          insert_tree(&root, create_node(repeat), tnil);
        }
      }
    }
    printf("Size of tree =>%d\n", tree_size(root, tnil));
    puts("Removing: ");

    for (int l = 0; l < 1000; l++) {
      remove_tree(&root, find(&root, list[l], tnil), tnil);
    }
    printf("Size of tree =>%d\n", tree_size(root, tnil));
    clean_nodes(&root, tnil);
  }
  return 0;
}
