/*
 * sign extend
 *
 * Author: Tianchang Yang
 * Date: 11/30/2017
 */

#ifndef _SIGNEXTEND_H_
#define _SIGNEXTEND_H_

#include <string>
using namespace std;

class SignExtend
{
    
private:
    
public:
    // Default constructor
    SignExtend();
    
    //extend a binary string into 32 bits supporting 2's complement representation
    string extend(string input);
};
#endif 