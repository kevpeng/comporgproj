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
	obj1.print();
	obj1.setCurrAddress("1000000C");	
	obj1.print();
	return(0);
}
