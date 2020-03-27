# G++ is for the GCC compiler for C++
PP := g++

# CFLAGS are the compiler flages for when we compile C code in this course 
FLAGS := -O0 -g -Wall -Wextra -Wconversion -Wshadow -pedantic -Werror -lm
CXXFLAGS := -m64 -std=c++11 -Weffc++ $(FLAGS) 



# Variables for Folders
CC2 := ~/DSInClass/CC2
CLASSES := $(CC2)/classes
PROG := $(CC2)/programs
OBJECTS := $(CC2)/objects
EXE := $(CC2)/executables



# Making the Playlist - CC2 Problem 1
# Command: make playlist
playlistObjs :=  $(OBJECTS)/playlist.o $(OBJECTS)/Song.o

playlist: $(playlistObjs) 
	$(PP) $(CXXFLAGS) -o $(EXE)/playlist $(playlistObjs)

$(OBJECTS)/playlist.o: $(PROG)/playlist.cpp $(CLASSES)/Song.h
	$(PP) $(CXXFLAGS) -c $(PROG)/playlist.cpp -o $@	

$(OBJECTS)/Song.o: $(CLASSES)/Song.cpp $(CLASSES)/Song.h
	$(PP) $(CXXFLAGS) -c $(CLASSES)/Song.cpp -o $@	
	
	
#Make all
all: playlist


# make test
test:
	make playlist
	$(EXE)/./playlist $(PROG)/playlist.txt


# Make clean
clean :
	rm -rf $(OBJECTS)/* $(EXE)/* 
