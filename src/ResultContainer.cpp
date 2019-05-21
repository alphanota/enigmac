//
// Created by angel on 5/19/19.
//

#include <iostream>
#include <fstream>
#include "ResultContainer.h"

ResultContainer::ResultContainer(int limit) : limit(limit) {}

void ResultContainer::insert(const Result& result) {
    if (results.size() < limit) {
        results.insert(result);
        if(result.result < bound) bound = result.result;
        return;
    }

    if (result.result < bound) return;
    else {
        results.erase(--results.end());
        results.insert(result);
    }
}

void ResultContainer::list() {
    std::multiset<Result>::iterator it;

    for(it = results.begin(); it != results.end(); ++it) {
        std::cout << it->result << ":" << it->setting  << std::endl;
    }
}

void ResultContainer::save(std::string file) {
    std::ofstream out(file);
    std::string line;
    std::multiset<Result>::iterator it;

    for(it = results.begin(); it != results.end(); ++it) {
        out << it->result << " " << it->setting  << std::endl;
    }
    out.close();
}

std::multiset<Result> ResultContainer::getResults() {
    return results;
}





