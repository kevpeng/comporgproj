#include "ConfigFileParser.h"

ConfigFileParser::ConfigFileParser() {}

void ConfigFileParser::configure(string file)
{
    fstream in;
    in.open(file.c_str());
    
    if (in.bad()){
        cout << "BAD CONFIG FILE" << endl;
    }
	
    string line;
    
    while (getline(in, line))
    {
        if (line.find("#") != std::string::npos)
        {
            continue;
        }
        else if (line.find("program_input") != std::string::npos)
        {
            line.erase(line.begin(), line.begin() + 14);
            programInput = line;
        }
        else if (line.find("memory_contents_input") != std::string::npos)
        {
            line.erase(line.begin(), line.begin() + 22);
            memoryContentsInput = line;
        }
        else if (line.find("register_file_input") != std::string::npos)
        {
            line.erase(line.begin(), line.begin() + 20);
            registerFileInput = line;
        }
        else if (line.find("output_mode") != std::string::npos)
        {
            if (line.find("batch") != std::string::npos){
                batch = true;
            }else{
                batch = false;
            }
        }
        else if (line.find("debug_mode") != std::string::npos)
        {
            if (line.find("true") != std::string::npos){
                debug = true;
            }else{
                debug = false;
            }
        }
        else if (line.find("print_memory_contents") != std::string::npos)
        {
            if (line.find("true") != std::string::npos){
                printMemoryInput = true;
            }else{
                printMemoryInput = false;
            }
       //     cout << "print memory contents " << printMemoryInput << endl;

        }
        else if (line.find("write_to_file") != std::string::npos)
        {
            if (line.find("true") != std::string::npos){
                writeToFile = true;
            }else{
                writeToFile = false;
            }
        }
        else if (line.find("output_file") != std::string::npos)
        {
            line.erase(line.begin(), line.begin() + 12);
            outputFile = line;
        }
	}    
}
