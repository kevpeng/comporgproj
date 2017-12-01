/*
*  
*
*  Author: Tianchang Yang
*  Date: 11/30/17
*/

#include "ALUControl.h"

//Default constructor
ALUControl::ALUControl() {
	myOp = -1;
}


void ALUControl::setALUOp(int op){
	myOp = op;
}

void ALUControl::setInstruction(string instruction){
	if (instruction ==	"100000") {
		myOp = 1;
	} else if (instruction == "100010") {
		myOp = 2;
	} else if (instruction == "101010") {
		myOp = 2;
	} else {
		//myOp = -1
	}
}