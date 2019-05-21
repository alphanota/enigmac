//
// Created by angel on 5/19/19.
//

#include <iostream>
#include <fstream>
#include <sstream>
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

ResultContainer::ResultContainer(std::string filename) {
    std::ifstream myfile(filename);
    std::string   line;

    getline(myfile,line);
    std::stringstream firstline(line);
    int containerSize;
    firstline >> containerSize;

    limit = containerSize;


    while(getline(myfile, line))
    {
        std::stringstream linestream(line);

        double score;
        std::string setting;

        linestream >> score >> setting;

        results.insert(Result(setting,score,0));


    }
    myfile.close();
}





