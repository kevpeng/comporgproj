default: 
	g++ --std=c++11 -Wall main.cpp Simulate.cpp InstructionMemory.cpp InstructionParser.cpp ConfigFileParser.cpp DataMemory.cpp ShiftLeft.cpp SignExtend.cpp ALU.cpp MUX.cpp ALUControl.cpp Control.cpp RegParser.cpp MemParser.cpp RegisterFile.cpp PC.cpp -o main

#o: 
#	vim -p RegisterFile.cpp Control.cpp Simulate.cpp main.cpp

#clean:
#	rm main
