/* Author: Are Oelsner
 * Register File
 * Reads in input registers and or immediate, outputs the relevant data to AL
 */
#ifndef __REGISTERFILE_H__
#define __REGISTERFILE_H__

#include"RegisterTable.h"

class RegisterFile {
  protected:
    RegisterTable::RegisterTable registerTable;

  public:
    ///Constructors
    //Default Constructor
    RegisterFile();

    ///Functions
    //Read Register 1 -- rs
    RegisterTable::Register readRegister1(RegisterTable::Register r1);
    //Read Register 2 -- rt
    RegisterTable::Register readRegister2(RegisterTable::Register r2);
    //Read Data 1 -- goes to ALU
    
    //Read Data 2 -- goes to Mux or  Write data of Data memory

    //Write Register -- received from Mux  of rd or rt
    void writeRegister(RegisterTable::Register rd, string binaryValue);
    //Write Data
    void writeData(RegisterTable::Register);

};

#endif
