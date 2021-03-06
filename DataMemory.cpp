/*
 * Author: Kevin Peng
 *
 * This class simulated the Data Memory of a processor. 
 * bool values, needToRead and needToWrite can be set from outside, 
 * and will determine if it's necessary to store things in memory or not. 
 */
#include "DataMemory.h"

// constructor for DataMemory
DataMemory::DataMemory() {
  dataMemoryMap = map<string, string> ();
}

// constructor from file 
DataMemory::DataMemory(string filename) { 
  dataMemoryMap = map<string, string>();
  setFromFile(filename);
}

// reads in file of strings. processes it and puts it into the map
void DataMemory::setFromFile(string filename) { 

  MemParser parser = MemParser(filename);
  dataMemoryMap = parser.getMemory();
}

void DataMemory::execute() {
  if (needToWrite) {
    dataMemoryMap[currentAddress] = currentData;
  }
}

string DataMemory::readData() {
  if (needToRead) {
    return dataMemoryMap[currentAddress];
  } else {
    return "";
  }
}

void DataMemory::print()  {
  cout << "Memory Contents:" << endl;
  map<string,string>::iterator it;
  for(it = dataMemoryMap.begin(); it != dataMemoryMap.end(); it++){
    string t = it->second;
    cout << "address:[0x" << it->first << "] = 0x" << bin2Hex(t) << endl;
  }

  cout << endl;
}

char DataMemory::getHexCharacter(string str) {
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

string DataMemory::bin2Hex(string s) {
  string endresult = "";
  for(unsigned int i = 0; i < s.length(); i = i+4)
  {
    endresult += getHexCharacter(s.substr(i,4));
  }
  return endresult;
}
