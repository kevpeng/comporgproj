/* Control Unit
 */
#ifndef __CONTROL_H__
#define __CONTROL_H__

#include "RegisterFile.h"
#include "ALU.h"
#include "DataMemory.h"

class Control {
  private:
    ///Private Variables
    // Input
    string opcode; //six bit instruction opcode from Instruction Memory
    string func; //six bit instruction func field from Instruction Memory
    string zero; //zero output from ALU

    // Output
    string RegDst; //Bool? int? Determines if a Register rd is used. Goes to Mux
    string RegWrite; // Determines if Register is written. Goes to Reg File
    string ALUSrc; // Determines value going into ALU. Goes to ALU Mux
    string ALUOp; // Determines operation of ALU. Goes to ALU
    string MemWrite; // Determines if Memory is written to. Goes to DataMemory
    string MemRead; // Determines if memory is read. Goes to Data Memory?
    string MemToReg; // Determines if Memory data is written to a register. Mux

  public:
    ///Constructors
    // Default Constructor
    Control();
    // Constructor TODO do we need this?
    Control(string opcode, string func, string zero);

    // Destructor
    ~Control();

    ///Functions
    // Reads in instruction, initializes input variables
    void readInstruction(string inst);
    // Parses instruction, initializes output variables
    void parseInstruction();
    // Clears instruction, wipes private variables
    void clearInstruction();

    
}
#endif


