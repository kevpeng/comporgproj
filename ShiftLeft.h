/*
 * shift left component
 *
 * Author: Tianchang Yang
 * Date: 11/30/2017
 */

#ifndef _SHIFTLEFT_H_
#define _SHIFTLEFT_H_

#include <string>

using namespace std;

class ShiftLeft {

  public:
    ///Constructors 
    // Default constructor
    ShiftLeft();

    ///Functions
    //takes in a 26-bit string that represents a binary number.
    //The method shifts the binary number left by 2 and adds 2 additional bits. 
    string shift(string input); 
};

#endif 
