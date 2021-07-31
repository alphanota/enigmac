//
// Created by angel on 5/16/19.
//

#include "Sinkov.h"


#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>

using namespace std;

Sinkov::Sinkov(){
    readFile("../src/english_bigrams.csv");
}

void Sinkov::readFile(string file) {
    ifstream myfile(file);
    string   line;

    while(getline(myfile, line))
    {
        std::stringstream   linestream(line);
        std::string         data;
        int c;
        double p,l;

        string entry;

        linestream >> entry >> c >> p >> l;
        bigramScore[ entry[0]-'A' ][ entry[1]-'A' ] = l;

    }
    myfile.close();

}

float Sinkov::score(std::string text) {
    float sum = 0;
    for (int i = 1; i < text.size(); i++) {
        int first = text[i-1] -'A';
        int last = text[i] -'A';
        sum = sum + bigramScore[first][last];
    }
    return sum;
}