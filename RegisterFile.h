/* 
 * RegisterFile.h
 * Reads in input registers and or immediate, outputs the relevant data to AL
 *
 * A state element that consists of a set of registers that can be read and
 * written by supplying a register number to be accessed
 * TB pg. 252-3
 */
#ifndef __REGISTERFILE_H__
#define __REGISTERFILE_H__

#include <map>
#include <string>

#include "RegParser.h"

using namespace std;

class RegisterFile {
  private:
    ///Private Variables
    // Registers
    map<int,string> registers;

    // Use variables
    int data1; // register number of rs
    int data2; // register number of rt
    int writeRegister; // register number of register to be written

    bool regWrite; //Input from Control that determines if a register is written

    ///Private Helper Methods
    // helper methods to get hex string
    char getHexCharacter(string str);
    string bin2Hex(string s);



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
    void readRegister1(string r1);
    // Read Register 2 -- rt
    void readRegister2(string r2);
    // Read Data 1 -- goes to ALU
    string readData1() {return registers.at(data1);}
    // Read Data 2 -- goes to Mux or  Write data of Data memory
    string readData2() {return registers.at(data2);}

    // Write Register -- received from Mux  of rd or rt. Depends on Control
    // signal TODO
    void writeToRegister(string rd) {writeRegister = stoi (rd,nullptr,2);}
    // Write Data -- writes to the register specified by writeToRegister
    void writeData(string value);

    void setWriteSignal(bool signal) { regWrite = signal; }

    // Function that outputs contents of Registers
    void printRegisterFile();

    map <int, string> getMap() { return registers; }
};

#endif
