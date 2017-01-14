# makefile for all c/c++ codes
# declaring variables
# c compiler
CC = g++
# flags
# add -g to create symbol tables for .o file
CFLAGS = -Wall -Werror -Wextra
# standard
CSTD = -std=c++11
# alt -std=c++0x

# to create all
all: avl rbt find_unique find_unique_oop qu cqu cqb cdll
	echo "all object files created!"

# to create interface for avl tree header
avl: avl_tree_oop_interface.cpp my_avl_tree_oop.hpp
	$(CC) $(CSTD) $(CFLAGS) avl_tree_oop_interface.cpp -o avl_tree_oop_interface.o

# to create interface for red black tree header
rbt: my_red_black_tree_oop.hpp rbt_oop_interface.cpp
	$(CC) $(CSTD) $(CFLAGS) rbt_oop_interface.cpp -o rbt_oop_interface.o

# for interview question 1, finding unique using procedural
find_unique: find_unique_from_array_procedural.cpp 
	$(CC) $(CSTD) $(CFLAGS) find_unique_from_array_procedural.cpp -o find_unique_procedural.o

# alternate for q1, using avl tree header
find_unique_oop: find_unique_oop.cpp  my_avl_tree_oop.hpp
	$(CC) $(CSTD) $(CFLAGS) find_unique_oop.cpp -o find_unique_oop.o

# for datastructure question 1, unbounded queue
qu: queue_unbounded.cpp
	$(CC) $(CSTD) $(CFLAGS) queue_unbounded.cpp -o queue_unbounded.o

cqu: circular_queue_unbounded.cpp
	$(CC) $(CSTD) $(CFLAGS) circular_queue_unbounded.cpp -o circular_queue_unbounded.o

cqb: circular_queue_bounded.cpp
	$(CC) $(CSTD) $(CFLAGS) circular_queue_bounded.cpp -o circular_queue_bounded.o

cdll: circular_doubly_linked_list.cpp
	$(CC) $(CSTD) $(CFLAGS) circular_doubly_linked_list.cpp -o circular_doubly_linked_list.o

# to delete all object/executable files and a.out
clean:
	rm -rf *o *exe a.out

# to show o, cpp or hpp files
so:
	ls *o

sc:
	ls *cpp

sh:
	ls *hpp
