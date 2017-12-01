//g++ -Wall main.cpp Simulate.cpp InstructionMemory.cpp InstructionParser.cpp ConfigFileParser.cpp DataMemory.cpp ShiftLeft.cpp signExtend.cpp ALU.cpp MUX.cpp ALUControl.cpp Control.cpp RegParser.cpp MemParser.cpp -o main



/*
*  
*
*  Author: Tianchang Yang
*  Date: 11/30/17
*/

#include "Simulate.h"

//Default constructor
Simulate::Simulate(string filename) {
	myConfigFile = filename;
	batch = false;
	printMemory = false;
	writeToFile = false;

	ConfigFileParser configParser = ConfigFileParser();
	configParser.configure(myConfigFile);

	string programFile = configParser.getInputFile();
	string memoryFile = configParser.getMemoryFile();
	string registerFile = configParser.getRegisterFile();
	outputFile = configParser.getOutputFile();
	batch = configParser.getOutputMode();
	writeToFile = configParser.getWriteToFile();
	printMemory = configParser.getPrintMemory();


	instruction_Memory = InstructionMemory(programFile);
	//instruction_Memory.readAddress("00400000");
	//cout << instruction_Memory.getInstruction() << endl;

	data_Memory = DataMemory(memoryFile);

	shift_Left_1 = ShiftLeft();
	shift_Left_2 = ShiftLeft();

	//cout << shift_Left_2.shift("11111111111111111111111111111111") << endl;

	sign_Extend = SignExtend();
	//cout << sign_Extend.extend("11010100010000101") << endl;

	ALU_1 = ALU();
	ALU_2 = ALU();
	ALU_3 = ALU();
	MUX_1 = MUX();
	MUX_2 = MUX();
	MUX_3 = MUX();
	MUX_4 = MUX();
	MUX_5 = MUX();
	ALU_Control = ALUControl();
	main_Control = Control();
}

//performs appropriate function
void Simulate::run(){
	parse();
}

void Simulate::parse(){
	
}