/*
 * Tester file for ALU
 *
 * Author: Tianchang Yang
 * Date: 11/3/17
 */
#include "ALU.h"

using namespace std;

int main(int argc, char *argv[]) {
  ALU temp = ALU();

  temp.setOperand1("11111111111111111111111111101111"); //-17
  temp.setOperand2("11111111111111111111111111101111");
  temp.setOperation(0);
  temp.execute();
  string output = temp.isEqual();

  cout << output << endl; //should output "true"


  temp.setOperand1("11111111111111111111111111101111"); //-17
  temp.setOperand2("00000000000000000000000000011000"); //24
  temp.setOperation(1);
  temp.execute();
  output = temp.getOutput();

  cout << output << endl; //should output "00000000000000000000000000000111"



  temp.setOperand1("11111111111111111111111111101111"); //-17
  temp.setOperand2("00000000000000000000000000011000"); //24
  temp.setOperation(2);
  temp.execute();
  output = temp.getOutput();

  cout << output << endl; //should output "11111111111111111111111111010111"

  temp.setOperand1("11111111111111111111111111101111"); //-17
  temp.setOperand2("00000000000000000000000000011000"); //24
  temp.setOperation(0);
  temp.execute();
  output = temp.isEqual();

  cout << output << endl; //should output "false"
}
