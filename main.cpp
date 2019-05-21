#include <iostream>
#include <fstream>
#include <stdlib.h>  // for strtol

#include "src/Crack.h"

using  namespace std;

int main(int argsc, char* argv[]) {

    if(argsc <3) {
        cout << "usage: ./enigma [ciphertext] [#plugpairs]" << endl;
        return 1;
    }

    Crack crack;

    crack.decipher(argv[1],stoi(argv[2]));

    return 0;
}