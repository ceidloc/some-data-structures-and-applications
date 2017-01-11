# make file for all c/c++ codes
# declaring variables
CC = g++
CFLAGS = -Wall -Werror -Wextra

avl: my_avl_tree_oop.cpp my_avl_tree_oop.hpp
	$(CC) $(CFLAGS) my_avl_tree_oop.cpp -o avl_interface.o
