//
// Created by angel on 5/16/19.
//

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch2/catch.hpp"
#include "../src/enigma.h"


TEST_CASE("Enigma machine", "[enigma]") {
    //Enigma enigma;
    Enigma machine(1,5,0,'I','W','M','A','A','A');
    machine.setStecker("JKFIAQ");

    std::string plaintext ("LIFESBUTAWALKINGSHADOWAPOORPLAYERTHATSTRUTSANDFRETSHISHOURUPONTHESTAGEKDB");
    std::string encryptedText ("MXZQISHYLOQDRLUWJQLJXZDVTEZUFRASGKFFNFLUZCLVQJCNKHQKUAIGRTPOIQWMLZBHUSSAH");

    std::string text = machine.encode(plaintext);
    REQUIRE( text == encryptedText );

}


TEST_CASE("vector slice", "[enigma]") {
    //Enigma enigma;

    std::string plaintext ("ABCDEFGHIJKLMNOP");

    size_t size = plaintext.size();

    size_t n = size / 4;



    std::string::iterator cur = plaintext.begin();
    std::string::iterator end = plaintext.end();

    cur += n;

    for (int j = 1; j < 4; j++){
        std::string sub = std::string(cur, cur+n);
        std::cout << sub << std::endl;
    }
}
