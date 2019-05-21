//
// Created by angel on 5/19/19.
//

#ifndef ENIGMAC_RESULTCONTAINER_H
#define ENIGMAC_RESULTCONTAINER_H


#include <set>
#include "Result.h"

class ResultContainer {
public:
    int limit; //# of elements the result set can contain;
    ResultContainer(int limit);

    void insert(const Result& result);
    void list();
    void save(std::string file);
    std::multiset<Result> getResults();

private:
    std::multiset<Result> results;

    double bound = 0;
    int bucket[336] = {};






};


#endif //ENIGMAC_RESULTCONTAINER_H
