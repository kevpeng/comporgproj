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

	string getOriginal();

	//print out contents
	void print();

	map<string, string> getMap() { return myInstruction; }

private:
	
	string myAddress;

	map<string, string> myInstruction;

	map<string, string> myOriginal;
	
	// helper methods to print in hexidecimal
	char getHexCharacter(string str);
	string bin2Hex(string s);
	string add(string operand1, string operand2);
	
};

#endif
