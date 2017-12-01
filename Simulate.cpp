//g++ -Wall main.cpp Simulate.cpp InstructionMemory.cpp InstructionParser.cpp ConfigFileParser.cpp DataMemory.cpp ShiftLeft.cpp signExtend.cpp ALU.cpp MUX.cpp ALUControl.cpp Control.cpp RegParser.cpp MemParser.cpp RegisterFile.cpp PC.cpp -o main



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
	instruction_Memory.readAddress("00400000");
	//cout << instruction_Memory.getInstruction() << endl;
	//cout << instruction_Memory.getInstruction().empty() << endl;
	//instruction_Memory.readAddress("00400C00");
	//cout << instruction_Memory.getInstruction() << endl;
	//cout << instruction_Memory.getInstruction().empty() << endl;

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
	register_File = RegisterFile(registerFile);
	//register_File.printRegisterFile();
	//register_File.readRegister1("11111");
	//cout << register_File.readData1() << endl;

	program_Counter = PC();
}

//performs appropriate function
void Simulate::run(){
	string curAddress = program_Counter.getAddress();
	instruction_Memory.readAddress(curAddress);
	string curInstruction = instruction_Memory.getInstruction();



	while (!curInstruction.empty()) {
		if (!batch) {
			cout << "Press Enter to Continue";
			cin.ignore();
		}

		//cout << curInstruction << endl;

		//PC + 4
		ALU_1.setOperand1(hex2Bin(curAddress));
		ALU_1.setOperand2("00000000000000000000000000000100");
		ALU_1.setOperation(1);
		ALU_1.execute();
		string PC_plus_4 = bin2Hex(ALU_1.getOutput());
		//cout << curAddress << endl;


		//update address to PC and fetch next instruction
		curAddress = PC_plus_4;
		instruction_Memory.readAddress(curAddress);
		curInstruction = instruction_Memory.getInstruction();
	}
}


















string Simulate::hex2Bin(string input) {
  string result;
  for (int i = 0; i < input.length(); i++) {
    char c = input[i];
    if (c == '0')  result += "0000";
    if (c == '1')  result += "0001";
    if (c == '2')  result += "0010";
    if (c == '3')  result += "0011";
    if (c == '4')  result += "0100";
    if (c == '5')  result += "0101";
    if (c == '6')  result += "0110";
    if (c == '7')  result += "0111";
    if (c == '8')  result += "1000";
    if (c == '9')  result += "1001";
    if (c == 'A')  result += "1010";
    if (c == 'B')  result += "1011";
    if (c == 'C')  result += "1100";
    if (c == 'D')  result += "1101";
    if (c == 'E')  result += "1110";
    if (c == 'F')  result += "1111";
  }
  return result;
}


char Simulate::getHexCharacter(string str)
{
	if(str.compare("1111") == 0) return 'F';
	else if(str.compare("1110") == 0) return 'E';
	else if(str.compare("1101")== 0) return 'D';
	else if(str.compare("1100")== 0) return 'C';
	else if(str.compare("1011")== 0) return 'B';
	else if(str.compare("1010")== 0) return 'A';
	else if(str.compare("1001")== 0) return '9';
	else if(str.compare("1000")== 0) return '8';
	else if(str.compare("0111")== 0) return '7';
	else if(str.compare("0110")== 0) return '6';
	else if(str.compare("0101")== 0) return '5';
	else if(str.compare("0100")== 0) return '4';
	else if(str.compare("0011")== 0) return '3';
	else if(str.compare("0010")== 0) return '2';
	else if(str.compare("0001")== 0) return '1';
	else if(str.compare("0000")== 0) return '0';
	return ' ';
}

string Simulate::bin2Hex(string input)
{
	string endresult = "";
	for(int i = 0; i < input.length(); i = i+4)
	{
		endresult += getHexCharacter(input.substr(i,4));
	}
	return endresult;
}

