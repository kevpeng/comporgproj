/*
 * This class simulates the PC, program counter, of our datapath. 
 * It has a current address that gets updated. 
 *
 *
 */

#include "PC.h" 

/*
void PC::updateAddress()
{
	string binaryAddress = PC::hex2Bin(currentAddress);
	ALU temp = ALU();
	temp.setOperand1(binaryAddress);
	temp.setOperand2("00000000000000000000000000000100");
	temp.setOperation(1);
	temp.execute();
	currentAddress = temp.getOutput(); 
	// currentAddress = bin2Hex(currentAddress);
}

string PC::hex2Bin(string s)
{
  	if(s.length() == 32) { return s; }

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
{	// code taken from stackoverflow.com/questions/29210120/binary-string-to-
	// hex-c 
	string binToHex = "";
	for(int i = 0; i < (s.size() - 1); i++){
    	string s;
		string tmp = "";
    	for (int j = 0; j < s.size(); j += 4){
    	    tmp = s.substr(j, 4);
    	    if      (!tmp.compare("0000")) binToHex += "0";
        	else if (!tmp.compare("0001")) binToHex += "1";
        	else if (!tmp.compare("0010")) binToHex += "2";
       		else if (!tmp.compare("0011")) binToHex += "3";
       	 	else if (!tmp.compare("0100")) binToHex += "4";
       	 	else if (!tmp.compare("0101")) binToHex += "5";
       	 	else if (!tmp.compare("0110")) binToHex += "6";
       	 	else if (!tmp.compare("0111")) binToHex += "7";
       	 	else if (!tmp.compare("1000")) binToHex += "8";
       	 	else if (!tmp.compare("1001")) binToHex += "9";
       	 	else if (!tmp.compare("1010")) binToHex += "A";
       	 	else if (!tmp.compare("1011")) binToHex += "B";
       	 	else if (!tmp.compare("1100")) binToHex += "C";
       	 	else if (!tmp.compare("1101")) binToHex += "D";
       	 	else if (!tmp.compare("1110")) binToHex += "E";
       	 	else if (!tmp.compare("1111")) binToHex += "F";
       	 	else continue;
		cout << "binToHex = " << binToHex << endl;
    	}
		cout << "binToHex = " << binToHex << endl;
    	return binToHex;
	}
	*/
/*	string out;
	int len = s.length();
	int temp;
	for(int i(0); i + 1 < len; i += 4){
		if(stringstream(s.substr(i,4)) >> hex >> temp){
		out.push_back(temp);
		}
	}
*/
