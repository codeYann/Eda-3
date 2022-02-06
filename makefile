CC = gcc 
SOURCE_DIR = src
SOURCE_C = $(wildcard $(SOURCE_DIR)/lib/*.c)


RB_TREE_TEST:
	$(CC) $(SOURCE_DIR)/rb_tree_test.c $(SOURCE_C) -o $(SOURCE_DIR)/rb_test
	./src/rb_test
	rm $(SOURCE_DIR)/rb_test
