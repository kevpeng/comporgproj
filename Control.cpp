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
}
