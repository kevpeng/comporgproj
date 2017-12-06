#include "PC.h" 
//#include "ALU.h"
#include <iostream>

int main(){
	PC temp = PC();
	cout << "current address expected = [0x00400000] actual = " << temp.getAddress() << endl;	
//	temp.updateAddress();	
	
//	cout << "current address expected = [0x00400000] actual = " << temp.getAddress() << endl;	
		
//	temp.updateAddress();	
//	
//	cout << "current address expected = [0x00400000] actual = " << temp.getAddress() << endl;	
//	temp.updateAddress();	
	
//	cout << "current address expected = [0x00400000] actual = " << temp.getAddress() << endl;	
	return 0;
}
