/**********************************************
* File: playlist.cpp
* Author: Christopher Reynders
* Email: creynder@nd.edu
* 
* This file contains the main driver for CC2 Problem 1
* Problem, it will read in the text file, store the 
* file information into the Song class objects
* which are then pushed into a vector
**********************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "../classes/Song.h"

/********************************************
* Function Name  : getFileStream 
* Pre-conditions : argc, argv, ifs
* 
* Gets the file stream and attempts to open the text file  
********************************************/

void getFileStream(int argc, char** argv, std::ifstream& ifs){
	
	// Must be exactly two characters
	if(argc != 2){
		std::cout << "Incorrect number of inputs" << std::endl;
		exit(-1);
	}
	
	// Attempt to open the file
	ifs.open (argv[1], std::ifstream::in);
	
	if(!ifs.is_open()){
		std::cout << "Input File Name " << argv[1] << " does not exist\n";
		exit(-1);
	}
	
}

/********************************************
* Function Name  : main 
* Pre-conditions : argc, argv
* Post-conditions: 
*  
* Main driver of the playlist.cpp function
********************************************/

int main(int argc, char** argv){
	
	// Check the input 
	std::ifstream playListIn;
	getFileStream(argc, argv, playListIn);
	
	/***************************************
	 * Initialize an empty song playlist 
	 * using your selected Data Structure
	 * between here and the while loop 
	 ***************************************/
	std::vector< Song > Playlist;
	
	// Read in the playlist information 
	while( !playListIn.eof() ){
		
		// Boolean if all checks pass 
		bool checks = true;
		
		// Get the unsigned int from the file 
		std::string readStr;
		
		// First, get the songID 
		std::getline(playListIn, readStr);
		std::stringstream convert(readStr);
		
		// Get all the information for a song 
		unsigned int songID;
		if( !(convert >> songID) ){
			checks = false;
		}
		
		// Use getline for the entire artist's Name 
		std::string artistName;
		std::getline(playListIn, artistName);
		
		// Use getline for the entire song title 
		std::string songTitle;
		std::getline(playListIn, songTitle);
		
		// Use getline for the entire Album Name 
		std::string albumName;
		std::getline(playListIn, albumName);
		
		// First, get the Year 
		std::getline(playListIn, readStr);
		std::stringstream convert2(readStr);
		unsigned int year;
		if( !(convert2 >> year) ){
			checks = false;
		}
		
		// If all checks pass 
		if(checks == true){
			
			/***********************
			* You have everything you need to insert 
			* into a Song class object. You just need 
			* to create the object and insert into the 
			* Data Structure of your choice
			***********************/
			Song newSong(songID, artistName, songTitle, albumName, year);
			Playlist.push_back(newSong);

		}
		
	}
	
	/***********************
	* Now that the playlist is created 
	* print all the objects in the Data Structure
	***********************/
	for(Song& theSong : Playlist){
		std::cout << theSong;
	}

	return 0;
}
