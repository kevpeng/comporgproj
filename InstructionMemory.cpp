/*
*  
*
*  Author: Tianchang Yang
*  Date: 11/30/17
*/

#include "InstructionMemory.h"


//Default constructor
InstructionMemory::InstructionMemory() {
	
}

//Default constructor
InstructionMemory::InstructionMemory(string filename) {
	InstructionParser parser = InstructionParser(filename);
	myInstruction = parser.getInstruction();
}

void InstructionMemory::readAddress(string address){
	myAddress = address;
}


string InstructionMemory::getInstruction(){
	return myInstruction[myAddress];
}