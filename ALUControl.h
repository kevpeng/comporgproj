/*
 *  ALU control class
 *
 *  Author: Tianchang Yang
 *  Date: 11/30/17
 */

#ifndef __ALUCONTROL_H__
#define __ALUCONTROL_H__

#include <string>

using namespace std;

class ALUControl {

  public:
    ///Constructors
    //Default constructor
    ALUControl();

    ///Functions
    // Sets ALU Operation
    void setALUOp(int op);
    // Sets Instruction
    void setInstruction(string instruction);


    ///Getters
    // Returns private variable for operation, myOp
    inline int getOutput() { return myOp; }


  private:
    ///Private Variables
    // Stores operation type
    int myOp;

};

#endif
