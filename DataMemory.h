#ifndef DATAMEMORY_h
#define DATAMEMORY_h

#include <iostream>
#include <string>
#include <cstring>
#include <map>  
#include <algorithm>
#include <sstream>
#include <fstream>
#include <iterator> 

using namespace std;

class DataMemory
{
    public: 
        // default constructor
        DataMemory();
        // constructs from a file 
		DataMemory(string filename);

		// perform the appropriate function
		void execute();


		// sets from a file
		void setFromFile(string filename);
        
		// writes data into a 32b string
		void writeData(string address);
	
		// updates the address
		void setCurrAddress(string address);
	
		// updates the data
		void setCurrData(string data);
       
		//set the needToWrite variable
		void setNeedToWrite(bool value);

		// set the needToRead variable
		void setNeedToRead(bool value);		
 
		// determines if needs to read memory and reads it
		string memRead();

		// determines if needs to write to memory and writes it
		void memWrite();
		
		// returns 32b string data
		string readData();
		
		// returns all the values as a string stream
//		string getAllData();		

		// prints values in table out
		void print();

	private:
		bool needToRead; // do we need to read the value
		bool needToWrite; // do we need to write the value
		string currentAddress; // current address
		string currentData; 	// current data
		map <string,string> dataMemoryMap;
	
		// helper files to help get hexidecimal from binary
		char getHexCharacter(string str);	
		string bin2Hex(string s);

};

#endif
