/*
 * sign extend
 *
 * Author: Tianchang Yang
 * Date: 11/30/2017
 */
#include "SignExtend.h"

// Default constructor
SignExtend::SignExtend() {
}

//extend a binary string into 32 bits supporting 2's complement representation
string SignExtend::extend(string input) {
    while (input.length() < 32) {
        input = input[0] + input;
    } 
    
    return input;
}

