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

#include "MemParser.h"

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

		void setFromFile(string filename);

		void setAddress(string address) { currentAddress = address; }
		void setWriteData(string data) { currentData = data; }
		void setMemWrite(bool memWrite) { needToWrite = memWrite; }
		void setMemRead(bool memRead) { needToRead = memRead; }

		string readData();
		
		// returns all the values as a string stream
//		string getAllData();		

		// prints values in table out
		void print();

		map<string, string> getMap() { return dataMemoryMap; }

		//void writeToFile(string filename);

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
