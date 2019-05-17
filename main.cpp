#include <iostream>
#include <fstream>

#include "src/enigma.h"
#include "src/Sinkov.h"
using  namespace std;
int main() {
    Enigma machine(1,5,0,'I','W','M','A','A','A');
    machine.setStecker("JKFIAQ");
    string cryptText = "MXZQISHYLOQDRLUWJQLJXZDVTEZUFRASGKFFNFLUZCLVQJCNKHQKUAIGRTPOIQWMLZBHUSSAH";
    string text = machine.encode(cryptText);
    cout << text << endl;

    Sinkov sinkov;
    double score = sinkov.score(cryptText);
    cout << "Score: " << score << endl;

    return 0;
}