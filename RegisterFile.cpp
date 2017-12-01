/* Author: Are Oelsner
 * RegisterFile.cpp
 */
#include "RegisterFile.h"
#include <fstream>

///Constructors
// Default Constructor
RegisterFile::
RegisterFile() {
  for(int i = 0; i < 32; i++) {
    registers.push_back(i, NULL);
  }
}

// File Constructor
RegisterFile::
RegisterFile(string filename) { //register1.memory
  RegParser::RegParser parser(filename); // Uses Register Parser from RegParser file
  registers = RegParser::parser.getRegisters();
//  fstream file;
//  file.open(filename);
//  if(file.bad()) { cout << "Error reading file" << endl;}
//  else {
//    string line;
//    while(getLine(file, line)) {
//      string regNum[2];
//      string hexVal[10];
//      //hexVal += "0x"; //Adds Hex beginning
//      bool data = false;
//
//      for(int i = 0; i < line.length(); i++) {
//        if(line[i] == ':') {
//          data = true;
//          continue;
//        }
//        if(!data)
//          regNum += line[i]; //Adds Register number
//        if(data) 
//          hexVal += line[i]; //Appends hex digits
//      }
//      if(hexVal[1] != 'x')
//        hexVal.insert(0, "0x");
//      registers.push_back((int)regNum, hexVal);
//    }
//  }
}

// Destructor
RegisterFile::
~RegisterFile() {
  delete RegisterFile;
}

///Functions
// Read Register 1 -- rs
string 
RegisterFile::
readRegister1(int r1) {data1 = r1;}

// Read Register 2 -- rt
string 
RegisterFile::
readRegister2(int r2) {data2 = r2;}

// Read Data 1 -- goes to ALU
string 
RegisterFile::
readData1() {return registers.at(data1);}

// Read Data 2 -- goes to Mux or  Write data of Data memory
string 
RegisterFile::
readData2() {return registers.at(data2);}

// Write Register -- received from Mux  of rd or rt. Depends on Contro signal
void 
RegisterFile::
writeToRegister(int rd) {writeRegister = rd;}

// Write Data -- actually writes data to the register specified by
// writeToRegister
void 
RegisterFile::
writeData(string value) {registers.at(writeRegister) = value;}

// Function that outputs contents of Registers
void
RegisterFile::
printRegisterFile() {
  cout << "Printing Registers" << endl;
  map<int,string>::iterator it;
  for(auto it : registers.begin()) {
    cout << "Register[" << it->first << "] = " << it->second << endl;
  }
}

