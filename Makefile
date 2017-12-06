# Makefile Variables
CC = g++     
LD = $(CC)
CCFLAGS = -Wall -Wno-deprecated --std=c++11 -g -c   
LDFLAGS = -Wall --std=c++11 -Wno-deprecated -g
OBJS = main.o Simulate.o InstructionMemory.o InstructionParser.o ConfigFileParser.o DataMemory.o ShiftLeft.o SignExtend.o ALU.o MUX.o ALUControl.o Control.o RegParser.o MemParser.o RegisterFile.o PC.o
SIMDEPS = Simulate.cpp ConfigFileParser.cpp InstructionMemory.cpp DataMemory.cpp InstructionParser.cpp MemParser.cpp ALU.cpp MUX.cpp PC.cpp RegisterFile.cpp RegParser.cpp ShiftLeft.cpp SignExtend.cpp ALUControl.cpp Control.cpp
################################################################################

#compiles main from .o files
main: $(OBJS) 
	$(LD) $(LDFLAGS) $(OBJS) -o $@

r: #runs main
	./main input.config

clean: #removes executable
	rm main

reallyclean: clean #cleans and removes all .o files
	rm *.o

old: #original make command. recompiles after each change
	g++ --std=c++11 -Wall main.cpp Simulate.cpp InstructionMemory.cpp InstructionParser.cpp ConfigFileParser.cpp DataMemory.cpp ShiftLeft.cpp SignExtend.cpp ALU.cpp MUX.cpp ALUControl.cpp Control.cpp RegParser.cpp MemParser.cpp RegisterFile.cpp PC.cpp -o main


################################################################################
# O Compilers -- reduces recompilation
################################################################################
main.o: main.cpp Simulate.cpp
	$(CC) $(CCFLAGS) $<

Simulate.o: $(SIMDEPS)
	$(CC) $(CCFLAGS) Simulate.cpp 

InstructionMemory.o: InstructionMemory.cpp InstructionParser.h
	$(CC) $(CCFLAGS) $<

InstructionParser.o: InstructionParser.cpp 
	$(CC) $(CCFLAGS) $<

ConfigFileParser.o: ConfigFileParser.cpp 
	$(CC) $(CCFLAGS) $<
	
DataMemory.o: DataMemory.cpp MemParser.cpp
	$(CC) $(CCFLAGS) $<

ShiftLeft.o: ShiftLeft.cpp 
	$(CC) $(CCFLAGS) $<

SignExtend.o: SignExtend.cpp 
	$(CC) $(CCFLAGS) $<
	
ALU.o: ALU.cpp 
	$(CC) $(CCFLAGS) $<

MUX.o: MUX.cpp 
	$(CC) $(CCFLAGS) $<

ALUControl.o: ALUControl.cpp 
	$(CC) $(CCFLAGS) $<

Control.o: Control.cpp 
	$(CC) $(CCFLAGS) $<

RegParser.o: RegParser.cpp 
	$(CC) $(CCFLAGS) $<

MemParser.o: MemParser.cpp 
	$(CC) $(CCFLAGS) $<

RegisterFile.o: RegisterFile.cpp RegParser.cpp
	$(CC) $(CCFLAGS) $<

PC.o: PC.cpp ALU.cpp
	$(CC) $(CCFLAGS) $<
