#include <stdio.h>
#include <stdlib.h>
#include "./lib/red_tree.h"
#include <time.h>
#include <stdbool.h>

const int size = 100;

int *create_list(int size)
{
	int *list = malloc(sizeof(int) * size);
	for (int i = 0; i < size; i++)
	{
		list[i] = i + 2;
	}
	return list;
}

int main(int argc, char **argv)
{
	Node *tnil = create_tnil();
	Node *root = tnil;

	int *list = create_list(size);

	for (int i = 0; i < size; i++) {
		insert_tree(&root, create_node(list[i]), tnil);
	}
	printf("Size of root => %d\n", tree_size(root, tnil));
	pre_order(root, tnil);

	puts("\nRemoving values\n");
	for (int i = 0; i < 10; i++) {
		remove_tree(&root, find(&root, list[i], tnil), tnil);
	}

	printf("Size of root => %d\n", tree_size(root, tnil));
	pre_order(root, tnil);

	clean_nodes(&root, tnil);
	free(list);
	return 0;
}
