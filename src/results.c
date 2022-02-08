#include <stdio.h>
#include <stdlib.h>
#include "./lib/red_tree.h"
#include <time.h>
#include <stdbool.h>

int black_height_traversal(Node *aux, Node *tnil) {
	if(aux == tnil)
		return 1;

	int left_height = black_height_traversal(aux->left, tnil),
	    right_height = black_height_traversal(aux->right, tnil);

	if(left_height != right_height || left_height == -1)
		return -1;
	else
		return left_height + (aux->color == 'B'? 1 : 0);
}

int get_black_height(Node *aux, Node *tnil) {
	if(aux == tnil)
		return 1;

	int left_height = black_height_traversal(aux->left, tnil),
	    right_height = black_height_traversal(aux->right, tnil);

	if(left_height != right_height || left_height == -1)
		return -1;
	else
		return left_height;
}

bool is_red_black_tree(Node *aux, Node *tnil) {
	if(aux == tnil)
		return true;

	if(get_black_height(aux, tnil) != -1)
		if(is_red_black_tree(aux->left, tnil))
			return is_red_black_tree(aux->right, tnil);

	return false;
}

int main(int argc, char **argv) 
{
  Node *tnil = create_tnil();
  Node *root = tnil;
  srand(time(NULL));
  for (int i = 0; i < 20; i++) {
    int key = rand() % 2557;
    printf("Key => %d\n",  key);
    insert_tree(&root, create_node(key), tnil);
  }

  printf("Size of root => %d\n", tree_size(root, tnil));
  printf("Is tree a red black? => %d\n", is_red_black_tree(root, tnil));
  pre_order(root, tnil);
  

  return 0;
}
