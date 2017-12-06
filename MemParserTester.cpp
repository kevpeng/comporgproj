/*
 * Tester file for class MemParser
 *
 * Author: Tianchang Yang
 * Date: 11/1/17
 */
#include "MemParser.h"

using namespace std;

int main(int argc, char *argv[]) {
  MemParser *parser;

  if(argc < 2){
    cerr << "Need to specify a memory file to translate."<<endl;
    exit(1);
  }

  parser = new MemParser(argv[1]);

  map<string, string> memoryMap = parser->getMemory();

  for (map<string, string>::iterator it = memoryMap.begin(); it!=memoryMap.end(); ++it) {
    cout << it->first << "\t"<< it->second << endl;
  }

  delete parser;
}
