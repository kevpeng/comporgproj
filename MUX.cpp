/*
*  This class imitate the functions of a multiplexer Unit of a processor. Values of
*  the instance variables 'operand1', and 'operand2' are set through their respective mutators. 
*  The value specified by control variable indicates the variable to be output. (control value 
*  of 0 outputs operand1, and value of 1 outputs operand2).
*
*  Author: Tianchang Yang
*  Date: 11/6/17
*/

#include "MUX.h"

using namespace std;

//Default constructor
MUX::MUX() {
	myControl = -1;
	myOutput = "00000000000000000000000000000000";
}

//selects appropriate output
void MUX::execute(){
	if (myControl == 0) {
		myOutput = myOperand1;
	} else if (myControl == 1) {
		myOutput = myOperand2;
	}
}

//Set operand1 equal to the argument string
void MUX::setOperand1(string operand){
	myOperand1 = operand;
}

//Set operand2 equal to the argument string
void MUX::setOperand2(string operand) {
	myOperand2 = operand;
}

//Sets the control equal to the argument int 
//value of 0 outputs operand1, value of 1 outputs operand2
void MUX::setControl(int control) {
	myControl = control;
}

//Returns the output
string MUX::getOutput() {
	return myOutput;
}
