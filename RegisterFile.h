/* Author: Are Oelsner
 * Register File
 * Reads in input registers and or immediate, outputs the relevant data to AL
 *
 * A state element that consists of a set of registers that can be read and
 * written by supplying a register number to be accessed
 * TB pg. 252-3
 */
#ifndef __REGISTERFILE_H__
#define __REGISTERFILE_H__

#include<unordered_map>

class RegisterFile {
  protected:
    typedef unordered_map<int, string> registers;

    int data1; // register number of rs
    int data2; // register number of rt
    int writeRegister; // register number of register to be written

    bool RegWrite; //Input from Control that determines if a register is written

  public:
    ///Constructors
    // Default Constructor
    RegisterFile();
    // File Constructor
    RegisterFile(string filename); //register1.memory

    // Destructor
    ~RegisterFile();

    ///Functions
    // Read Register 1 -- rs
    inline string readRegister1(int r1) {data1 = r1;}
    // Read Register 2 -- rt
    inline string readRegister2(int r2) {data2 = r2;}
    // Read Data 1 -- goes to ALU
    inline string readData1() {return registers.at(data1);}
    // Read Data 2 -- goes to Mux or  Write data of Data memory
    inline string readData2() {return registers.at(data2);}

    // Write Register -- received from Mux  of rd or rt. Depends on Control
    // signal TODO
    //void writeRegister(RegisterTable::Register rd, string hexValue);
    //inline void writeRegister(int rd, string value) {registers.at(rd) = value;}
    inline void writeRegister(int rd) {writeRegister = rd;}
    // Write Data
    //void writeData(string hexValue, string address);
    inline void writeData(string value) {registers.at(writeRegister) = value;}

    // Function that outputs contents of Registers TODO
    void printRegisterFile();

};

#endif
