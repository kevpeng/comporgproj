#include <iostream>
#include "Simulate.h"

/*
 * Main method of the non pipeline processor simulation
 * 
 * Author: Tianchang Yang
 * Date: 11/30/2017
*/

int main(int argc, const char * argv[]) {

    Simulate sim = Simulate(argv[1]);
    sim.run();
    return 0;
}