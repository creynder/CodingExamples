//lifeboard.h
//Christopher Reynders

const int SIZE = 40;
const char BLANK = ' ';
const char ALIVE = 'X';
const char DEAD = ' ';

class Lifeboard{
	public:
		Lifeboard();
		~Lifeboard();
		void displayBoard();
		void addCell(int,int);
		void removeCell(int, int);
		void advance();
		bool checkSpace(int,int);
		bool inBound(int,int);
		void copyToTemp();
		void copyToMain();
		void applyRules();
	private:
		char tempboard[SIZE][SIZE];
		char mainboard[SIZE][SIZE];
};
