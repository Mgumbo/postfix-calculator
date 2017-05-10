/*************************************************************
 * Author: Mgumbo
 *
 * Date Completed: 24 February 2016
 *
 * Description: File containing the implementation for
 *				the Calculator class.
 ***************************************************************/

#include <iostream>
#include <cstdlib>
#include "Calculator.h"

/**
 * A default constructor. Initializes the bool controlling looping
 * to true.
 **/
Calculator::Calculator() : _running(true)
{
}

/**
 * A wrapper function that begins to display the menu.
 **/
void Calculator::start()
{
	//continue to loop through the menu
	do
	{
		displayMenu();
	} while (_running);
} //end start

/**
 * Loops through a text-based menu in order to get user input. Prompts
 * the user to enter an expression and, if it is valid, evaluates the
 * expression and prints the result. This menu will continue to loop
 * until the user provides input to exit.
 **/
void Calculator::displayMenu()
{
	//prompt user and get input
	std::cout << "Enter an expression: ";
	std::string expression;
	std::getline(std::cin, expression);

	//check if the user's group operator input is valid
	if (matchingGroupOperators(expression))
	{
		expression = convertToPostfix(expression);
		std::cout << "Postfix: " << expression << "\n";
		std::cout << "Result is: " << evaluatePostfix(expression) << "\n";

		//check if the user wants to keep using the calculator
		char userInput = ' ';
		do
		{
			std::cout << "Would you like to continue (y/n)? ";
			std::cin >> userInput;

			if (userInput == 'n') //if the user wants to exit
			{
				_running = false; //the user wants to quit
				break; //exit current while
			} //end if
			else if (userInput != 'y') //if user does not input 'y' or 'n'
				std::cout << "Please enter a valid response.\n";
		} while (userInput != 'y'); //end do-while

		std::cout << "\n"; //print a blank line for clarity
		std::cin.ignore(); //clear newline char from stream to continue
	} //end if
	else
		std::cout << "Invalid group operators. "
				  << "Please verify your parenthesis.\n\n";
} //end displayMenu

/**
 * Takes a string representing an expression in infix notation as a parameter
 * and iterates through it in order to verify that each opening group operator
 * has an accompanying closing group operator.
 **/
bool Calculator::matchingGroupOperators(std::string infixExpression) const
{
	//this stack will hold open parenthesis to verify the expression is valid
	Mystack<char> verifyStack;

	//loop through the expression
	for (int i = 0; i < infixExpression.length(); i++)
	{
		if (infixExpression[i] == '(')
			verifyStack.push('(');
		else if (infixExpression[i] == ')')
		{
			if (verifyStack.isEmpty()) //if there's a close without an open
				return false;
			else
				verifyStack.pop();
		} //end else if
	} //end for

	return verifyStack.isEmpty();
} //end matchingGroupOperators

/**
 * Returns an int representing the precedence level of a given operator
 * character. '+' and '-' have the same precedence, but have a lower
 * precedence than '*', '/', and '%'.
 **/
int Calculator::checkPrecedence(char op) const
{
	return (op == '+' || op == '-') ? 1 : 2;
} //end checkPrecedence

/**
 * Takes a string representing an expression in infix notation as a parameter
 * and then attempts to convert the expression into postfix notation. This
 * will account for numbers with multiple digits, and adds a space in between
 * each operator and operand before returning a string representing the
 * expression in proper postfix notation.
 **/
