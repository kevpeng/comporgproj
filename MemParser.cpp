#include "MemParser.h"
#include<iostream>

// Default constructor, parse memory data into map data structure
MemParser::MemParser(string filename) {

  ifstream in;
  in.open(filename.c_str());
  if(in.bad()){

  }
  else{
    string line;
    while(getline(in, line)){
      if (!isEmpty(line) && !isComment(line)) { //not whitespaces or comments
        parseLine(line);
      }
    }
  }
}

// Helper mathod to determine if a string contains only whitespaces
bool MemParser::isEmpty(string s) {
  bool result = true;
  char c;
  for(unsigned int i = 0; i < s.length(); i++) {
    c = s[i]; 
    if (!isspace(c)) {
      result = false;
    }
  }
  return result;
}

// Helper method to determine if a string is a comment 
// (ignnoring whitespaces, starts with a "#")
bool MemParser::isComment(string s) {
  char c;
  for(unsigned int i = 0; i < s.length(); i++) {
    c = s[i]; 
    if (!isspace(c)) {
      if (c == '#') {
        return true;
      } else {
        return false;
      }
    }
  }
  return false;
}

// Given the line is neither empty nor a comment, and it is 
// correctly formatted, parse the line into memory map and its BINARY values.
void MemParser::parseLine(string s){
  unsigned int index = s.find(':');
  if (index != string::npos){ // found a ':'
    string str0 = s.substr(0, index); // memory address
    string str1 = s.substr(index + 1, s.length()); //value

    // erase possible whitespaces
    str0.erase(remove_if(str0.begin(), str0.end(), ::isspace), str0.end()); 
    str1.erase(remove_if(str1.begin(), str1.end(), ::isspace), str1.end());

    string address = formatHex(str0);
    string value = formatHex(str1);
    string result = hex2Bin(value);

    //cout << i << endl;
    //cout << value << endl;

    myMem[address] = result;
  } else {

  }
}

// Converts a string to an integer.  Assumes s is something like "-231" and produces -231
int MemParser::cvtNumString2Number(string s) {
  int k = 1;
  int val = 0;
  for (int i = s.length()-1; i>0; i--)
  {
    char c = s.at(i);
    val = val + k*((int)(c - '0'));
    k = k*10;
  }
  if (isSign(s.at(0)))
  {
    if (s.at(0) == '-') val = -1*val;
  }
  else
  {
    val = val + k*((int)(s.at(0) - '0'));
  }
  return val;
}

string MemParser::formatHex(string s) {
  if ((s[0] == '0' && s[1] == 'x') || (s[0] == '0' && s[1] == 'X')) {
    // take care of "0x" or "0X"
    s.erase(0, 2);
  }
  transform(s.begin(), s.end(), s.begin(), ::toupper); //convert to all capital
  return s;
}

string MemParser::hex2Bin(string s) {
  string result;
  for (unsigned int i = 0; i < s.length(); i++) {
    char c = s[i];
    if (c == '0')  result += "0000";
    if (c == '1')  result += "0001";
    if (c == '2')  result += "0010";
    if (c == '3')  result += "0011";
    if (c == '4')  result += "0100";
    if (c == '5')  result += "0101";
    if (c == '6')  result += "0110";
    if (c == '7')  result += "0111";
    if (c == '8')  result += "1000";
    if (c == '9')  result += "1001";
    if (c == 'A')  result += "1010";
    if (c == 'B')  result += "1011";
    if (c == 'C')  result += "1100";
    if (c == 'D')  result += "1101";
    if (c == 'E')  result += "1110";
    if (c == 'F')  result += "1111";
  }
  return result;
}
