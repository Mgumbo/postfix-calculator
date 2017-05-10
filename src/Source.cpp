/*************************************************************************
 * Author: Mgumbo
 *
 * Date Completed: 24 February 2016
 *
 * Description: A driver program that creates a Calculator object
 *		and calls the object's start() method to begin
 *		user interaction with the program.
 **/

#include <iostream>
#include "Calculator.h"

/**
 * Runs the program.
 **/
int main()
{
	Calculator calc; //create the Calculator object
	calc.start(); //start the Calculator

	return 0;
} //end main
