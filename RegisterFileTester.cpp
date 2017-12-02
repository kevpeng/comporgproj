#include "RegisterFile.h"

int main() {
  RegisterFile::RegisterFile regFile("register1.memory");
  regFile.printRegisterFile();
  return 1;
}
