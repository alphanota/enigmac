//
// Created by angel on 5/19/19.
//

#ifndef ENIGMAC_RESULT_H
#define ENIGMAC_RESULT_H


#include <string>

class Result {
public:
    Result(const std::string &setting, double result, int bin);

    bool operator<(const Result &rhs) const;
    std::string setting;
    double result;
    int bin;

};


#endif //ENIGMAC_RESULT_H
