#include "MUX.h"

using namespace std;

/*
 * Tester file for MUX
 *
 * Author: Tianchang Yang
 * Date: 11/3/17
 */

int main(int argc, char *argv[])
{
  MUX temp = MUX();

  temp.setOperand1("11111111111111111111111111101111"); //-17
  temp.setOperand2("11111111111111111111111111101111");
  temp.setControl(0);
  temp.execute();
  string output = temp.getOutput();

  cout << output << endl; //should output "11111111111111111111111111101111"


  temp.setOperand1("11111111111111111111111111101111"); //-17
  temp.setOperand2("00000000000000000000000000011000"); //24
  temp.setControl(0);
  temp.execute();
  output = temp.getOutput();

  cout << output << endl; //should output "11111111111111111111111111101111"


  temp.setOperand1("11111111111111111111111111101111"); //-17
  temp.setOperand2("00000000000000000000000000011000"); //24
  temp.setControl(1);
  temp.execute();
  output = temp.getOutput();

  cout << output << endl; //should output "00000000000000000000000000011000"

}
