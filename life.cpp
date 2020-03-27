//life.cpp
//Christopher Reynders

#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
using namespace std;

#include "lifeboard.h"

int main(int argc, char *argv[])
{
	if(argc == 1)
	{
		//run menu with user choice
		Lifeboard board;
		bool done = false;
		bool infiniteLoop = false;
		char userChoice;
		int xcoor;
		int ycoor;	
		
		board.displayBoard();
		while(done == false)
		{
			cout << "a: add coordinate" << endl;
			cout << "r: remove coordinate" << endl;
			cout << "n: advance one step" << endl;
			cout << "q: quit program" << endl;
			cout << "p: play forever" << endl;
			cout << "Enter your choice: " << endl;
			cin >> userChoice;
			switch(userChoice)
			{
				case('a'):
				{
					cout << "Enter add cell coordinates: " << endl;
					cin >> xcoor;
					cin >> ycoor;
					board.addCell(xcoor,ycoor);
					board.displayBoard();
					break;
				}
				case('r'):
				{
					cout << "Enter remove cell coordinates: " << endl;
					cin >> xcoor;
					cin >> ycoor;
					board.removeCell(xcoor,ycoor);
					board.displayBoard();
					break;
				}
				case('n'):
				{
					//advance the simulation one step
					board.advance();
					break;
				}
				case('q'):
				{
					//quit the program
					done = true;
					break;
				}
				case('p'):
				{
					//play game forever
					while(infiniteLoop == false)
					{
						usleep(50000);
						board.advance();
					}
					break;
				}
				default:
				{
					cout << "Invalid Input" << endl;
					break;
				}
			}
		}

	}
	else if(argc == 2)
	{
		//run batch version
		//take file name from argv[] and run commands
		Lifeboard boardbatch;
		ifstream ifs;

		ifs.open(argv[1]);
		if(!ifs){
			cout << "Error opening file" << endl;
			return 1;
		}
		else
		{
		int xcoor1;
		int ycoor1;
		char choice;
		bool infiniteLoop2 = false;
		while(ifs.peek() != EOF)
		{
			ifs >> choice;
			switch(choice)
			{
				case('a'):
				{
					ifs >> xcoor1;
					ifs >> ycoor1;
					boardbatch.addCell(xcoor1,ycoor1);
					boardbatch.displayBoard();
					break;
				}
				case('r'):
				{
					ifs >> xcoor1;
					ifs >> ycoor1;
					boardbatch.removeCell(xcoor1,ycoor1);
					boardbatch.displayBoard();
					break;
				}
				case('p'):
				{
					while(infiniteLoop2 == false)
					{
						usleep(50000);
						boardbatch.advance();
					}
					break;
				}
				default:
				{
					break;
				}
			}
		}
		}


	}
	else
	{
		cout << "Invalid Arguments" << endl;
	}

	return 0;
}
