//lifeboard.cpp
//Christopher Reynders

#include <iostream>
#include <cstdlib>
using namespace std;

#include "lifeboard.h"

Lifeboard::Lifeboard()
{
	for(int i = 0; i < SIZE; i++)
	{
		for(int j = 0; j < SIZE; j++)
		{
			mainboard[i][j] = BLANK;
		}
	}

	copyToTemp();
}

Lifeboard::~Lifeboard()
{
}

void Lifeboard::displayBoard()
{
	system("clear");
	cout << "-";
	for(int m = 0; m < SIZE; m++)
	{
		cout << "-";
	}
	cout << "-" << endl;

	for(int i = 0; i < SIZE; i++)
	{
		cout << "|";
		for(int j = 0; j < SIZE; j++)
		{
			cout << mainboard[i][j];
		}
		cout << "|" << endl;
	}

	cout << "-";
	for(int n = 0; n < SIZE; n++)
	{
		cout << "-";
	}
	cout << "-" << endl;
}

void Lifeboard::addCell(int x, int y)
{
	if(inBound(x,y)== true)
	{
		//copyToTemp();
		
		if(checkSpace(x,y) == true)
		{
			mainboard[x][y] = ALIVE;
		}
		
		//copyToMain();
	}
}
void Lifeboard::removeCell(int x, int y)
{
	if(inBound(x,y) == true)
	{
		//copyToTemp();
		if(checkSpace(x,y) == false)
		{
			mainboard[x][y] = DEAD;
		}
		//copyToMain();
	}
}

void Lifeboard::advance()
{
	//copyToTemp();
	applyRules();
	//copyToMain();
	displayBoard();
}

bool Lifeboard::checkSpace(int x, int y)
{
	//check space if empty, if not return false, if dead or blank return true
	if(mainboard[x][y] == ALIVE)
	{
		return false;
	}
	else if(mainboard[x][y] == DEAD || tempboard[x][y] == BLANK)
	{
		return true;
	}
}

