/* Author: Are Oelsner
 * RegisterFile.cpp
 */
#include "RegisterFile.h"
#include <fstream>

///Constructors
// Default Constructor
RegisterFile::
RegisterFile() {
  data1 = -1;
  data2 = -1;
  writeRegister = -1;
  
}

// File Constructor
RegisterFile::
RegisterFile(string filename) { //register1.memory
  RegParser parser = RegParser(filename); // Uses Register Parser from RegParser file
  registers = parser.getRegisters();
  data1 = -1;
  data2 = -1;
  writeRegister = -1;
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
  //delete RegisterFile;
}

 // Read Register 1 -- rs
void RegisterFile::readRegister1(string r1) {
  data1 = stoi (r1,nullptr,2);
}

// Read Register 2 -- rt
void RegisterFile::readRegister2(string r2) {
  data2 = stoi (r2, nullptr, 2);
}

void RegisterFile::writeData(string value) {
  if (regWrite) {
    registers.at(writeRegister) = value;
  }
}


// Function that outputs contents of Registers
void
RegisterFile::
printRegisterFile() {
  cout << "Printing Registers" << endl;

  for (int i = 0; i < 32; i++) {
    cout << "Register["  << i << "] = " << "\t"<< registers[i] << endl;
  }
}

