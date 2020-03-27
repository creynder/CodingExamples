# G++ is for the GCC compiler for C++
PP := g++

# CFLAGS are the compiler flages for when we compile C code in this course 
FLAGS := -O0 -g -Wall -Wextra -Wconversion -Wshadow -pedantic -Werror -lm
CXXFLAGS := -m64 -std=c++11 -Weffc++ $(FLAGS) 



# Variables for Folders
CC1 := ~/DSInClass/CC1



# Compiling the childSteps function - CC1 Problem 2
# Command: make childSteps
childStepsObjs :=  $(CC1)/childSteps.o

childSteps: $(childStepsObjs) 
	$(PP) $(CXXFLAGS) -o $(CC1)/childSteps $(childStepsObjs)

childSteps.o: $(CC1)/childSteps.cpp
	$(PP) $(CXXFLAGS) -c $(CC1)/childSteps.cpp	



# Make all
all: childSteps


# make test
test:
	make childSteps
	chmod +x test.sh
	./test.sh 
	


# Make clean
clean :
	rm -rf *.o childSteps
