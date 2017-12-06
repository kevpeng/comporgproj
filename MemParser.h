/* 
 * Parses memory data configuration file. Assumes format is correct.
 * 
 * Author: Tianchang Yang
 * Date: 11/1/17
 */

#ifndef __MEMPARSER_H__
#define __MEMPARSER_H__

#include <iostream>
#include <map>
#include <fstream>
#include <algorithm>

using namespace std;

class MemParser{
  public:
    ///Constructors
    // Default constructor, parse memory data into map data structure
    MemParser(string filename);

    ///Getters
    // Accessor for the memory data file parsed from memory data input file
    map<string, string> getMemory() { return myMem; }

  private:
    ///Private Variables
    // Instance variable storing memory values (binary values)
    map<string, string> myMem;



    ///Private Helper Methods
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
