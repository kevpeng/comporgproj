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
    string opcode; //six bit instruction opcode
    string func; //six bit instruction func field
    string zero; //zero output from ALU

    // Output
    string RegDst; //Bool? int?
    string RegWrite;
    string ALUSrc;
    string ALUOp;
    string MemWrite;
    string MemRead;
    string MemToReg;

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


