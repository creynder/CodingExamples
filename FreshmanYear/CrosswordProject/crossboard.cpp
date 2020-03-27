#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "crossboard.h"

Crossboard::Crossboard(){
// make a 15x15 blank board
	for(int i=0; i<SIZE; i++){
		for(int j=0; j<SIZE; j++){
			answerKey[i][j] = EMPTY;
			}
	}

	for(int k=0; k<20; k++){
		for(int l=0; l<2; l++){
			wordLocations[k][l] = 0;
		}
	}

	// order tracks which word is placed when, start at 1
	order = 1;

	// orientation tracks whether a word is an across or down clue
	for(int i=0; i<20; i++){
		orientation[i] = " ";
	}
}

Crossboard::~Crossboard() {}

// printSolBoard displays the solution board
void Crossboard::printSolBoard(){
	cout << "-";
 	for(int m = 0;m < SIZE;m++)
	{
		cout << "-";
	}
	cout << "-" << endl;

	for(int i=0; i<SIZE; i++){
		cout << "|";
		for(int j=0; j<SIZE; j++){
            if(answerKey[i][j]==EMPTY)
            {
	            cout << FILLSPACESOL;
            }
            else
            {
				cout << answerKey[i][j];
            }
   		}
		cout << "|" << endl;
	}

	cout << "-";
 	for(int n = 0;n < SIZE;n++)
	{
		cout << "-";
	}
	cout << "-" << endl;

}

// printAnsBoard method prints the puzzle
void Crossboard::printAnsBoard(){
	cout << "-";
	for(int m = 0; m < SIZE; m++)
	{
		cout << "-";
	}
	cout << "-" << endl;

	for(int i=0; i<SIZE; i++){
		cout << "|";
		for(int j=0; j<SIZE; j++){
			if(answerKey[i][j]== EMPTY){
				cout << FILLSPACE;
            }
   			else 
	        {
			    cout << EMPTY;
			}
		}
		cout << "|" <<  endl;
	}

	for(int n = 0; n < SIZE; n++)
	{
		cout << "-";
	}
	cout << "-" << endl;

}
	
// setChar puts one letter on the board
void Crossboard::setChar(char c, int row, int col) {
	answerKey[row][col] = c;
}

// getRowLocation returns the row at which a word was placed
int Crossboard::getRowLocation(int x){
	return wordLocations[x][0]+1;
	// add 1 so the coordinates go from 1-15
}

// getColumnLocation returns the column at which a word was placed
int Crossboard::getColumnLocation(int y){
	return wordLocations[y][1]+1;
	// add 1 so the coordinates go from 1-15
}

// placeList places list of words from main on the board
void Crossboard::createBoard(vector<string>& list){
	for(int i=0; i<list.size(); i++){
		if(i==0){
			for(int j=0; j<list[0].size(); j++){
				// place first (longest) word in middle, horizontally
				setChar((list[0])[j], 7, (SIZE-list[0].size())/2 + j);
				orientation[0] = "ACROSS";
			}
			wordLocations[0][0] = 7;
			wordLocations[0][1] = (SIZE-list[0].size())/2;
			}
			// alternate placing words vertically and horizontally
			// if doesn't fit, move to next option
			if(i!=0 && i%2==0){
				if(placeNextVert(list[i])){
					orientation[i] = "DOWN";
					}
				else if(placeNextHor(list[i])){
					orientation[i] = "ACROSS";
					}
				else{
					cout << list[i] << " could not be placed" << endl;
					list[i] = " ";
					order++;
					orientation[i] = " ";
					}
			}
			else if(i!=0 && i%2!=0){
				if(placeNextHor(list[i])){
					orientation[i] = "ACROSS";
					}
				else if(placeNextVert(list[i])){
					orientation[i] = "DOWN";
					}
				else{
					cout << list[i] << " could not be placed" << endl;
					list[i] = " ";
					order++;
					orientation[i] = " ";
					}
			}
		}
}

//returns the character at a specific location on the board
char Crossboard::getChar(int i, int j) {
	return answerKey[i][j];
}

//returns the orientation of a specified word
string Crossboard::getOrientation(int x){
	return orientation[x];
}

// placeNextVert tries to find and place next word on board vertically

bool Crossboard::placeNextVert(string word){
	int match = 0;
	bool placed = false;
	bool key = false;
		for(int j=0; j<SIZE; j++){
			for(int i=0; i<SIZE+1-word.size(); i++){
				for(int k=0; k<word.size(); k++){
					if(getChar(i+k,j)==EMPTY || getChar(i+k,j)==word[k]){
						match++;
						}
					if(getChar(i+k,j)==word[k]){
						if(getChar(i+k+1,j)==EMPTY && getChar(i+k-1,j)==EMPTY){
							match = match+2;
							key = true;
							}
					}
					if(getChar(i+k,j+1)==EMPTY && getChar(i+k,j-1)==EMPTY){
						match = match + 2;
					}
					if(getChar(i-1,j)==EMPTY && getChar((i+word.size()),j)==EMPTY){
						if(k==0) match = match + 2;
					}
				}
				if(match == 3*word.size()+2 && key == 1 && placed == false){
					// place word
					for(int p=0; p<word.size(); p++){
						setChar(word[p], i+p, j);
						}
					placed = true;
					// assign coordinates to the newly-placed word
					wordLocations[order][0] = i;
					wordLocations[order][1] = j;
					order++;
					return 1;
				}
				match = 0;
				key = false;
			}
		}
	return false;
}

// placeNextHor method tries to find and place next word on board horizontally
bool Crossboard::placeNextHor(string word){
	int match = 0;
	bool placed = 0;
	bool key = 0;
	for(int j=0; j<SIZE; j++){
		for(int i=0; i<SIZE+1-word.size(); i++){
			for(int k=0; k<word.size(); k++){
				if(getChar(j,i+k)==EMPTY || getChar(j,i+k)==word[k]){
					match++;
				}
				if(getChar(j,i+k)==word[k]){
					if(getChar(j,i+k+1)==EMPTY && getChar(j,i+k-1)==EMPTY){
						match = match+2;
						key = true;
					}
				}
				if(getChar(j+1,i+k)==EMPTY && getChar(j-1,i+k)==EMPTY){
					match = match + 2;
				}
				if(getChar(j,i-1)==EMPTY && getChar(j,i+word.size())==EMPTY){
					if(k==0) match = match + 2;
				}
			}
			if(match == 3*word.size()+2 && key == 1 && placed == false){
				// place word
				for(int p=0; p<word.size(); p++){
					setChar(word[p], j,i+p);
				}
				wordLocations[order][0] = j;
				wordLocations[order][1] = i;
				order++;
				
				placed = true;
				return 1;
			}
			match = 0;
			key = false;
		}
	} 
	return false;
	// return false if the word was not able to be placed horizontally
} 

// findMatch returns 1 if at least 1 letter from the word
int Crossboard::findMatch(string word){
	for(int i=0; i<SIZE; i++){
		for(int j=0; j<SIZE; j++){
			for(int k=0; k<word.size(); k++){
				if(word[k] == getChar(i,j))
				{
					return 1;
				}
			}
		}
	}
	return 0;
}
