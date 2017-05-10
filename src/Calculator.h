/*************************************************************************
 * Author: Mgumbo
 *
 * Date Completed: 24 February 2016
 *
 * Description: A class that represents a calculator. This class will
 *				allow the user to input an expression, and the calculator 
 *				will evaluate the expression using a custom stack class.
 *************************************************************************/

#ifndef CALCULATOR_H_
#define CALCULATOR_H_

#include <string>
#include "Mystack.cpp"

class Calculator
{
public:
	Calculator(); //default constructor

	//Run the calculator
	void start();

private:
	//Member functions
	void displayMenu();
	bool matchingGroupOperators(std::string infixExpression) const;
	int checkPrecedence(char op) const;
	std::string convertToPostfix(std::string infixExpression);
	int evaluatePostfix(std::string postfixExpression);

	//Member variables
	bool _running; //controls whether the calculator keeps looping
};

#endif