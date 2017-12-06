/*
 * Tester file for instruction parser class
 *
 * Author: Tianchang Yang
 * Date: 11/30/17
 */
#include "InstructionParser.h"

using namespace std;

int main(int argc, char *argv[]) {
  InstructionParser temp = InstructionParser(argv[1]);

  map<string, string> instructions = temp.getInstruction();

  for (map<string, string>::iterator it = instructions.begin(); it!=instructions.end(); ++it) {
    cout << it->first << "\t"<< it->second << endl;
  }
}
