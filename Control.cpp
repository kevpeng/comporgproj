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
  func = inst.substr(6,6);
  zero = inst.substr(12, 1);
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
  func     = NULL;
  zero     = NULL;
          
  RegDst   = NULL;
  RegWrite = NULL;
  ALUSrc   = NULL;
  ALUOp    = NULL;
  MemWrite = NULL;
  MemRead  = NULL;
  MemToReg = NULL;
}

void 
Control::
sendSignals() {
  ///Calls functions in
  // RegisterMux
  // RegisterFile
  // ALUMux
  // ALU
  // DataMemory
  // DataMemory
  // Mux for data memory written to register
  ///To emit control signals
}
