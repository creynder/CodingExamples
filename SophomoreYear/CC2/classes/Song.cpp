/**********************************************
* File: Song.cpp
* Author: Christopher Reynders
* Email: creynder@nd.edu
* 
* This is the .cpp file for the Song class for CC2
* Contains the constructor and print methods
**********************************************/

#include "Song.h"

Song::Song(unsigned int songIDIn, std::string songArtistIn, std::string songTitleIn, std::string albumNameIn, unsigned int songYearIn) :
	songID(songIDIn), songArtist(songArtistIn), songTitle(songTitleIn),
	albumName(albumNameIn), songYear(songYearIn) {}

std::ostream& operator<<(std::ostream& out, const Song& print){
	
	out << "Song ID: " << print.songID << std::endl;
	out << "Artist Name: " << print.songArtist << std::endl;
	out << "Song Title: " << print.songTitle << std::endl;
	out << "Album Name: " << print.albumName << std::endl;
	out << "Release Year: " << print.songYear << std::endl;

	return out;
}
