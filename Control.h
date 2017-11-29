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
    string RegDst; //Bool? int? Determines if a Register rd is used?
    string RegWrite; // Determines if Register is written 
    string ALUSrc; // Determines value going into ALU
    string ALUOp; // Determines operation of ALU
    string MemWrite; // Determines if Memory is written to
    string MemRead; // Determines if memory is read
    string MemToReg; // Determines if Memory data is written to a register

  public:
    ///Constructors
    // Default Constructor
    Control();

    // Destructor
    ~Control();

    ///Functions
    // Parse Instruction?
    //
    //

    
}
#endif


