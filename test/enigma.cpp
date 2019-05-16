//
// Created by angel on 5/16/19.
//

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch2/catch.hpp"
#include "../src/enigma.h"


TEST_CASE("Enigma machine", "[enigma]") {
    Enigma enigma;
    Enigma machine(1,5,0,'I','W','M','A','A','A');
    machine.setStecker("JKFIAQ");

    std::string plaintext ("LIFESBUTAWALKINGSHADOWAPOORPLAYERTHATSTRUTSANDFRETSHISHOURUPONTHESTAGEKDB");
    std::string encryptedText ("MXZQISHYLOQDRLUWJQLJXZDVTEZUFRASGKFFNFLUZCLVQJCNKHQKUAIGRTPOIQWMLZBHUSSAH");

    std::string text = machine.encode(plaintext);
    REQUIRE( text == encryptedText );
}