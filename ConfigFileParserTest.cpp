#include "ConfigFileParser.h"

int main()
{
	ConfigFileParser temp = ConfigFileParser();
	temp.configure("input1.config");
	cout << "input file name (.asm) = " << temp.getInputFile() << endl;
	cout << "memory file name = " << temp.getMemoryFile() << endl;
	cout << "register file name = " << temp.getRegisterFile() << endl;
	cout << "output mode(1 = batch, 0 = single_step) = " << temp.getOutputMode() << endl;
	cout << "output file name = " << temp.getOutputFile() << endl;
	cout << "debug mode(1 = true, 0 = false) = " << temp.getDebugMode() << endl;
	cout << "write to file? (1 = true, 0 = false) = " << temp.getWriteToFile() << endl;
	cout << "print memory? (1 = true, 0 = false) = " << temp.getPrintMemory() << endl;
	return 0;

}
