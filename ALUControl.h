/*
 *  ALU control class
 *
 *  Author: Tianchang Yang
 *  Date: 11/30/17
 */
#ifndef _ALUCONTROL_H_
#define _ALUCONTROL_H_

#include <string>

using namespace std;

class ALUControl {
  public:
    ///Constructors
    //Default constructor
    ALUControl();

    ///Functions
    void setALUOp(int op);

    void setInstruction(string instruction);

    int getOutput() { return myOp; }


  private:
    ///Private Variables
    int myOp;
};

#endif
