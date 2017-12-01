/* Control Unit
 */
#include "Control.h"

Control::
Control() {
}

void
Control::
readInstruction(string inst) {
  opcode = inst.substr(0,6);
  parseInstruction();
}

void
Control::
parseInstruction() {
  //use parser from lab 5 to parse instruction and assign values to output
  //variables
}

void
Control::
clearInstruction() {
  opcode   = NULL;
          
  RegDst   = NULL;
  RegWrite = NULL;
  ALUSrc   = NULL;
  ALUOp    = NULL;
  MemWrite = NULL;
  MemRead  = NULL;
  MemToReg = NULL;
}

