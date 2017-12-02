/*
 * Author: Kevin Peng
 *
 * This class simulated the Data Memory of a processor. 
 * bool values, needToRead and needToWrite can be set from outside, 
 * and will determine if it's necessary to store things in memory or not. 
 *
 */
#include "DataMemory.h"
#include "MemParser.h"

// constructor for DataMemory
DataMemory::DataMemory()
{
  dataMemoryMap = map<string, string> ();
}

// constructor from file 
DataMemory::DataMemory(string filename)
{ 
  dataMemoryMap = map<string, string>();
  setFromFile(filename);
}

// reads in file of strings. processes it and puts it into the map
void DataMemory::setFromFile(string filename)
{ 
	
	MemParser parser = MemParser(filename);
  	dataMemoryMap = parser.getMemory();
/*  
  	fstream input;
  	input.open(filename.c_str());
  	if(input.bad()) { cout << "error reading file" << endl; }
  	else {
    	string line;
    	while(getline(input, line))
    	{
		
    	  	// replace the colons with spaces in text file.
    	  	string stringsArray[2];
    	  	bool data = false;
			bool comment = false;
		    for(int i = 0; i < line.length(); i++) {
    	    	if(line[i] == '#') { // if its a comment, go to next line.
					comment = true;
					break;
				}
	
				if(line[i] == ':') {
	        		data = true;
	        		continue;
	        	}  
	        	if(!data) { // address put into stringsArray[0]
	        		stringsArray[0] += line[i];
	        	}
	        	if(data) { // data put into stingsArray[1]
	        	  	stringsArray[1] += line[i];	
	        	}
	      	}
		  	if(!comment){  
	      	// make into uniform hexidecimal
	      		for(int i = 0; i < 2; i++){
	        		if(stringsArray[i].substr(0,2) != "0x"){
	        			stringsArray[i] = "0x" + stringsArray[i];
	        		}
		  		}
	      		// put the processed data into the map.
	      		dataMemoryMap[stringsArray[0]] = stringsArray[1];		
	    	}
		}    
	}
*/
}

// sets the needToWrite instance variable
void DataMemory::setNeedToWrite(bool writeToMem) 
{
  needToWrite = writeToMem;
}

// if it's necessary to write data, write the data into the address given
void DataMemory::writeData(string address) 
{
  if(needToWrite){
    dataMemoryMap[address] = currentData;
  }
}


// determines if it's necessary and sets the needToRead instance variable
void DataMemory::setNeedToRead(bool readFromMem)
{
  needToRead = readFromMem;
}

// given a hex string addres, sets it to the current address;
void DataMemory::setCurrAddress(string address)
{
  currentAddress = address;
  currentData = dataMemoryMap[currentAddress];
}

// given the data, sets current data to it.
void DataMemory::setCurrData(string data)
{
  currentData = data;
}

// if it's necessary to read from memory, read it.
string DataMemory::memRead()
{
  if(needToRead)
  {
    cout << "Memory Read: " << dataMemoryMap[currentAddress] << endl;
    return dataMemoryMap[currentAddress];
  } else {
    cout << "Memory Read Disabled " << endl;
    return "";
  }
}

//If it's necessary to write to memory, write it.
void DataMemory::memWrite()
{
  if(DataMemory::needToWrite){
    cout << "Memory written: " << currentData << " At Address " << currentAddress << endl;
    dataMemoryMap[currentAddress] = currentData;
  }	

}

string DataMemory::readData()
{
  return currentData;
}
/*
   string DataMemory::getAllData()
   {
   stringstream ss;
   map<string,string>::iterator it;
   for(it = dataMemoryMap.begin(); it != dataMemoryMap.end(); it++) {
   ss << "dataMemoryMap[" << it->first << "] = " << it->second << endl; 
   }
   return ss.str();
   }
*/

void DataMemory::print() 
{
  cout << "Memory Contents:" << endl;
  map<string,string>::iterator it;
  for(it = dataMemoryMap.begin(); it != dataMemoryMap.end(); it++){
	string t = it->second;
    cout << "address:[0x" << it->first << "] = 0x" << bin2Hex(t) << endl;
  }

  cout << endl;
  //cout << "current address: " << currentAddress << endl;
  //cout << "current data: " << currentData << endl;

}

char DataMemory::getHexCharacter(string str)
{
	if(str.compare("1111") == 0) return 'F';
	else if(str.compare("1110") == 0) return 'E';
	else if(str.compare("1101")== 0) return 'D';
	else if(str.compare("1100")== 0) return 'C';
	else if(str.compare("1011")== 0) return 'B';
	else if(str.compare("1010")== 0) return 'A';
	else if(str.compare("1001")== 0) return '9';
	else if(str.compare("1000")== 0) return '8';
	else if(str.compare("0111")== 0) return '7';
	else if(str.compare("0110")== 0) return '6';
	else if(str.compare("0101")== 0) return '5';
	else if(str.compare("0100")== 0) return '4';
	else if(str.compare("0011")== 0) return '3';
	else if(str.compare("0010")== 0) return '2';
	else if(str.compare("0001")== 0) return '1';
	else if(str.compare("0000")== 0) return '0';
	return ' ';
}

string DataMemory::bin2Hex(string s)
{
	string endresult = "";
	for(int i = 0; i < s.length(); i = i+4)
	{
		endresult += getHexCharacter(s.substr(i,4));
	}
	return endresult;
}



