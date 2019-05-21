#include <iostream>
#include <fstream>

#include "src/enigma.h"
#include "src/Sinkov.h"
#include "src/Crack.h"
#include "src/ResultContainer.h"

using  namespace std;

const string cryptText = "MXZQISHYLOQDRLUWJQLJXZDVTEZUFRASGKFFNFLUZCLVQJCNKHQKUAIGRTPOIQWMLZBHUSSAH";
const string cryptedText2016 = "CGKYTCJPXBMRRIQCQCVPYVYWVTCHEVQKCZNYXZULOPYWFCMLVPSOSYWZVDWOYAMCWMJ";

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

    //example();
    Enigma machine;
    machine.setSettings("524FXCAAAFYMNOSDL");
    cout << machine.encode(cryptedText2016) << endl;
    Crack crack;
    //crack.decipher(cryptedText2016);
    //crack.findStecker("step4.txt",cryptedText2016);
    return 0;
}