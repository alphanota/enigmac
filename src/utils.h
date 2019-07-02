//
// Created by angel on 7/1/19.
//

#ifndef ENIGMAC_UTILS_H
#define ENIGMAC_UTILS_H

#include "Result.h"
#include "ResultContainer.h"
#include <vector>

std::vector<Result> to_vector(ResultContainer container) {
    std::multiset<Result> data = container.getResults();
    std::multiset<Result>::iterator it2;

    std::vector<Result> newResults;
    for(it2 = data.begin(); it2 != data.end(); ++it2) {
        newResults.push_back(*it2);
    }
    return newResults;
}

#endif //ENIGMAC_UTILS_H
