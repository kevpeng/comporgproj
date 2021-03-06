/*
 *  Author: Tianchang Yang
 *  Date: 11/30/17
 */

#include "InstructionMemory.h"

//Default constructor
InstructionMemory::InstructionMemory() {
}

//Constructor
InstructionMemory::InstructionMemory(string filename) {
  InstructionParser parser = InstructionParser(filename);
  myInstruction = parser.getInstruction();
  myOriginal = parser.getOriginal();
}

void InstructionMemory::readAddress(string address){
  myAddress = address;
}

string InstructionMemory::getInstruction(){
  return myInstruction[myAddress];
}

string InstructionMemory::getOriginal(){
  return myOriginal[myAddress];
}

void InstructionMemory::print() 
{
  cout << "Instruction Memory Contents:" << endl;
  map<string,string>::iterator it;
  for(it = myInstruction.begin(); it != myInstruction.end(); it++){
    string t = it->second;
    cout << "address:[0x" << it->first << "] = 0x" << InstructionMemory::bin2Hex(t) << endl;
  }
  cout << endl;
}

char InstructionMemory::getHexCharacter(string str)
{
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

string InstructionMemory::bin2Hex(string s)
{
  string endresult = "";
  for(unsigned int i = 0; i < s.length(); i = i+4)
  {
    endresult += getHexCharacter(s.substr(i,4));
  }
  return endresult;
}
