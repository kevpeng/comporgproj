//g++ -Wall main.cpp Simulate.cpp InstructionMemory.cpp InstructionParser.cpp ConfigFileParser.cpp DataMemory.cpp ShiftLeft.cpp SignExtend.cpp ALU.cpp MUX.cpp ALUControl.cpp Control.cpp RegParser.cpp MemParser.cpp RegisterFile.cpp PC.cpp -o main



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

	if (!writeToFile) {
		run();
	} else {
		runNWrite();
	}
}

//performs appropriate function
void Simulate::run(){
	string curAddress = program_Counter.getAddress();
	instruction_Memory.readAddress(curAddress);
	string curInstruction = instruction_Memory.getInstruction();
	string curOriginal = instruction_Memory.getOriginal();
	cout << "------------------begining simulation------------------" << endl;



	while (!curInstruction.empty()) {
		if (!batch) {
			cout << "Press Enter to Continue";
			cin.ignore();
		}

		
		cout << "Next instruction is: " << curOriginal << endl;

		cout << "binary machine code: " << curInstruction << endl << endl;

		if (printMemory) {
			register_File.printRegisterFile();
			cout << endl;
			data_Memory.print();
			cout << endl;
			instruction_Memory.print();
		}
		

		//PC
		cout << "PC: \ncurrent PC address: " << "0x" << curAddress << endl << endl;
		cout << "Instruction memory: current instruction memory address: " << "0x" << curAddress << endl;
		cout << "current instruction fetched from instruction memory: " << "0x" << bin2Hex(curInstruction) << endl;


		//cout << curInstruction << endl;

		//PC + 4
		ALU_1.setOperand1(hex2Bin(curAddress));
		ALU_1.setOperand2("00000000000000000000000000000100");
		ALU_1.setOperation(1);
		ALU_1.execute();
		string PC_plus_4 = bin2Hex(ALU_1.getOutput());
		cout << endl;
		cout << "ALU 1: \naddress PC passed into ALU 1 is: 0x" << curAddress << endl;
		cout << "the other operand ALU 1 takes in is: 0x" << bin2Hex("00000000000000000000000000000100") << endl;
		cout << "the result of ALU 1 is: 0x" << bin2Hex(ALU_1.getOutput()) << endl << endl;
		//cout << curAddress << endl;

		//Control
		string opcode = curInstruction.substr(0, 6);
		main_Control.setOpcode(opcode);
		//cout << opcode << endl;
		cout << "Control: \nThe opcode passed to control is: 0x" << bin2Hex("00" + opcode) << endl;
		cout << "RegDst: " << main_Control.getRegDst() << endl;
		cout << "Jump: " << main_Control.getJump() << endl;
		cout << "Branch: " << main_Control.getBranch() << endl;
		cout << "MemRead: " << main_Control.getMemRead() << endl;
		cout << "MemToReg: " << main_Control.getMemToReg() << endl;
		cout << "ALUOp: " << main_Control.getALUOp() << endl;
		cout << "MemWrite: " << main_Control.getMemWrite() << endl;
		cout << "ALUSrc: " << main_Control.getALUSrc() << endl;
		cout << "RegWrite: " << main_Control.getRegWrite() << endl << endl;


		//MUX 1
		MUX_1.setOperand1(curInstruction.substr(11,5));
		MUX_1.setOperand2(curInstruction.substr(16,5));
		MUX_1.setControl(main_Control.getRegDst());
		MUX_1.execute();
		string MUX_1_output = MUX_1.getOutput();
		cout << "MUX 1: \nThe first operand passed in: 0x" << bin2Hex("000" + curInstruction.substr(11,5)) << endl;
		cout << "The second operand passed in: 0x" << bin2Hex("000" + curInstruction.substr(16,5)) << endl;
		cout << "The control passed to MUX 1 from main control is: " << main_Control.getRegDst() << endl;
		cout << "The output from MUX 1 is: 0x" << bin2Hex("000" + MUX_1_output) << endl << endl;


		//register file -- read
		register_File.readRegister1(curInstruction.substr(6,5));
		register_File.readRegister2(curInstruction.substr(11,5));
		register_File.writeToRegister(MUX_1_output);
		register_File.setWriteSignal(main_Control.getRegWrite());
		string registerData1 = register_File.readData1();
		string registerData2 = register_File.readData2();
		cout << "Register File: \nThe first read register number is: 0x" << bin2Hex("000" + curInstruction.substr(6,5)) << endl;
		cout << "The second read register number is: 0x" << bin2Hex("000" + curInstruction.substr(11,5)) << endl;
		cout << "The data read from first register is: 0x" << bin2Hex(registerData1) << endl;
		cout << "The data read from second register is: 0x" << bin2Hex(registerData2) << endl << endl;


		//sign extend
		string extend_Data = sign_Extend.extend(curInstruction.substr(16,16));
		//cout << curInstruction.substr(16,16) << endl;
		cout << "Sign Extend: \nThe input is: 0x" << bin2Hex(curInstruction.substr(16,16)) << endl;
		cout << "The output is: 0x" << bin2Hex(extend_Data) << endl << endl;


		//MUX 2
		MUX_2.setOperand1(registerData2);
		MUX_2.setOperand2(extend_Data);
		MUX_2.setControl(main_Control.getALUSrc());
		MUX_2.execute();
		string MUX_2_output = MUX_2.getOutput();
		cout << "MUX 2: \nThe first operand passed in: 0x" << bin2Hex(registerData2) << endl;
		cout << "The second operand passed in: 0x" << bin2Hex(extend_Data) << endl;
		cout << "The control passed to MUX 2 from main control is: " << main_Control.getALUSrc() << endl;
		cout << "The output from MUX 2 is: 0x" << bin2Hex(MUX_2_output) << endl << endl;


		//ALU Control
		ALU_Control.setALUOp(main_Control.getALUOp()); //Set ALUOp before set instruction!!!
		ALU_Control.setInstruction(curInstruction.substr(26,6));
		int ALUOperation = ALU_Control.getOutput();
		cout << "ALU Control: \nThe instruction received is: 0x" << bin2Hex("00" + curInstruction.substr(26,6)) << endl;
		cout << "The ALUOp received from main control is: " << main_Control.getALUOp() <<endl;
		cout << "The control sending to ALU 3 is: " << ALUOperation << endl << endl;


		//ALU 3
		ALU_3.setOperand1(registerData1);
		ALU_3.setOperand2(MUX_2_output);
		ALU_3.setOperation(ALUOperation);
		ALU_3.execute();
		string ALU_3_result = ALU_3.getOutput();
		bool isZero = ALU_3.isEqual();
		cout << "ALU 3:\nOperand 1 is: 0x" << bin2Hex(registerData1) << endl;
		cout << "Operand 2 is: 0x" << bin2Hex(MUX_2_output) << endl;
		cout << "Operation for ALU 3 to perform is: " << ALUOperation << endl;
		cout << "the result of ALU 3 is: 0x" << bin2Hex(ALU_3_result) << endl;
		cout << "The two operand is equal or not: " << isZero << endl << endl;


		//Data memory
		data_Memory.setAddress(bin2Hex(ALU_3_result));
		//if (main_Control.getMemRead()) {
		//	cout <<  "ATTENTION: " << bin2Hex(ALU_3_result) << endl;
		//}
		data_Memory.setWriteData(registerData2);
		data_Memory.setMemWrite(main_Control.getMemWrite());
		data_Memory.setMemRead(main_Control.getMemRead());
		data_Memory.execute();
		string memory_Data = data_Memory.readData();
		cout << "Data Memory: \nAddress is set to: 0x" << bin2Hex(ALU_3_result) << endl;
		cout << "Data to write is: 0x" << bin2Hex(registerData2) << endl;
		cout << "MemWrite signal received from main control is: " << main_Control.getMemWrite() << endl;
		cout << "MemRead signal received from main control is: " << main_Control.getMemRead() << endl;
		cout << "The data read from data memory is: 0x" << bin2Hex(memory_Data) << endl << endl;

		//MUX 3
		MUX_3.setOperand1(ALU_3_result);
		MUX_3.setOperand2(memory_Data);
		MUX_3.setControl(main_Control.getMemToReg());
		MUX_3.execute();
		string MUX_3_output = MUX_3.getOutput();
		cout << "MUX 3: \nThe first operand passed in: 0x" << bin2Hex(ALU_3_result) << endl;
		cout << "The second operand passed in: 0x" << bin2Hex(memory_Data) << endl;
		cout << "The control passed to MUX 3 from main control is: " << main_Control.getMemToReg() << endl;
		cout << "The output from MUX 3 is: 0x" << bin2Hex(MUX_3_output) << endl << endl;

		if (opcode == "000000" && curInstruction.substr(26,6) == "101010") {
			if (MUX_3_output.substr(0,1) == "1") {
				MUX_3_output = "00000000000000000000000000000001";
			} else {
				MUX_3_output = "00000000000000000000000000000000";
			}

			if (registerData1.substr(0,1) == "0" && MUX_2_output.substr(0,1) == "1") {
				MUX_3_output = "00000000000000000000000000000000";
			}
		}

		//writeback
		register_File.writeData(MUX_3_output);
		cout << "Writeback: \nThe RegWrite signal is: " << main_Control.getRegWrite() << endl;
		cout << "The data to write to register is: 0x" << bin2Hex(MUX_3_output) << endl;
		cout << "The register to write to is: 0x" << bin2Hex("000" + MUX_1_output) << endl << endl;

		//shift left 1
		string jump_address = shift_Left_1.shift(curInstruction.substr(6,26));
		cout << "Shift left 1: \nThe instruction passed in is: 0x" << bin2Hex("00" + curInstruction.substr(6,26)) << endl;
		cout << "Shift result is: 0x" << bin2Hex(jump_address) << endl;
		//cout << PC_plus_4 << endl;
		jump_address = hex2Bin(PC_plus_4).substr(0,4) + jump_address;
		jump_address = bin2Hex(jump_address);
		//cout << jump_address << endl;
		cout << "The jump address is: 0x" << jump_address << endl << endl;

		//shift left 2
		string branch_address = shift_Left_2.shift(extend_Data);
		cout << "Shift left 2: \nThe instruction passed in is: 0x" << bin2Hex(extend_Data) << endl;
		cout << "Shift result is: 0x" << bin2Hex(branch_address) << endl << endl;

		//ALU 2
		ALU_2.setOperand1(hex2Bin(PC_plus_4));
		ALU_2.setOperand2(branch_address);
		ALU_2.setOperation(1);
		ALU_2.execute();
		string ALU_2_result = ALU_2.getOutput();
		cout << "ALU 2:\nOperand 1 is: 0x" << PC_plus_4 << endl;
		cout << "Operand 2 is: 0x" << bin2Hex(branch_address) << endl;
		cout << "the result of ALU 2 is: 0x" << bin2Hex(ALU_2_result) << endl << endl;
		branch_address = bin2Hex(ALU_2_result);

		MUX_5.setOperand1(PC_plus_4);
		MUX_5.setOperand2(branch_address);
		int MUX_5_Control;
		if (isZero && main_Control.getBranch()) {
			MUX_5_Control = 1;
		} else {
			MUX_5_Control = 0;
		}
		MUX_5.setControl(MUX_5_Control);
		MUX_5.execute();
		string MUX_5_output = MUX_5.getOutput();
		cout << "MUX 5: \nThe first operand passed in: 0x" << PC_plus_4 << endl;
		cout << "The second operand passed in: 0x" << branch_address << endl;
		cout << "The control passed to MUX 5 from main control is: " << MUX_5_Control << endl;
		cout << "The output from MUX 5 is: 0x" << MUX_5_output << endl << endl;

		MUX_4.setOperand1(MUX_5_output);
		MUX_4.setOperand2(jump_address);
		MUX_4.setControl(main_Control.getJump());
		MUX_4.execute();
		string nextAddress = MUX_4.getOutput();
		cout << "MUX 4: \nThe first operand passed in: 0x" << MUX_5_output << endl;
		cout << "The second operand passed in: 0x" << jump_address << endl;
		cout << "The control passed to MUX 4 from main control is: " << main_Control.getJump() << endl;
		cout << "The output from MUX 4 is: 0x" << nextAddress << endl << endl;





		//update address to PC and fetch next instruction
		curAddress = nextAddress;
		instruction_Memory.readAddress(curAddress);
		curInstruction = instruction_Memory.getInstruction();
		curOriginal = instruction_Memory.getOriginal();

		cout << endl << endl;



		//data_Memory.print();


		//curInstruction = "";
	}

	cout << "------------------end------------------" << endl;
	if (printMemory) {
		register_File.printRegisterFile();
		cout << endl;
		data_Memory.print();
		cout << endl;
		instruction_Memory.print();
	}
}










