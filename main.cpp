#include <iostream>
#include <fstream>

#include "src/enigma.h"
#include "src/Sinkov.h"
#include "src/Crack.h"
#include "src/ResultContainer.h"

using  namespace std;

const string cryptText = "MXZQISHYLOQDRLUWJQLJXZDVTEZUFRASGKFFNFLUZCLVQJCNKHQKUAIGRTPOIQWMLZBHUSSAH";

void example(){
    Enigma machine;
    machine.setSettings("150IWMAAAJKFIAQ");
    string text = machine.encode(cryptText);
    cout << text << endl;

    Sinkov sinkov;
    double score = sinkov.score(cryptText);
    cout << "Score: " << score << endl;

    cout << sinkov.score("LIFESBUTAWALKINGSHADOWAPOORPLAYERTHATSTRUTSANDFRETSHISHOURUPONTHESTAGEKDB");
}

int main() {

    Crack crack;
    example();
    crack.decipher(cryptText);


    return 0;
}