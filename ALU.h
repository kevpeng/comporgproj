/*
*  This class imitate the functions of a Arithmetic Logic Unit of a processor. Values of
*  the instance variables 'operation', 'operand1', and 'operand2' are set through
*  their respective mutators. Method execute then performs the appropriate computation and
*  the result can be accessed from method getOutput (Comparison result can be accessed from
*  method isEqual). 
*
*  Author: Tianchang Yang
*/

#ifndef ALU_h
#define ALU_h

#include <string>

using namespace std;
class ALU {

public:

	//Default constructor
	ALU();

	//performs appropriate function
	void execute();

	//Set operand1 equal to the argument string
	void setOperand1(string operand);

	//Set operand2 equal to the argument string
	void setOperand2(string operand);

	//Sets the operation equal to the argument int
	void setOperation(int in);

	//Returns the output
	string getOutput();

	//returns true if two operands are equal, false otherwise
	bool isEqual();
};

#endif