//performs appropriate function
void Simulate::runNWrite(){

	ofstream writeFile;
	writeFile.open(outputFile);

	string curAddress = program_Counter.getAddress();
	instruction_Memory.readAddress(curAddress);
	string curInstruction = instruction_Memory.getInstruction();
	string curOriginal = instruction_Memory.getOriginal();
	cout << "------------------begining simulation------------------" << endl;
	writeFile << "------------------begining simulation------------------" << endl;



	while (!curInstruction.empty()) {
		if (!batch) {
			cout << "Press Enter to Continue";
			writeFile << "Press Enter to Continue" << endl;
			cin.ignore();
		}

		
		cout << "Next instruction is: " << curOriginal << endl;
		cout << "binary machine code: " << curInstruction << endl << endl;

		writeFile << "Next instruction is: " << curOriginal << endl;
		writeFile << "binary machine code: " << curInstruction << endl << endl;

		if (printMemory) {
			register_File.printRegisterFile();
			cout << endl;
			data_Memory.print();
			cout << endl;
			instruction_Memory.print();

			//register_File.writeToFile(outputFile);
			//writeFile << endl;
			//data_Memory.writeToFile(outputFile);
			//writeFile << endl;
			//instruction_Memory.print();

			


    		writeFile << "Printing Registers" << endl;
    		map<int, string> registers = register_File.getMap();
  			for (int i = 0; i < 32; i++) {
   		 		writeFile << "Register["  << i << "] = " << "\t 0x"<< bin2Hex(registers[i]) << endl;
  			}

  			writeFile << endl << "Memory Contents:" << endl;
			map<string,string> dataMemoryMap = data_Memory.getMap();
  			map<string,string>::iterator it2;
  			for(it2 = dataMemoryMap.begin(); it2 != dataMemoryMap.end(); it2++){
				string t = it2->second;
    			writeFile << "address:[0x" << it2->first << "] = 0x" << bin2Hex(t) << endl;
    		}
    		writeFile << endl;

    		writeFile << "Instruction Memory Contents:" << endl;
    		map<string, string> myInstruction = instruction_Memory.getMap();
  			map<string,string>::iterator it3;
  			for(it3 = myInstruction.begin(); it3 != myInstruction.end(); it3++){
				string t = it3->second;
    			writeFile << "address:[0x" << it3->first << "] = 0x" << bin2Hex(t) << endl;
  			}
  			writeFile << endl;

		}
		

		//PC
		cout << "PC: \ncurrent PC address: " << "0x" << curAddress << endl << endl;
		cout << "Instruction memory: current instruction memory address: " << "0x" << curAddress << endl;
		cout << "current instruction fetched from instruction memory: " << "0x" << bin2Hex(curInstruction) << endl;

		writeFile << "PC: \ncurrent PC address: " << "0x" << curAddress << endl << endl;
		writeFile << "Instruction memory: current instruction memory address: " << "0x" << curAddress << endl;
		writeFile << "current instruction fetched from instruction memory: " << "0x" << bin2Hex(curInstruction) << endl;


		//cout << curInstruction << endl;

		//PC + 4
		ALU_1.setOperand1(hex2Bin(curAddress));
		ALU_1.setOperand2("00000000000000000000000000000100");
		ALU_1.setOperation(1);
		ALU_1.execute();
		string PC_plus_4 = bin2Hex(ALU_1.getOutput());
		cout << endl;
		cout << "ALU 1: \naddress PC passed into ALU 1 is: 0x" << curAddress << endl;
		cout << "the other operand ALU 1 takes in is: 0x" << bin2Hex("00000000000000000000000000000100") << endl;
		cout << "the result of ALU 1 is: 0x" << bin2Hex(ALU_1.getOutput()) << endl << endl;
		//cout << curAddress << endl;

		writeFile << endl;
		writeFile << "ALU 1: \naddress PC passed into ALU 1 is: 0x" << curAddress << endl;
		writeFile << "the other operand ALU 1 takes in is: 0x" << bin2Hex("00000000000000000000000000000100") << endl;
		writeFile << "the result of ALU 1 is: 0x" << bin2Hex(ALU_1.getOutput()) << endl << endl;



		//Control
		string opcode = curInstruction.substr(0, 6);
		main_Control.setOpcode(opcode);
		//cout << opcode << endl;
		cout << "Control: \nThe opcode passed to control is: 0x" << bin2Hex("00" + opcode) << endl;
		cout << "RegDst: " << main_Control.getRegDst() << endl;
		cout << "Jump: " << main_Control.getJump() << endl;
		cout << "Branch: " << main_Control.getBranch() << endl;
		cout << "MemRead: " << main_Control.getMemRead() << endl;
		cout << "MemToReg: " << main_Control.getMemToReg() << endl;
		cout << "ALUOp: " << main_Control.getALUOp() << endl;
		cout << "MemWrite: " << main_Control.getMemWrite() << endl;
		cout << "ALUSrc: " << main_Control.getALUSrc() << endl;
		cout << "RegWrite: " << main_Control.getRegWrite() << endl << endl;

		writeFile << "Control: \nThe opcode passed to control is: 0x" << bin2Hex("00" + opcode) << endl;
		writeFile << "RegDst: " << main_Control.getRegDst() << endl;
		writeFile << "Jump: " << main_Control.getJump() << endl;
		writeFile << "Branch: " << main_Control.getBranch() << endl;
		writeFile << "MemRead: " << main_Control.getMemRead() << endl;
		writeFile << "MemToReg: " << main_Control.getMemToReg() << endl;
		writeFile << "ALUOp: " << main_Control.getALUOp() << endl;
		writeFile << "MemWrite: " << main_Control.getMemWrite() << endl;
		writeFile << "ALUSrc: " << main_Control.getALUSrc() << endl;
		writeFile << "RegWrite: " << main_Control.getRegWrite() << endl << endl;


		//MUX 1
		MUX_1.setOperand1(curInstruction.substr(11,5));
		MUX_1.setOperand2(curInstruction.substr(16,5));
		MUX_1.setControl(main_Control.getRegDst());
		MUX_1.execute();
		string MUX_1_output = MUX_1.getOutput();
		cout << "MUX 1: \nThe first operand passed in: 0x" << bin2Hex("000" + curInstruction.substr(11,5)) << endl;
		cout << "The second operand passed in: 0x" << bin2Hex("000" + curInstruction.substr(16,5)) << endl;
		cout << "The control passed to MUX 1 from main control is: " << main_Control.getRegDst() << endl;
		cout << "The output from MUX 1 is: 0x" << bin2Hex("000" + MUX_1_output) << endl << endl;

		writeFile << "MUX 1: \nThe first operand passed in: 0x" << bin2Hex("000" + curInstruction.substr(11,5)) << endl;
		writeFile << "The second operand passed in: 0x" << bin2Hex("000" + curInstruction.substr(16,5)) << endl;
		writeFile << "The control passed to MUX 1 from main control is: " << main_Control.getRegDst() << endl;
		writeFile << "The output from MUX 1 is: 0x" << bin2Hex("000" + MUX_1_output) << endl << endl;


		//register file -- read
		register_File.readRegister1(curInstruction.substr(6,5));
		register_File.readRegister2(curInstruction.substr(11,5));
		register_File.writeToRegister(MUX_1_output);
		register_File.setWriteSignal(main_Control.getRegWrite());
		string registerData1 = register_File.readData1();
		string registerData2 = register_File.readData2();
		cout << "Register File: \nThe first read register number is: 0x" << bin2Hex("000" + curInstruction.substr(6,5)) << endl;
		cout << "The second read register number is: 0x" << bin2Hex("000" + curInstruction.substr(11,5)) << endl;
		cout << "The data read from first register is: 0x" << bin2Hex(registerData1) << endl;
		cout << "The data read from second register is: 0x" << bin2Hex(registerData2) << endl << endl;

		writeFile << "Register File: \nThe first read register number is: 0x" << bin2Hex("000" + curInstruction.substr(6,5)) << endl;
		writeFile << "The second read register number is: 0x" << bin2Hex("000" + curInstruction.substr(11,5)) << endl;
		writeFile << "The data read from first register is: 0x" << bin2Hex(registerData1) << endl;
		writeFile << "The data read from second register is: 0x" << bin2Hex(registerData2) << endl << endl;


		//sign extend
		string extend_Data = sign_Extend.extend(curInstruction.substr(16,16));
		//cout << curInstruction.substr(16,16) << endl;
		cout << "Sign Extend: \nThe input is: 0x" << bin2Hex(curInstruction.substr(16,16)) << endl;
		cout << "The output is: 0x" << bin2Hex(extend_Data) << endl << endl;

		writeFile << "Sign Extend: \nThe input is: 0x" << bin2Hex(curInstruction.substr(16,16)) << endl;
		writeFile << "The output is: 0x" << bin2Hex(extend_Data) << endl << endl;


		//MUX 2
		MUX_2.setOperand1(registerData2);
		MUX_2.setOperand2(extend_Data);
		MUX_2.setControl(main_Control.getALUSrc());
		MUX_2.execute();
		string MUX_2_output = MUX_2.getOutput();
		cout << "MUX 2: \nThe first operand passed in: 0x" << bin2Hex(registerData2) << endl;
		cout << "The second operand passed in: 0x" << bin2Hex(extend_Data) << endl;
		cout << "The control passed to MUX 2 from main control is: " << main_Control.getALUSrc() << endl;
		cout << "The output from MUX 2 is: 0x" << bin2Hex(MUX_2_output) << endl << endl;

		writeFile << "MUX 2: \nThe first operand passed in: 0x" << bin2Hex(registerData2) << endl;
		writeFile << "The second operand passed in: 0x" << bin2Hex(extend_Data) << endl;
		writeFile << "The control passed to MUX 2 from main control is: " << main_Control.getALUSrc() << endl;
		writeFile << "The output from MUX 2 is: 0x" << bin2Hex(MUX_2_output) << endl << endl;


		//ALU Control
		ALU_Control.setALUOp(main_Control.getALUOp()); //Set ALUOp before set instruction!!!
		ALU_Control.setInstruction(curInstruction.substr(26,6));
		int ALUOperation = ALU_Control.getOutput();
		cout << "ALU Control: \nThe instruction received is: 0x" << bin2Hex("00" + curInstruction.substr(26,6)) << endl;
		cout << "The ALUOp received from main control is: " << main_Control.getALUOp() <<endl;
		cout << "The control sending to ALU 3 is: " << ALUOperation << endl << endl;

		writeFile << "ALU Control: \nThe instruction received is: 0x" << bin2Hex("00" + curInstruction.substr(26,6)) << endl;
		writeFile << "The ALUOp received from main control is: " << main_Control.getALUOp() <<endl;
		writeFile << "The control sending to ALU 3 is: " << ALUOperation << endl << endl;


		//ALU 3
		ALU_3.setOperand1(registerData1);
		ALU_3.setOperand2(MUX_2_output);
		ALU_3.setOperation(ALUOperation);
		ALU_3.execute();
		string ALU_3_result = ALU_3.getOutput();
		bool isZero = ALU_3.isEqual();
		cout << "ALU 3:\nOperand 1 is: 0x" << bin2Hex(registerData1) << endl;
		cout << "Operand 2 is: 0x" << bin2Hex(MUX_2_output) << endl;
		cout << "Operation for ALU 3 to perform is: " << ALUOperation << endl;
		cout << "the result of ALU 3 is: 0x" << bin2Hex(ALU_3_result) << endl;
		cout << "The two operand is equal or not: " << isZero << endl << endl;


		writeFile << "ALU 3:\nOperand 1 is: 0x" << bin2Hex(registerData1) << endl;
		writeFile << "Operand 2 is: 0x" << bin2Hex(MUX_2_output) << endl;
		writeFile << "Operation for ALU 3 to perform is: " << ALUOperation << endl;
		writeFile << "the result of ALU 3 is: 0x" << bin2Hex(ALU_3_result) << endl;
		writeFile << "The two operand is equal or not: " << isZero << endl << endl;


		//Data memory
		data_Memory.setAddress(bin2Hex(ALU_3_result));
		//if (main_Control.getMemRead()) {
		//	cout <<  "ATTENTION: " << bin2Hex(ALU_3_result) << endl;
		//}
		data_Memory.setWriteData(registerData2);
		data_Memory.setMemWrite(main_Control.getMemWrite());
		data_Memory.setMemRead(main_Control.getMemRead());
		data_Memory.execute();
		string memory_Data = data_Memory.readData();
		cout << "Data Memory: \nAddress is set to: 0x" << bin2Hex(ALU_3_result) << endl;
		cout << "Data to write is: 0x" << bin2Hex(registerData2) << endl;
		cout << "MemWrite signal received from main control is: " << main_Control.getMemWrite() << endl;
		cout << "MemRead signal received from main control is: " << main_Control.getMemRead() << endl;
		cout << "The data read from data memory is: 0x" << bin2Hex(memory_Data) << endl << endl;

		writeFile << "Data Memory: \nAddress is set to: 0x" << bin2Hex(ALU_3_result) << endl;
		writeFile << "Data to write is: 0x" << bin2Hex(registerData2) << endl;
		writeFile << "MemWrite signal received from main control is: " << main_Control.getMemWrite() << endl;
		writeFile << "MemRead signal received from main control is: " << main_Control.getMemRead() << endl;
		writeFile << "The data read from data memory is: 0x" << bin2Hex(memory_Data) << endl << endl;

		//MUX 3
		MUX_3.setOperand1(ALU_3_result);
		MUX_3.setOperand2(memory_Data);
		MUX_3.setControl(main_Control.getMemToReg());
		MUX_3.execute();
		string MUX_3_output = MUX_3.getOutput();
		cout << "MUX 3: \nThe first operand passed in: 0x" << bin2Hex(ALU_3_result) << endl;
		cout << "The second operand passed in: 0x" << bin2Hex(memory_Data) << endl;
		cout << "The control passed to MUX 3 from main control is: " << main_Control.getMemToReg() << endl;
		cout << "The output from MUX 3 is: 0x" << bin2Hex(MUX_3_output) << endl << endl;


		writeFile << "MUX 3: \nThe first operand passed in: 0x" << bin2Hex(ALU_3_result) << endl;
		writeFile << "The second operand passed in: 0x" << bin2Hex(memory_Data) << endl;
		writeFile << "The control passed to MUX 3 from main control is: " << main_Control.getMemToReg() << endl;
		writeFile << "The output from MUX 3 is: 0x" << bin2Hex(MUX_3_output) << endl << endl;


		//special case of slt
		if (opcode == "000000" && curInstruction.substr(26,6) == "101010") {
			if (MUX_3_output.substr(0,1) == "1") {
				MUX_3_output = "00000000000000000000000000000001";
			} else {
				MUX_3_output = "00000000000000000000000000000000";
			}

			if (registerData1.substr(0,1) == "0" && MUX_2_output.substr(0,1) == "1") {
				MUX_3_output = "00000000000000000000000000000000";
			}
		}

		//writeback
		register_File.writeData(MUX_3_output);
		cout << "Writeback: \nThe RegWrite signal is: " << main_Control.getRegWrite() << endl;
		cout << "The data to write to register is: 0x" << bin2Hex(MUX_3_output) << endl;
		cout << "The register to write to is: 0x" << bin2Hex("000" + MUX_1_output) << endl << endl;

		writeFile << "Writeback: \nThe RegWrite signal is: " << main_Control.getRegWrite() << endl;
		writeFile << "The data to write to register is: 0x" << bin2Hex(MUX_3_output) << endl;
		writeFile << "The register to write to is: 0x" << bin2Hex("000" + MUX_1_output) << endl << endl;

		//shift left 1
		string jump_address = shift_Left_1.shift(curInstruction.substr(6,26));
		cout << "Shift left 1: \nThe instruction passed in is: 0x" << bin2Hex("00" + curInstruction.substr(6,26)) << endl;
		cout << "Shift result is: 0x" << bin2Hex(jump_address) << endl;

		writeFile << "Shift left 1: \nThe instruction passed in is: 0x" << bin2Hex("00" + curInstruction.substr(6,26)) << endl;
		writeFile << "Shift result is: 0x" << bin2Hex(jump_address) << endl;
		//cout << PC_plus_4 << endl;
		jump_address = hex2Bin(PC_plus_4).substr(0,4) + jump_address;
		jump_address = bin2Hex(jump_address);
		//cout << jump_address << endl;
		cout << "The jump address is: 0x" << jump_address << endl << endl;

		writeFile << "The jump address is: 0x" << jump_address << endl << endl;

		//shift left 2
		string branch_address = shift_Left_2.shift(extend_Data);
		cout << "Shift left 2: \nThe instruction passed in is: 0x" << bin2Hex(extend_Data) << endl;
		cout << "Shift result is: 0x" << bin2Hex(branch_address) << endl << endl;


		writeFile << "Shift left 2: \nThe instruction passed in is: 0x" << bin2Hex(extend_Data) << endl;
		writeFile << "Shift result is: 0x" << bin2Hex(branch_address) << endl << endl;

		//ALU 2
		ALU_2.setOperand1(hex2Bin(PC_plus_4));
		ALU_2.setOperand2(branch_address);
		ALU_2.setOperation(1);
		ALU_2.execute();
		string ALU_2_result = ALU_2.getOutput();
		cout << "ALU 2:\nOperand 1 is: 0x" << PC_plus_4 << endl;
		cout << "Operand 2 is: 0x" << bin2Hex(branch_address) << endl;
		cout << "the result of ALU 2 is: 0x" << bin2Hex(ALU_2_result) << endl << endl;

		writeFile << "ALU 2:\nOperand 1 is: 0x" << PC_plus_4 << endl;
		writeFile << "Operand 2 is: 0x" << bin2Hex(branch_address) << endl;
		writeFile << "the result of ALU 2 is: 0x" << bin2Hex(ALU_2_result) << endl << endl;
		branch_address = bin2Hex(ALU_2_result);

		MUX_5.setOperand1(PC_plus_4);
		MUX_5.setOperand2(branch_address);
		int MUX_5_Control;
		if (isZero && main_Control.getBranch()) {
			MUX_5_Control = 1;
		} else {
			MUX_5_Control = 0;
		}
		MUX_5.setControl(MUX_5_Control);
		MUX_5.execute();
		string MUX_5_output = MUX_5.getOutput();
		cout << "MUX 5: \nThe first operand passed in: 0x" << PC_plus_4 << endl;
		cout << "The second operand passed in: 0x" << branch_address << endl;
		cout << "The control passed to MUX 5 from main control is: " << MUX_5_Control << endl;
		cout << "The output from MUX 5 is: 0x" << MUX_5_output << endl << endl;


		writeFile << "MUX 5: \nThe first operand passed in: 0x" << PC_plus_4 << endl;
		writeFile << "The second operand passed in: 0x" << branch_address << endl;
		writeFile << "The control passed to MUX 5 from main control is: " << MUX_5_Control << endl;
		writeFile << "The output from MUX 5 is: 0x" << MUX_5_output << endl << endl;

		MUX_4.setOperand1(MUX_5_output);
		MUX_4.setOperand2(jump_address);
		MUX_4.setControl(main_Control.getJump());
		MUX_4.execute();
		string nextAddress = MUX_4.getOutput();
		cout << "MUX 4: \nThe first operand passed in: 0x" << MUX_5_output << endl;
		cout << "The second operand passed in: 0x" << jump_address << endl;
		cout << "The control passed to MUX 4 from main control is: " << main_Control.getJump() << endl;
		cout << "The output from MUX 4 is: 0x" << nextAddress << endl << endl;


		writeFile << "MUX 4: \nThe first operand passed in: 0x" << MUX_5_output << endl;
		writeFile << "The second operand passed in: 0x" << jump_address << endl;
		writeFile << "The control passed to MUX 4 from main control is: " << main_Control.getJump() << endl;
		writeFile << "The output from MUX 4 is: 0x" << nextAddress << endl << endl;





		//update address to PC and fetch next instruction
		curAddress = nextAddress;
		instruction_Memory.readAddress(curAddress);
		curInstruction = instruction_Memory.getInstruction();
		curOriginal = instruction_Memory.getOriginal();

		cout << endl << endl;
		writeFile << endl << endl;



		//data_Memory.print();


		//curInstruction = "";
	}

	cout << "------------------end------------------" << endl;
	writeFile << "------------------end------------------" << endl;
	if (printMemory) {
		register_File.printRegisterFile();
		cout << endl;
		data_Memory.print();
		cout << endl;
		instruction_Memory.print();


    	writeFile << "Printing Registers" << endl;
    	map<int, string> registers = register_File.getMap();
  		for (int i = 0; i < 32; i++) {
   			writeFile << "Register["  << i << "] = " << "\t 0x"<< bin2Hex(registers[i]) << endl;
  		}

  		writeFile << endl << "Memory Contents:" << endl;
		map<string,string> dataMemoryMap = data_Memory.getMap();
  		map<string,string>::iterator it2;
  		for(it2 = dataMemoryMap.begin(); it2 != dataMemoryMap.end(); it2++){
			string t = it2->second;
    		writeFile << "address:[0x" << it2->first << "] = 0x" << bin2Hex(t) << endl;
    	}
    	writeFile << endl;

    	writeFile << "Instruction Memory Contents:" << endl;
    	map<string, string> myInstruction = instruction_Memory.getMap();
  		map<string,string>::iterator it3;
  		for(it3 = myInstruction.begin(); it3 != myInstruction.end(); it3++){
			string t = it3->second;
    		writeFile << "address:[0x" << it3->first << "] = 0x" << bin2Hex(t) << endl;
  		}
  		writeFile << endl;
	}
	writeFile.close();
	//cout << "writeToFile" << endl;
}


















string Simulate::hex2Bin(string input) {
  string result;
  for (unsigned int i = 0; i < input.length(); i++) {
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
	for(unsigned int i = 0; i < input.length(); i = i+4)
	{
		endresult += getHexCharacter(input.substr(i,4));
	}
	return endresult;
}

