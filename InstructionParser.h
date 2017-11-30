#ifndef _INSTRUCTIONPARSER_H_
#define _INSTRUCTIONPARSER_H_

#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <bitset>

using namespace std;

class InstructionParser{
    
private:
    map<string, string> myInstruction;

    string myAddress;

    void isADD(string line);

    void isSUB(string line);

    void isADDI(string line);

    void isSLT(string line);

    void isLW(string line);

    void isSW(string line);

    void isBEQ(string line);

    void isJ(string line);

    void increment();

    bool isEmpty(string s);
    bool isComment(string s);
    bool isWhitespace(char c)    { return (c == ' '|| c == '\t'); };

    string hex2Bin(string s);
    string bin2Hex(string s);
    string add(string operand1, string operand2);
    char getHexCharacter(string str);

    
public:
    InstructionParser(string file);

    map<string, string> getInstruction() { return myInstruction; }
};
#endif
