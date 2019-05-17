//
// Created by angel on 5/16/19.
//

#ifndef ENIGMAC_SINKOV_H
#define ENIGMAC_SINKOV_H


#include <string>

class Sinkov {
private:
    double bigramScore[26][26];

public:
    Sinkov();
    void readFile(std::string filename);
    float score(std::string text);
};


#endif //ENIGMAC_SINKOV_H
