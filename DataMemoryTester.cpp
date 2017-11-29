/*
 *  Tester file for DataMemory
 *  
 *  Author: Kevin Peng
 *  Date: 11/28/2017
 *
 */

#include "DataMemory.h"
using namespace std;

int main()
{
	DataMemory obj = DataMemory();	
	cout << "tests" << endl;
	DataMemory obj1 = DataMemory("data1.memory");
	//obj1.setFromFile("data1.memory");
	cout << "works" << endl;
	obj1.setCurrAddress("0x10000000");
	obj1.print();
	obj1.writeData("0x10000004");	
	obj1.print();
	
	return(0);
}
