/* Author: Are Oelsner
 * Register File 
 */
#include "RegisterFile.h"
#include <fstream>

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
  fstream file;
  file.open(filename);
  if(file.bad()) { cout << "Error reading file" << endl;}
  else {
    string line;
    while(getLine(file, line)) {
      string regNum[2];
      string hexVal[10];
      hexVal += "0x"; //Adds Hex beginning
      bool data = false;

      for(int i = 0; i < line.length(); i++) {
        if(line[i] == ':') {
          data = true;
          continue;
        }
        if(!data)
          regNum += line[i]; //Adds Register number
        if(data) 
          hexVal += line[i]; //Appends hex digits
      }
      registers.push_back((int)regNum, hexVal);
    }
  }
}

// Print Registers
void
RegisterFile::
printRegisterFile() {
  cout << "Printing Registers" << endl;
  unordered_map<int,string>::iterator it;
  for(auto it : registers.begin()) {
    cout << "Register[" << it->first << "] = " << it->second << endl;
  }

}

