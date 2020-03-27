//Christopher Reynders
//crossboard.h
#include <vector>
#include <string>
using namespace std;
const int SIZE = 15;
const char FILLSPACE = '#';
const char FILLSPACESOL = '.';
const char EMPTY = ' ';

class Crossboard{
	public:
	    Crossboard(); //frame box and fill with empty spaces
        ~Crossboard();
        char getChar(int,int);
        int getRowLocation(int);
        int getColumnLocation(int);
        string getOrientation(int);
        void updateBoard();
        void setChar(char,int,int);
        void createBoard(vector<string>&);
    	bool placeNextVert(string);
	    bool placeNextHor(string);
		int findMatch(string);
		void printSolBoard();
		void printAnsBoard();
	private:
		char answerKey[SIZE][SIZE];
		int wordLocations[20][2];
		string orientation[20];
		int order;
};
