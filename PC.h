#ifndef PC_h
#define PC_h

#include <string>

using namespace std;

class PC
{
	public:
		// default constructor
		inline PC() { currentAddress = "0x00400000"; }	
		
		// sets the current address
		inline void setCurrAddress(string address) { currentAddress = address;}
		
		// updates the address	
		void updateAddress();

		// get the currentAddress
		inline string getAddress() { return currentAddress; }
	
		// converts hexidecimal to binary
		string hex2Bin(string s);

		// converts binary to hexidecimal
		string bin2Hex(string s);	

	private: 
		// currentAddress is in hexidecimal
		string currentAddress;
	
};

#endif
