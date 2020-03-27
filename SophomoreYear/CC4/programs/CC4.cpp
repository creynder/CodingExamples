#include <iostream>
#include "../classes/BST.h"

/*************************
 * Function Name: fillTree
 * Preconditions: int&, int&, char&
 * Postconditions: none
 * Gets input from the user and determines the length, rotations, and direction
 * **********************/
void fillTree(BST<int>& theTree){

	unsigned int numElements;

    std::cout << "-----------------------------------------------------------------------" << std::endl;
    std::cout << "First, enter the number of elements in the tree: ";
    std::cin >> numElements;

	std::cout << "\nNext, insert " << numElements << " elements into the tree: ";

	for(unsigned int i = 0; i < numElements; i++){

		int temp;
		std::cin >> temp;

		theTree.Insert(temp);
	}

	std::cout << "\nThe initial tree is: \n";

	theTree.printInOrder(std::cout);

	theTree.printPreOrder(std::cout);

	theTree.printPostOrder(std::cout);

}



/*************************
 * Function Name: main
 * Preconditions: none
 * Postconditions: int
 * This is the main driver function
 * **********************/
int main()
{

	// Create the Binary Search Tree
	BST<int> theTree;

	// Fill the Tree
	fillTree( theTree );

    // Rotation char loop
    char loopCont = 'y';

	while(loopCont == 'y'){

			int x1;
			int x2;

			std::cout << "Insert a pair to check - [First] [Second]: ";
			std::cin >> x1;
			std::cin >> x2;

			theTree.printLowestCommonAncestor(x1,x2);

			std::cout << "\nContinue loop? [y/n]: ";
			std::cin >> loopCont;
			std::cout << std::endl;
	}

    std::cout << "...Exiting Program ..." << std::endl;

    return 0;
}
