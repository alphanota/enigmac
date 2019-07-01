#include <iostream>
#include <fstream>
#include <stdlib.h>  // for strtol

#include "src/Crack.h"
#include "src/enigma.h"

using  namespace std;

int main(int argsc, char* argv[]) {

    if(argsc == 4 ) {
        Enigma machine;
        machine.setSettings(argv[2]);
        cout << argv[1] << " : " << machine.encode(argv[3]);
        return 0;
    }

    if(argsc <3) {
        cout << "usage: ./enigma [ciphertext] [#plugpairs]" << endl;
        return 1;
    }
    Crack crack;

    crack.decipher(argv[1],stoi(argv[2]));

    return 0;
}