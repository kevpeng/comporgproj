/*
 *  Simulate class
 *
 *  Author: Tianchang Yang
 *  Date: 11/30/17
 */

#ifndef __SIMULATE_H__
#define __SIMULATE_H__

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
    ///Constructors
    //Default constructor
    Simulate(string filename);

    ///Functions
    void run();

  private:

    ///Private Variables
    string myConfigFile;   // Input Configuration file
    bool batch;            // sets single_step or batch mode
    bool printMemory;      // Determines if memory is printed
    bool writeToFile;      // Determines if output should be written to a file 
    string outputFile;     // Name of output file

    ///Class Objects
    InstructionMemory instruction_Memory; // Instruction Memory instance
    DataMemory data_Memory; // Data Memory instance
    ShiftLeft shift_Left_1; // Shift left unit from Instruction memory
    ShiftLeft shift_Left_2; // Shift left unit from sign extend unit
    SignExtend sign_Extend; // Sign extend unit from Instruction memory
    ALU ALU_1;              // ALU unit from PC, increments PC
    ALU ALU_2;              // ALU unit from Shift Left 2 and ALU1. Branches
    ALU ALU_3;              // Main ALU unit, handles arithmetic operations
    MUX MUX_1;              // Instruction Mux determines write register input
    MUX MUX_2;              // Determines input into ALU3 based on ALUSrc signal
    MUX MUX_3;              // MemtoReg signal determines ALU3 result v. dataMem
    MUX MUX_4;              // Jump signal determines branch/jump
    MUX MUX_5;              // Branch signal + ALU3 zero set branch to Mux4
    ALUControl ALU_Control; // ALU control takes ALUOp signal and sets ALU3 op
    Control main_Control;   // Control parses Opcode and emits control signals
    RegisterFile register_File; // Registerfile stores register states 
    PC program_Counter;     // PC holds address of instruction 

    ///Private Functions
    // Converter from hexadecimal to binary 
    string hex2Bin(string input);
    // Converter from binary to hexadecimal
    string bin2Hex(string input);
    // Helper function that finds hex character
    char getHexCharacter(string str);

};

#endif
