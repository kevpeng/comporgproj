#ifndef __REGPARSER_H__
#define __REGPARSER_H__

using namespace std;

#include <iostream>
#include <map>
#include <fstream>
#include <algorithm>

/* 
 * Parses register configuration file. Assumes format is correct.
 * 
 * Author: Tianchang Yang
 * Date: 11/1/17
 */
   

class RegParser{
 public:
  // Default constructor, parse registers into map data structure
  RegParser(string filename);

  // Accessor for the register file parsed from register input file
  &map<int, string> getRegisters() { return &myReg; }

 private:
  // Instance variable storing registers values (binary values)
  map<int, string> myReg;



  // Helper methods
  bool isSign(char c)          { return (c == '-' || c == '+'); };
  bool isEmpty(string s);
  bool isComment(string s);

  // Method to parse a line of a correct formatted input
  void parseLine(string s);
  
  // Converts a string to an integer.  Assumes s is something like "-231" and produces -231
  // Taken from ASMParser class
  int  cvtNumString2Number(string s);

  // Given a correct formatted string, convert it into a string of all capital, no "0x" 
  // or "0X" string representation of a hex number
  string formatHex(string s);

  // Convert a correct formatted string into binary strings representation of the same value
  string hex2Bin(string s);

};

#endif
