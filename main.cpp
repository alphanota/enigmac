#include <iostream>

#include "src/enigma.h"
int main() {
    Enigma machine(1,5,0,'I','W','M','A','A','A');
    machine.setStecker("JKFIAQ");
    std::string text = machine.encode("MXZQISHYLOQDRLUWJQLJXZDVTEZUFRASGKFFNFLUZCLVQJCNKHQKUAIGRTPOIQWMLZBHUSSAH");
    std::cout << text << std::endl;
    return 0;
}