#include <string>
#include <iostream>
#include <fstream>
using namespace std; 

class ConfigFileParser
{
	public: 
		
		// constructor for configurateion file parser
		ConfigFileParser();
		void configure(string file);	
		inline string getInputFile() { return programInput; }
		inline string getMemoryFile() { return memoryContentsInput; }
		inline string getRegisterFile() { return registerFileInput; } 
		inline string getOutputFile() { return outputFile; } // what the output file name is.
		inline bool getOutputMode() { return batch;  } // if false, single step mode.
		inline bool getDebugMode() { return debug; } // if false, don't debug
		inline bool getWriteToFile() { return writeToFile; } // if true, all output for this run will write to a file
		inline bool getPrintMemory() { return printMemoryInput; } // if true, prints out current contents of entire register file and entire memory
 
	private:
		// private instance variables	
		string programInput;
		string  memoryContentsInput;
		string registerFileInput;
		string outputFile;
	
		bool batch;
		bool debug;
		bool writeToFile;
		bool printMemoryInput;
};
