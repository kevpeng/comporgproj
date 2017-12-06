/*
*  Simulate class
*
*  Author: Tianchang Yang
*  Date: 11/30/17
*/

#ifndef _SIMULATE_H_
#define _SIMULATE_H_

#include <fstream>
#include <iostream>
#include "ConfigFileParser.h"
#include "InstructionMemory.h"
#include "DataMemory.h"
#include "InstructionParser.h"
#include "MemParser.h"
#include "ALU.h"
#include "MUX.h"
#include "PC.h"
#include "RegisterFile.h"
#include "RegParser.h"
#include "ShiftLeft.h"
#include "SignExtend.h"
#include "ALUControl.h"
#include "Control.h"

using namespace std;
class Simulate {

public:

	//Default constructor
	Simulate(string filename);

	void run();

	void runNWrite();


private:
	
	string myConfigFile;
	bool batch;
	bool printMemory;
	bool writeToFile;
	string outputFile;

	InstructionMemory instruction_Memory;
	DataMemory data_Memory;
	ShiftLeft shift_Left_1;
	ShiftLeft shift_Left_2;
	SignExtend sign_Extend;
	ALU ALU_1;
	ALU ALU_2;
	ALU ALU_3;
	MUX MUX_1;
	MUX MUX_2;
	MUX MUX_3;
	MUX MUX_4;
	MUX MUX_5;
	ALUControl ALU_Control;
	Control main_Control;
	RegisterFile register_File;
	PC program_Counter;


	
	string hex2Bin(string input);
	string bin2Hex(string input);
	char getHexCharacter(string str);

};

#endif
