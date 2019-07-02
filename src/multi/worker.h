//
// Created by angel on 7/1/19.
//

#ifndef ENIGMAC_WORKER_H
#define ENIGMAC_WORKER_H


#include <vector>
#include <set>
#include "../Result.h"
#include "../enigma.h"
#include "../Sinkov.h"
#include "../Crack.h"
# include <boost/thread.hpp>
#include <iterator>


class worker {

private:
    std::vector<Result> mContainer;
    std::vector<Result>::iterator mBegin;
    std::vector<Result>::iterator mEnd;
    std::string mText;
    Sinkov mSinkov;

public:
    void setup(std::vector<Result>::iterator begin, std::vector<Result>::iterator end, std::string text, Sinkov sinkov);

    // Beginning of Example A.1.1.1c of OpenMP 2.5 standard document
    void decode(std::vector<Result>::iterator begin, std::vector<Result>::iterator end, std::vector<Result>& container, std::string text);


    virtual void process_it(std::vector<Result>::iterator it, Enigma& machine, Sinkov& sinkov, std::vector<Result>& container, std::string text) = 0;


    std::vector<Result> getContainer();
    void operator()()
    {     decode(mBegin, mEnd, mContainer, mText); }
};


class worker_p: public worker {

public:

    virtual void process_it(vector<Result>::iterator it, Enigma& machine, Sinkov& sinkov,
                    vector<Result>& container, string text) override ;

};

class worker_r: public worker {

    public:

    virtual void process_it(vector<Result>::iterator it, Enigma& machine, Sinkov& sinkov,
                    vector<Result>& container, string text) override;

};

#endif //ENIGMAC_WORKER_H
