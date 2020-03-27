/**********************************************
* File: childSteps.cpp
* Author: Christopher Reynders
* Email: creynder@nd.edu
**********************************************/

#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream, std::stringbuf
#include <cstdlib>		// exitr

/********************************************
* Function Name  : getArgv1Num
* Pre-conditions : int argc, char** argv
* Post-conditions: int
*
* Returns argv[1] as an int if valid
********************************************/
int getArgv1Num(int argc, char** argv){

	if(argc != 2){
		std::cout << "Incorrect number of inputs" << std::endl;
		exit(-1);
	}

	// stringstream used for the conversion initialized with the contents of argv[1]
	int stepVal;
	std::stringstream convert(argv[1]);

	//give the value to factNum using the characters in the string
	if ( !(convert >> stepVal) ){
		std::cout << "Not a valid integer" << std::endl;
		exit(-1);
	}

	// Check if input is < 1
	if( stepVal < 1 ){

		std::cout << stepVal << " must be 1 or more " << std::endl;
		exit(-1);
	}

	return stepVal;

}

/********************************************
* Function Name  : countMethods
* Pre-conditions : int n
* Post-conditions: int
*
* Returns the integer number of methods to reach the nth stair
********************************************/
int countMethods(int stepsLeft){
	//base case if number of steps left are 0, this means that there was only one way
	//for the child to go n number of steps
	if(stepsLeft == 0)
	{
		return 1;
	}
	else if(stepsLeft == 1)
	{
		//returns 1 because the only way to travel 1 step is by taking 1 step, prevents
		//tree from having to continue down the branch
		return 1;
	}
	else if(stepsLeft == 2)
	{
		//returns 2 because there are two ways to travel 2 steps, take 2 steps once or
		//take 1 step twice, prevents tree from having to continue down branch
		return 2;
	}
	else if(stepsLeft == 3)
	{
		//returns 4 because there are four ways to travel 3 steps, take 3 steps once, take
		//2 steps once and then 1 step once, take 1 step once and then 2 steps once,
		//or take 1 step three times
		return 4;
	}
	else
	{
		//if there are more than three steps, use recursion function to calculate the number of methods
		return countMethods(stepsLeft-3) + countMethods(stepsLeft-2) + countMethods(stepsLeft-1);
	}
}


/********************************************
* Function Name  : main
* Pre-conditions : int argc, char** argv
* Post-conditions: int
*
* This is the main driver function
********************************************/
int main(int argc, char** argv){

	// Get the number of steps from the user
	int numSteps = getArgv1Num(argc, argv);

	std::cout << "The child is taking " << numSteps << " steps " << std::endl;

	int numMethods = countMethods(numSteps);

	std::cout << "There are " << numMethods << " methods to climb " << numSteps << " steps going 1, 2, or 3 steps at a time" << std::endl;

	return 0;
}
