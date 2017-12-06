#ifndef PC_h
#define PC_h

#include <string>

using namespace std;

class PC {
  public:
    ///Constructors
    // default constructor
    inline PC() { currentAddress = "00400000"; }	

    ///Functions
    // sets the current address
    inline void setCurrAddress(string address) { currentAddress = address;}

    // get the currentAddress
    inline string getAddress() { return currentAddress; }

  private: 
    ///Private Variables
    // currentAddress is in hexidecimal
    string currentAddress;
};

#endif
