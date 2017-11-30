#include "InstructionParser.h"

using namespace std;

/*
 * Tester file for ALU
 *
 * Author: Tianchang Yang
 * Date: 11/3/17
 */

int main(int argc, char *argv[])
{
  InstructionParser temp = InstructionParser(argv[1]);

  map<string, string> instructions = temp.getInstruction();

  for (map<string, string>::iterator it = instructions.begin(); it!=instructions.end(); ++it) {
    cout << it->first << "\t"<< it->second << endl;
  }
  
}
