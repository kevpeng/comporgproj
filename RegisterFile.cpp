/* Author: Are Oelsner
 * Register File
 */
#include "RegisterFile.h"

RegisterFile::
RegisterFile() {
  for(int i = 0; i < 32; i++) {
    registers.push_back(i, NULL);
  }
}
