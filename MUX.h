/*
*  This class imitate the functions of a multiplexer Unit of a processor. Values of
*  the instance variables 'operand1', and 'operand2' are set through their respective mutators. 
*  The value specified by control variable indicates the variable to be output. (control value 
*  of 0 outputs operand1, and value of 1 outputs operand2).
*
*  Author: Tianchang Yang
*  Date: 11/6/17
*/

#ifndef MUX_h
#define MUX_h

#include <string>
#include <iostream>

using namespace std;
class MUX {

public:

	//Default constructor
	MUX();

	//selects appropriate output
	void execute();

	//Set operand1 equal to the argument string - input format must be a 32 bits binary string
	void setOperand1(string operand);

	//Set operand2 equal to the argument string - input format must be a 32 bits binary string
	void setOperand2(string operand);

	//Sets the control equal to the argument int 
	//value of 0 outputs operand1, value of 1 outputs operand2
	void setControl(int control);

	//Returns the output - format is 32 bits binary string
	string getOutput();

private:
	int myControl; // value of 0 outputs operand1, value of 1 outputs operand2
	string myOperand1; //32 bits binary string
	string myOperand2; //32 bits binary string
	string myOutput; //32 bits result string
};

#endif