bool Lifeboard::inBound(int x, int y)
{
	//check if referenced point is inbounds
	if((x>=0 && x < SIZE) && (y>=0 && y<SIZE))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Lifeboard::copyToMain()
{
	for(int i = 0; i < SIZE; i++)
	{
		for(int j = 0; j < SIZE; j++)
		{
			mainboard[i][j] = tempboard[i][j];
		}
	}
}

void Lifeboard::copyToTemp()
{
	for(int i = 0; i < SIZE; i++)
	{
		for(int j=0; j < SIZE; j++)
		{
			tempboard[i][j] = mainboard[i][j];
		}
	}
}

void Lifeboard::applyRules()
{
	//apply the rules of the game
	//dead cell with exactly three neighbors becomes live
	//only live cell with 2 or 3 neighbors survive
	//all other live cells die
	//neighbors are in 8 directions
	//different set of rules for borders and inner spaces and corners
	
	copyToTemp();
	int neighborCount;
	for(int i = 0; i < SIZE; i++)
	{
		for(int j = 0; j < SIZE; j++)
		{
			if(i == 0 && j == 0) //top left corner
			{
				neighborCount = 0;
				if(mainboard[i][j+1] == ALIVE)
				{
					neighborCount++;
				}
				if(mainboard[i+1][j] == ALIVE)
				{
					neighborCount++;
				}
				if(mainboard[i+1][j+1] == ALIVE)
				{
					neighborCount++;
				}
			}
			else if(i == SIZE-1 && j == 0) // bottom left corner
			{
				neighborCount = 0;
				if(mainboard[i-1][j] == ALIVE)
				{
					neighborCount++;
				}
				if(mainboard[i][j+1] == ALIVE)
				{
					neighborCount++;
				}
				if(mainboard[i-1][j+1] == ALIVE)
				{
					neighborCount++;
				}
				
			}
			else if(i == 0 && j == SIZE-1) // top right corner
			{
				neighborCount = 0;
				if(mainboard[i+1][j] == ALIVE)
				{
					neighborCount++;
				}
				if(mainboard[i][j-1] == ALIVE)
				{
					neighborCount++;
				}
				if(mainboard[i+1][j-1] == ALIVE)
				{
					neighborCount++;
				}
			}
			else if(i == SIZE-1 && j == SIZE-1) // bottom right corner
			{
				neighborCount = 0;
				if(mainboard[i-1][j] == ALIVE)
				{
					neighborCount++;
				}
				if(mainboard[i][j-1] == ALIVE)
				{
					neighborCount++;
				}
				if(mainboard[i-1][j-1] == ALIVE)
				{
					neighborCount++;
				}
			}
			else if(i == 0) //top border
			{
				neighborCount = 0;
				if(mainboard[i][j-1] == ALIVE)
				{
					neighborCount++;
				}
				if(mainboard[i][j+1] == ALIVE)
				{
					neighborCount++;
				}
				if(mainboard[i+1][j-1] == ALIVE)
				{
					neighborCount++;
				}
				if(mainboard[i+1][j+1] == ALIVE)
				{
					neighborCount++;
				}
				if(mainboard[i+1][j] == ALIVE)
				{
					neighborCount++;
				}
			}
			else if(j == 0) //left border
			{
				neighborCount = 0;
				if(mainboard[i-1][j] == ALIVE)
				{
					neighborCount++;
				}
				if(mainboard[i-1][j+1] == ALIVE)
				{
					neighborCount++;
				}
				if(mainboard[i][j+1] == ALIVE)
				{
					neighborCount++;
				}
				if(mainboard[i+1][j] == ALIVE)
				{
					neighborCount++;
				}
				if(mainboard[i+1][j+1] == ALIVE)
				{
					neighborCount++;
				}
			}
			else if(i == SIZE-1) //bottom border
			{
				neighborCount = 0;
				if(mainboard[i][j-1] == ALIVE)
				{
					neighborCount++;
				}
				if(mainboard[i-1][j-1] == ALIVE)
				{
					neighborCount++;
				}
				if(mainboard[i-1][j] == ALIVE)
				{
					neighborCount++;
				}
				if(mainboard[i-1][j+1] == ALIVE)
				{
					neighborCount++;
				}
				if(mainboard[i][j+1] == ALIVE)
				{
					neighborCount++;
				}

			}
			else if(j == SIZE-1) // right border
			{
				neighborCount = 0;
				if(mainboard[i-1][j] == ALIVE)
				{
					neighborCount++;
				}
				if(mainboard[i][j-1] == ALIVE)
				{
					neighborCount++;
				}
				if(mainboard[i-1][j-1] == ALIVE)
				{
					neighborCount++;
				}
				if(mainboard[i+1][j-1] == ALIVE)
				{
					neighborCount++;
				}
				if(mainboard[i+1][j] == ALIVE)
				{
					neighborCount++;
				}

			}
			else //everything else
			{
				neighborCount = 0;
				if(mainboard[i-1][j-1] == ALIVE)
				{
					neighborCount++;
				}
				if(mainboard[i-1][j] == ALIVE)
				{
					neighborCount++;
				}
				if(mainboard[i-1][j+1] == ALIVE)
				{
					neighborCount++;
				}
				if(mainboard[i][j-1] == ALIVE)
				{
					neighborCount++;
				}
				if(mainboard[i][j+1] == ALIVE)
				{
					neighborCount++;
				}
				if(mainboard[i+1][j-1] == ALIVE)
				{
					neighborCount++;
				}
				if(mainboard[i+1][j] == ALIVE)
				{
					neighborCount++;
				}
				if(mainboard[i+1][j+1] == ALIVE)
				{
					neighborCount++;
				}
			}

			if(mainboard[i][j] == DEAD)
			{
				if(neighborCount == 3)
				{
					tempboard[i][j] = ALIVE;
				}
			}
			else if(mainboard[i][j] == ALIVE)
			{
				if(neighborCount == 2 || neighborCount == 3)
				{
					//do nothing
				}
				else
				{
					tempboard[i][j] = DEAD;
				}
			}

		}
	}

	copyToMain();
}
