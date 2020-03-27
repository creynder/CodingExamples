# G++ is for the GCC compiler for C++
PP := g++

# CFLAGS are the compiler flages for when we compile C code in this course 
FLAGS := -O0 -g -Wall -Wextra -Wconversion -Wshadow -pedantic -Werror -lm
CXXFLAGS := -m64 -std=c++11 -Weffc++ $(FLAGS) 



# Variables for Folders
CC4 := ~/DSInClass/CC4
CLASSES := $(CC4)/classes
PROG := $(CC4)/programs
OBJECTS := $(CC4)/objects
EXE := $(CC4)/executables



# Rotations
# Command: make CC4
CC4Objs :=  $(OBJECTS)/CC4.o

CC4: $(CC4Objs) 
	$(PP) $(CXXFLAGS) -o $(EXE)/CC4 $(CC4Objs)
	$(EXE)/./CC4

$(OBJECTS)/CC4.o: $(PROG)/CC4.cpp  $(CLASSES)/BST.h
	$(PP) $(CXXFLAGS) -c $(PROG)/CC4.cpp -o $@	

	
	
#Make all
all: CC4


# Make clean
clean :
	rm -rf $(OBJECTS)/* $(EXE)/* 
