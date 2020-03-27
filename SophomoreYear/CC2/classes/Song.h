/**********************************************
* File: Song.h
* Author: Christopher Reynders
* Email: creynder@nd.edu
*
* This is the .h file for the Song Class
**********************************************/

#ifndef SONG_H
#define SONG_H

#include <string>
#include <iostream>

class Song{
	
	private:
		unsigned int songID;
		std::string songArtist;
		std::string songTitle;
		std::string albumName;
		unsigned int songYear;
	
	public:

		Song(unsigned int songIDIn, std::string songArtistIn, std::string songTitleIn, std::string albumNameIn, unsigned int songYearIn);

		friend std::ostream& operator<<(std::ostream& out, const Song& print);

};

#endif
