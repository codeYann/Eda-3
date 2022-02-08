CC = gcc 
SOURCE_DIR = src
SOURCE_C = $(wildcard $(SOURCE_DIR)/lib/*.c)


RB_TREE_TEST:
	$(CC) $(SOURCE_DIR)/index.c $(SOURCE_C) -o $(SOURCE_DIR)/rb_test
	./src/rb_test
	rm $(SOURCE_DIR)/rb_test


RB_TREE_RESULTS:
	$(CC) $(SOURCE_DIR)/results.c $(SOURCE_C) -o $(SOURCE_DIR)/results
	./src/results
	rm $(SOURCE_DIR)/results