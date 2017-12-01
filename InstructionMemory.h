/*
*  InstructionMemory class
*
*  Author: Tianchang Yang
*  Date: 11/30/17
*/

#ifndef _INSTRUCTIONMEMORY_H_
#define _INSTRUCTIONMEMORY_H_

#include "InstructionParser.h"

using namespace std;
class InstructionMemory {

public:

	InstructionMemory();

	//Default constructor
	InstructionMemory(string filename);

	void readAddress(string address);

	string getInstruction();


private:
	
	string myAddress;

	map<string, string> myInstruction;

};

#endif
