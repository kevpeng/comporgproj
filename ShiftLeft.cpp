/*
 * shift left component
 *
 * Author: Tianchang Yang
 * Date: 11/30/2017
 */

#include "ShiftLeft.h"

ShiftLeft::ShiftLeft()
{

}

//takes in a 26-bit string that represents a binary number.
//The method shifts the binary number left by 2 and adds 2 additional bits. 
string ShiftLeft::shift(string input)
{
	if(input.length() == 32){
        input.erase(0,2);
    }
    input += "00";
    
    return input;
}
