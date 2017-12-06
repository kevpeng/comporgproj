/*
*  This class imitate the functions of a Arithmetic Logic Unit of a processor. Values of
*  the instance variables 'operation', 'operand1', and 'operand2' are set through
*  their respective mutators. Method execute then performs the appropriate computation and
*  the result can be accessed from method getOutput (Comparison result can be accessed from
*  method isEqual). 
*
*  Author: Tianchang Yang
*  Date: 11/3/17
*/

#ifndef ALU_h
#define ALU_h

#include <string>
#include <iostream>

using namespace std;
class ALU {

public:

	//Default constructor
	ALU();

	//performs appropriate function
	void execute();

	//Set operand1 equal to the argument string - input format must be a 32 bits binary string
	void setOperand1(string operand);

	//Set operand2 equal to the argument string - input format must be a 32 bits binary string
	void setOperand2(string operand);

	//Sets the operation equal to the argument int 
	//compare is 0; addition is 1; subtract is 2;
	void setOperation(int operation);

	//Returns the output - format is 32 bits binary string
	//except when comparing - then it would be string "true" if they are equal, "false" otherwise
	string getOutput();

	
	bool isEqual();

private:
	int myOperation; // compare is 0; addition is 1; subtract is 2;
	string myOperand1; //32 bits binary string
	string myOperand2; //32 bits binary string
	string myOutput; //32 bits result string
	bool equals;

	//helper methods
	void compare();
	void add();
	string add(string operand1, string operand2);
	void subtract();
};

#endif
