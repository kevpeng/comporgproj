/* 
 * RegisterFile.cpp
 */
#include <fstream>

#include "RegisterFile.h"

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
}

// Destructor
RegisterFile::
~RegisterFile() {
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
    registers[writeRegister] = value;
  }
}

// Function that outputs contents of Registers
void
RegisterFile::
printRegisterFile() {
  cout << "Printing Registers" << endl;

  for (int i = 0; i < 32; i++) {
    cout << "Register["  << i << "] = " << "\t 0x"<< bin2Hex(registers[i]) << endl;
  }
}

char RegisterFile::getHexCharacter(string str) {
  if(str.compare("1111") == 0) return 'F';
  else if(str.compare("1110") == 0) return 'E';
  else if(str.compare("1101")== 0) return 'D';
  else if(str.compare("1100")== 0) return 'C';
  else if(str.compare("1011")== 0) return 'B';
  else if(str.compare("1010")== 0) return 'A';
  else if(str.compare("1001")== 0) return '9';
  else if(str.compare("1000")== 0) return '8';
  else if(str.compare("0111")== 0) return '7';
  else if(str.compare("0110")== 0) return '6';
  else if(str.compare("0101")== 0) return '5';
  else if(str.compare("0100")== 0) return '4';
  else if(str.compare("0011")== 0) return '3';
  else if(str.compare("0010")== 0) return '2';
  else if(str.compare("0001")== 0) return '1';
  else if(str.compare("0000")== 0) return '0';
  return ' ';
}

string RegisterFile::bin2Hex(string s) {
  string endresult = "";
  for(unsigned int i = 0; i < s.length(); i = i+4)
  {
    endresult += getHexCharacter(s.substr(i,4));
  }
  return endresult;
}
