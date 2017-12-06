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

#include "ALU.h"

using namespace std;

//Default constructor
ALU::ALU() {
	myOperation = -1;
	equals = false;
}

//performs appropriate function
void ALU::execute(){
	if (myOperation == 0) {
		compare();
	}
	if (myOperation == 1) {
		compare();
		add();
	}
	if (myOperation == 2) {
		compare();
		subtract();
	}
}

void ALU::compare() {
	subtract(); //do subtract first
	if (myOutput == "00000000000000000000000000000000") {
		//the subtract result is zero
		myOutput = "00000000000000000000000000000000";
		equals = true;
	} else {
		myOutput = "00000000000000000000000000000000";
		equals = false;
	}
}

// ignores overflow!!
void ALU::add() {
	myOutput = add(myOperand1, myOperand2); //call helper method
}

string ALU::add(string operand1, string operand2) {
	//cout << "operand1\t" << operand1 << "\tlength:\t"<< operand1.length () << endl;
	//cout << "operand2\t" << operand2 << "\tlength:\t"<< operand2.length () << endl;
	//cout << "yep" << endl;
	char carry = '0'; //carry bit
	string result = "00000000000000000000000000000000";
	for (int i = 31; i > -1; i--) {
		//cout << i << carry << myOperand1[i] << myOperand2[i] << endl;
		if (operand1[i] == '0' && operand2[i] == '0' && carry == '0') {
			//ignore overflow

			//cout << i << "\tcarry = 0 result = 0" << endl;
			result[i] = '0';
			carry = '0';
		} else if ((operand1[i] == '0' && operand2[i] == '0' && carry == '1')
			|| (operand1[i] == '0' && operand2[i] == '1' && carry == '0')
			|| (operand1[i] == '1' && operand2[i] == '0' && carry == '0')) {
			//cout << i << "\tcarry = 0 result = 1" << endl;
			result[i] = '1';
			carry = '0';
		} else if ((operand1[i] == '1' && operand2[i] == '1' && carry == '0')
			|| (operand1[i] == '1' && operand2[i] == '0' && carry == '1')
			|| (operand1[i] == '0' && operand2[i] == '1' && carry == '1')) {
			//cout << i << "\tcarry = 1 result = 0" << endl;
			result[i] = '0';
			carry = '1';
		} else if (operand1[i] == '1' && operand2[i] == '1' && carry == '1') {
			//cout << i << "\tcarry = 1 result = 1" << endl;
			result[i] = '1';
			carry = '1';
		}
	}
	//cout << "result\t\t" << result << endl;
	return result;
}

// first performs two's complement on operand2, then call add method
// on operand1 and two's complement of operand2
void ALU::subtract() {
	string temp = "00000000000000000000000000000000";
	for (int i = 0; i < 32; i++) {
		if (myOperand2[i] == '0') {
			temp[i] = '1';
		} else if (myOperand2[i] == '1') {
			temp[i] = '0';
		}
	}
	string str = "00000000000000000000000000000001";
	//cout << temp << endl;
	//cout << str << endl;

	string complement = add(temp, str);
	// calculate two's complement of operand2

	//cout << temp << endl;
	//cout << str << endl;
	//cout << "complement: \t" << complement << endl;
	string result = add(myOperand1, complement);
	// calculate sum of operand1 and two's complement of operand2

	myOutput = result;
}

//Set operand1 equal to the argument string
void ALU::setOperand1(string operand){
	myOperand1 = operand;
}

//Set operand2 equal to the argument string
void ALU::setOperand2(string operand) {
	myOperand2 = operand;
}

//Sets the operation equal to the argument int
void ALU::setOperation(int operation) {
	myOperation = operation;
}

//Returns the output
string ALU::getOutput() {
	return myOutput;
}

//returns true if two operands are equal, false otherwise
bool ALU::isEqual(){
	return equals;
}
