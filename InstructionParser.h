#ifndef _INSTRUCTIONPARSER_H_
#define _INSTRUCTIONPARSER_H_

#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <bitset>
#include <algorithm>

using namespace std;


/* 
 * Parses mips instruction file into binary encoding. Supports add, addi, sub, 
 * slt,lw, sw,beq,and j instructions.Assumes format is correct. Stores all 
 * instructions in map data structure and assign correct address (starts with 
 * 0x00400000 and increment by 4)
 * 
 * Author: Tiancahng Yang
 * Date: 11/30/17
 */
   
class InstructionParser{
    
private:
    //data structure to store binary encoding with its respective address
    map<string, string> myInstruction;

    map<string, string> myOriginal;

    //current address (starts with 0x00400000)
    string myAddress;

    //private method to decode each instruction
    void isADD(string line);

    void isSUB(string line);

    void isADDI(string line);

    void isSLT(string line);

    void isLW(string line);

    void isSW(string line);

    void isBEQ(string line);

    void isJ(string line);

    //increment the address
    void increment();

    //helper method to help with parsing
    bool isEmpty(string s);
    bool isComment(string s);
    bool isWhitespace(char c)    { return (c == ' '|| c == '\t'); };

    //helper method to convert between hex and binary
    string hex2Bin(string s);
    string bin2Hex(string s);
    char getHexCharacter(string str);

    //helper method to increment address
    string add(string operand1, string operand2);

    
public:
    //constructor that takes in a string and parse the instruction within
    //the file specified by the paramenter string 
    InstructionParser(string file);

   //returens the map storing binary encoding
   map<string, string> getInstruction() { return myInstruction; }

   map<string, string> getOriginal() { return myOriginal; }
};
#endif
