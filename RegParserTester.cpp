#include "RegParser.h"

using namespace std;

/*
 * Tester file for class RegParser
 *
 * Author: Tianchang Yang
 * Date: 11/1/17
 */

int main(int argc, char *argv[])
{
  RegParser *parser;

  if(argc < 2){
    cerr << "Need to specify an register file to translate."<<endl;
    exit(1);
  }

  parser = new RegParser(argv[1]);

  map<int, string> registerMap = parser->getRegisters();
  for (int i = 0; i < 32; i++) {
  	cout << i << "\t"<< registerMap[i] << endl;
  }
  
  
  delete parser;
}
