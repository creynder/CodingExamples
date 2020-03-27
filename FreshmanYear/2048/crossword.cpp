//Christopher Reynders
//crossword.cpp

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;


#include "crossboard.h"

void sortByLength(vector<string>&);
void allCaps(vector<string>&);
bool checkForLetters(string);

int main(int argc, char *argv[]){
		cout << "Anagram Crossword Puzzle Generator" << endl;
		cout << "----------------------------------\n\n" << endl;
				
		vector<string> list;
		string newWord;

		if(argc == 1) {
			// create word list from user input
			cout << "Enter  a list of up to 20 words, with a maximum of 15 characters" << endl;
			cout << "Type a period '.' after the final word:" << endl;
			getline(cin, newWord);
			while(newWord[0] != '.'){
				if(list.size()==20){
					break;
				}
				if(checkForLetters(newWord)){
					list.push_back(newWord);
				}
				else{
					cout << newWord << " is not a valid input (contains non-alphabet numbers or is too long)" << endl;
				}
				
				getline(cin, newWord);
			}
		}
		if(argc==2 || argc==3) {
			// read data file and create list
			ifstream ifs;
			ifs.open(argv[1]);
			
			if(!ifs){
				cout << "\nInvalid file name";
				return 1;
			}
			
			// fill list from file
			while(ifs.peek() != '.'){
				if(list.size()==20){
					break;
				}
				getline(ifs, newWord, '\n');
				if(checkForLetters(newWord)){
					list.push_back(newWord);
				}
				else{
					cout << newWord << " is not a valid word (contains non-alphabet numbers or is too long)" << endl;
				}
			}
		}
		
		// create Board object
		Crossboard board;
		sortByLength(list);
		allCaps(list);
		
		// print words
		cout << "\nList of words: " << endl;
		for(int a=0; a<list.size(); a++){
			cout << list[a] << endl;
		}
		cout << endl;
		
		// place list on board
		board.createBoard(list);
		
		//print solution board
		cout << "SOLUTION: " << endl;
		board.printSolBoard();
		
		// print puzzle crossword
		cout << "\n\nPUZZLE: " << endl;
		board.printAnsBoard();
		
		// shuffle and display clues
		cout<<"\n\nCLUES: "<<endl;
		for(int s=0; s<list.size(); s++){
			random_shuffle(list[s].begin(), list[s].end());
		}
		
		for(int n=0; n<list.size(); n++){
			if(list[n][0] != ' '){
				cout << "\t" << setw(2) << right <<  board.getColumnLocation(n) << ", " << setw(2) << right << board.getRowLocation(n) << "|";
				cout << "\t" << setw(6) << right << board.getOrientation(n) << "|";
				cout << "\t" << setw(8) << left << list[n] << endl;
			}
		}
		
		if(argc==3){
			ofstream ofs;
			ofs.open(argv[2]);
			if(!ofs){
				cout << "Error: Could not open file '" << argv[2] << endl;
			}
			
			ofs << "SOLUTION: " << endl;
			// output solution board
			ofs << "-";
			for(int m=0;m<SIZE;m++)
			{
				ofs << "-";
			}
			ofs << "-" << endl;

			for(int i=0; i<SIZE; i++){
				ofs << "|";
				for(int j=0; j<SIZE; j++){
					if(board.getChar(i,j)==EMPTY)
					{
						ofs << FILLSPACESOL;
					}
					else
					{
						ofs << board.getChar(i,j);
					}
				}
				ofs << "|" << endl;
			}

			ofs << "-";
			for(int m=0;m<SIZE;m++)
			{
				ofs << "-";
			}
			ofs << "-" << endl;

			ofs << "\n\n" << endl;

			// output puzzle board
			
			ofs << "\n\nPUZZLE: " << endl;

			ofs << "-";
			for(int m=0;m<SIZE;m++)
			{
				ofs << "-";
			}
			ofs << "-" << endl;
			
			for(int i=0; i<SIZE; i++){
				ofs << "|";
				for(int j=0; j<SIZE; j++){
					if(board.getChar(i,j)==EMPTY) ofs << FILLSPACE;
					else ofs << EMPTY;
				}
				ofs << "|" << endl;
			}

			ofs << "-";
			for(int m=0;m<SIZE;m++)
			{
				ofs << "-";
			}
			ofs << "-" << endl;

			ofs << "\n\n" << endl;
			
			// output the anagram clues
			ofs << "CLUES:" << endl;
			for(int n=0; n<list.size(); n++){
				if(list[n][0] != ' '){
					ofs << "\t" << setw(2) << right << board.getColumnLocation(n) << ", " << setw(2) << right << board.getRowLocation(n) << "|";
					ofs << "\t" << setw(6) << right << board.getOrientation(n) << "|";
					ofs << "\t" << setw(8) << left << list[n] << endl;
				}
			}
			ofs.close();
		}
		
		return 0;
}
	
// sorts the list from longest to shortest words using bubble sort
void sortByLength(vector<string>& list){
	string temp;
	for(int i=0; i<list.size()-1; i++){
		for(int j=0; j<list.size()-i-1; j++){
			if(list[j].size() < list[j+1].size()){
				temp = list[j];
				list[j] = list[j+1];
				list[j+1] = temp;
			}
		}
	}
}

// makes all letters in the list capital
void allCaps(vector<string>& list){
	for(int i=0; i<list.size(); i++){
		for(int j=0; j<list[i].size(); j++){
			(list[i])[j] = toupper((list[i])[j]);
		}
	}
}

// returns true if all characters in the word are true, else false
bool checkForLetters(string word){
	if(word.size()>15 || word.size() == 1) return false;
	for(int i=0; i<word.size(); i++){
		if(word[i]<65 || word[i]>122 || (word[i]>90&&word[i]<97)){
			return false;
		}
	}
	return true;
}
