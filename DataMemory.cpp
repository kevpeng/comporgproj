/*
 * Author: Kevin Peng
 *
 * This class simulated the Data Memory of a processor. 
 * bool values, needToRead and needToWrite can be set from outside, 
 * and will determine if it's necessary to store things in memory or not. 
 *
 */
#include "MemParser.h"
#include "DataMemory.h"

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
  if(MemParser::isComment(line)) continue;
  
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
      for(int i = 0; i < line.length(); i++) {
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

// sets the needToWRite instance variable
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
  // currentData = dataMemoryMap[currentAddress];
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
  cout << "in print()" << endl;
  map<string,string>::iterator it;
  for(it = dataMemoryMap.begin(); it != dataMemoryMap.end(); it++){
    cout << "dataMemoryMap[" << it->first << "] = " << it->second << endl;
  }
  cout << "current address: " << currentAddress << endl;
  cout << "current data: " << currentData << endl;

}

