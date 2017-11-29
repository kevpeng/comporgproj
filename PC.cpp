/*
 * This class simulates the PC, program counter, of our datapath. 
 * It has a current address that gets updated. 
 *
 *
 */

#include "PC.h" 
#include "ALU.h"

void PC::updateAddress()
{
	string binaryAddress = PC::hex2Bin(currentAddress);
	currentAddress = ALU::add(binaryAddress, "00000000000000000000000000000100");	
	/*
 	* need to convert it back to hex... 
 	*/ 
}

string PC::hex2Bin(string s)
{
  	string result;
  	for (int i = 0; i < s.length(); i++) {
    	char c = s[i];
   		if (c == '0')  result += "0000";
   		if (c == '1')  result += "0001";
   		if (c == '2')  result += "0010";
   		if (c == '3')  result += "0011";
   		if (c == '4')  result += "0100";
   		if (c == '5')  result += "0101";
   		if (c == '6')  result += "0110";
   		if (c == '7')  result += "0111";
   		if (c == '8')  result += "1000";
   		if (c == '9')  result += "1001";
   		if (c == 'A')  result += "1010";
   		if (c == 'B')  result += "1011";
   		if (c == 'C')  result += "1100";
   		if (c == 'D')  result += "1101";
   		if (c == 'E')  result += "1110";
   		if (c == 'F')  result += "1111";
  	}
  	return result;
}

string PC::bin2Hex(string s) 
{
}
