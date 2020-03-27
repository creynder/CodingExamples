/*************************************
 * File name: CC3.cpp
 * Author: Chris Reynders
 * Email: creynder@nd.edu
 *
 * Given a set of inputs from the user, perform a
 * set of rotations on a array of integers
 *
 * ***********************************/

#include <iostream>
#include "../classes/DLList.h"

/*************************
 * Function Name: getInputConstr
 * Preconditions: int&, int&, char&
 * Postconditions: none
 * Gets input from the user and determines the length, rotations, and direction
 * **********************/
void getInputConstr(unsigned int& length, unsigned int& rotations, char& cDirection){

    std::cout << "-----------------------------------------------------------------------" << std::endl;
    std::cout << "Enter the length, number of rotations, and the direction (L/R)." << std::endl;
    std::cout << "e.g.: length = 5, number of rotations = 4, and the direction is left..." << std::endl;
    std::cout << "Then the desired input is: 5 4 L" << std::endl;
    std::cout << "Enter your values: ";

  std::cin >> length;
	std::cin >> rotations;
	std::cin >> cDirection;

}

void getVals(DLList<int>& theList, const unsigned int length){

	std::cout << "\nType in " << length << " integers: ";

	for(unsigned int i = 0; i < length; i++){

		int temp;
		std::cin >> temp;
		theList.Insert(temp);
	}

	std::cout << std::endl;

}


/*************************
 * Function Name: main
 * Preconditions: none
 * Postconditions: int
 * This is the main driver function
 * **********************/
int main()
{
    // Rotation char loop
    char loopCont = 'y';

    while(loopCont == 'y'){

		// Set the Initial input variables
		unsigned int length, rotations;
		char cDirection;

		// Get the input constraints
		getInputConstr(length, rotations, cDirection);

    std::cout << "User entered: Length = " << length;
		std::cout << ", NumRotations = " << rotations;
		std::cout << ", and will rotate in " << cDirection << " direction.\n";

		// Student algorithm will go here
    DLList<int> theList;
		getVals(theList, length);

		std::cout << "Initial List: " << theList << std::endl;

		// Rotate
		theList.rotate(rotations, cDirection);

		// Print final list to user
		std::cout << "Rotated List: " << theList << std::endl;


		// Finish the loop
        std::cout << "Continue? Enter y/n: ";
        std::cin >> loopCont;

    }

    std::cout << "...Exiting Program ..." << std::endl;

    return 0;
}
