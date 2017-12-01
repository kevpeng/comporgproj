/* Control Unit
 */
#ifndef __CONTROL_H__
#define __CONTROL_H__

#include <string>

using namespace std;

class Control {
  private:
    ///Private Variables
    // Input
    string myOpcode; //six bit instruction opcode from Instruction Memory

    // Output
    int myRegDst; //Determines if a Register rd is used. Goes to Mux
    int myJump;
    bool myBranch;
    bool myMemRead; // Determines if memory is read. Goes to Data Memory?
    int myMemToReg; // Determines if Memory data is written to a register. Mux
    int myALUOp; // Determines operation of ALU. Goes to ALU
    bool myMemWrite; // Determines if Memory is written to. Goes to DataMemory
    int myALUSrc; // Determines value going into ALU. Goes to ALU Mux
    bool myRegWrite; // Determines if Register is written. Goes to Reg File
    

  public:
    ///Constructors
    // Default Constructor
    Control();

    // Destructor
    //~Control();

    
    void setOpcode(string inst);

    int getRegDst() { return myRegDst; }
    int getJump() { return myJump; }
    bool getBranch() { return myBranch; }
    bool getMemRead() { return myMemRead; }
    int getMemToReg() { return myMemToReg; }
    int getALUOp() { return myALUOp; }
    bool getMemWrite() { return myMemWrite; }
    int getALUSrc() { return myALUSrc; }
    bool getRegWrite() { return myRegWrite; }
    
};
#endif


