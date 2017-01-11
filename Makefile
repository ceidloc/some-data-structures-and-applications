# make file for all c/c++ codes
# declaring variables
# c compiler
CC = g++
# flags
CFLAGS = -Wall -Werror -Wextra
# standard
CSTD = -std=c++11
# alt -std=c++0x

# to create interface for avl tree header
avl: my_avl_tree_oop.cpp my_avl_tree_oop.hpp
	$(CC) $(CSTD) $(CFLAGS) my_avl_tree_oop.cpp -o avl_interface.o

# for interview question 1, finding unique using procedural
find_unique: find_unique_from_array_procedural.cpp 
	$(CC) $(CSTD) $(CFLAGS) find_unique_from_array_procedural.cpp -o find_unique_procedural.o

# alternate for q1, using avl tree header
f_u_oop: find_unique_oop.cpp  my_avl_tree_oop.hpp
	$(CC) $(CSTD) $(CFLAGS) find_unique_oop.cpp -o find_unique_oop.o

# to delete all object/executable files and a.out
clean:
	rm -rf *o *exe a.out

# to show o or cpp files
so:
	ls *o

sc:
	ls *cpp