std::string Calculator::convertToPostfix(std::string infixExpression)
{
	std::string postfixExpression = ""; //chars will be appended in postfix form
	Mystack<char> operators; //stack that will hold operators

	//loop through the characters of the infix expression
	for (int i = 0; i < infixExpression.length(); i++)
	{
		char ch = infixExpression[i];

		switch (ch) //check the character
		{
		case ' ': //simply ignore spaces if the user types any
			break;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			while (isdigit(infixExpression[i])) //account for multiple digits
				postfixExpression += infixExpression[i++]; //append digits

			i--; //decrement to prevent from skipping over operators
			postfixExpression += ' '; //add a space after the complete number
			break;
		case '(': //opening group operator
			operators.push(ch);
			break;
		case ')': //closing group operator
			while (operators.top() != '(')
			{
				postfixExpression += operators.top(); //append top of stack
				operators.pop();
				postfixExpression += ' ';
			} //end while
			operators.pop();
			break;
		case '-':
		case '+':
		case '*':
		case '/':
		case '%':
			/* pop the stack until it's either empty, the next operator is
			   higher precedence, or the top is the closing group operator */
			while (!operators.isEmpty() &&
				checkPrecedence(ch) <= checkPrecedence(operators.top()) &&
				operators.top() != '(')
			{
				postfixExpression += operators.top(); //append top of stack
				operators.pop();
				postfixExpression += ' ';
			} //end while
			operators.push(ch); //add the new operator to the stack
			break;
		default: //if the user inputs an invalid character, return empty string
			std::cout << "Invalid character: " << ch << "\n";
			return "";
		} //end switch
	} //end for

	//append the remainder of the operators until there are no more
	while (!operators.isEmpty())
	{
		postfixExpression += operators.top();
		postfixExpression += ' '; //append a space in between operators
		operators.pop();
	} //end while

	return postfixExpression;
} //end convertToPostfix

/**
 * Takes a string representing an expression in postfix notation as a parameter
 * and evaluates the expression to return the result. While iterating through
 * the string, adds operands to a stack and performs operations on them until
 * the expression has been fully evaluated. The result is then returned as an
 * int.
 **/
int Calculator::evaluatePostfix(std::string postfixExpression)
{
	Mystack<int> operands; //will hold all of the operands for evaluation

	//iterate through the postfix expression
	for (int i = 0; i < postfixExpression.length(); i++)
	{
		if (isdigit(postfixExpression[i]))
		{
			std::string temp; //will hold the digits for a multi-digit number
			while (postfixExpression[i] != ' ')
				temp += postfixExpression[i++]; //append digit and increment

			//convert the string to an int, and then push it onto the stack
			operands.push(std::atoi(temp.c_str()));
		} //end if
		else if (postfixExpression[i] != ' ') //do not treat spaces as operators
		{
			//prepare operands and operators
			char operatorChar = postfixExpression[i];
			int operand1, operand2;

			if (!operands.isEmpty()) //the stack should have operands in it
			{
				//since the second operand went in last, get it out first
				operand2 = operands.top();
				operands.pop();
			} //end if
			else
			{
				std::cout << "Error, only one operand. "
						  << "Unable to calculate proper result.\n";
				return 0;
			} //end else

			if (!operands.isEmpty()) //the stack should still have stuff in it
			{
				//now the first operand is retrieved
				operand1 = operands.top();
				operands.pop();
			} //end if
			else
			{
				std::cout << "Error, only one operand. "
						  << "Unable to calculate proper result.\n";
				return 0;
			} //end else

			//perform the appropriate operation
			switch (operatorChar)
			{
			case '+': //addition
				operands.push(operand1 + operand2);
				break;
			case '-': //subtraction
				operands.push(operand1 - operand2);
				break;
			case '*': //multiplication
				operands.push(operand1 * operand2);
				break;
			case '/': //division
				operands.push(operand1 / operand2);
				break;
			case '%': //modulus
				operands.push(operand1 % operand2);
				break;
			} //end switch
		} //end else if
	} //end for

	int result = 0; //initialize to 0 in case the user didn't actually enter anything
	if (!operands.isEmpty())
	{
		//the top is equal to the result, so store it and pop to clear the stack
		result = operands.top();
		operands.pop();
	} //end if

	if (!operands.isEmpty()) //if the stack has contents, something went wrong
	{
		std::cout << "Error, incorrect result\n";
		return 0;
	} //end if

	return result;
} //end evaluatePostfix