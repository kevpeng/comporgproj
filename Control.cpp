/* Control Unit
 */
#include "Control.h"

// Default Constructor
Control::Control() {
  myRegDst = -1;
  myJump = -1;
  myBranch = false;
  myMemRead = false; 
  myMemToReg = -1; 
  myALUOp = -1; 
  myMemWrite = false; 
  myALUSrc = -1;
  myRegWrite = false;
}

// Parses input instruction to set private variables
void Control::setOpcode(string inst) {
  myOpcode = inst;

  if (inst == "000000") { //R-type
    myRegDst = 1;
    myJump = 0;
    myBranch = false;
    myMemRead = false;
    myMemToReg = 0;
    myALUOp = -1;
    myMemWrite = false;
    myALUSrc = 0;
    myRegWrite = true;
  } else if (inst == "001000") { //addi
    myRegDst = 0;
    myJump = 0;
    myBranch = false;
    myMemRead = false;
    myMemToReg = 0;
    myALUOp = 1; //add
    myMemWrite = false;
    myALUSrc = 1;
    myRegWrite = true;
  } else if (inst == "100011") { //lw
    myRegDst = 0;
    myJump = 0;
    myBranch = false;
    myMemRead = true;
    myMemToReg = 1;
    myALUOp = 1; //add
    myMemWrite = false;
    myALUSrc = 1;
    myRegWrite = true;
  } else if (inst == "101011") { //sw
    myRegDst = 0; //doesn't matter
    myJump = 0;
    myBranch = false;
    myMemRead = false;
    myMemToReg = 0;
    myALUOp = 1; //add
    myMemWrite = true;
    myALUSrc = 1;
    myRegWrite = false;
  } else if (inst == "000100") { //beq
    myRegDst = 0; //doesn't matter
    myJump = 0;
    myBranch = true;
    myMemRead = false;
    myMemToReg = 0;
    myALUOp = 0; //compare
    myMemWrite = false;
    myALUSrc = 0;
    myRegWrite = false;
  } else if (inst == "000010") { //j
    myRegDst = 0; //doesn't matter
    myJump = 1;
    //all don't matter
    myBranch = false;
    myMemRead = false;
    myMemToReg = 0;
    myALUOp = 0;
    myMemWrite = false;
    myALUSrc = 0;
    myRegWrite = false;
  }
}
