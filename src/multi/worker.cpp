//
// Created by angel on 7/1/19.
//

#include "worker_r.h"
#include "worker_p.h"
#include "worker.h"

void worker::setup(std::vector<Result>::iterator begin, std::vector<Result>::iterator end, std::string text, Sinkov sinkov) {
    mBegin = begin;
    mEnd = end;
    mText = text;
    mSinkov = sinkov;
}

void worker::decode(std::vector<Result>::iterator begin, std::vector<Result>::iterator end, std::vector<Result>& container, std::string text) {
    Enigma machine;
    std::vector<Result>::iterator it;
    for(it = begin; it != end; ++it){
        process_it(it, machine, mSinkov, mContainer, text);
    }

}


std::vector<Result> worker::getContainer(){
    return mContainer;
}

void worker_p::process_it(vector<Result>::iterator it, Enigma& machine, Sinkov& sinkov,
                          vector<Result>& container, string text) {

    cout << "I'm running" << endl;

    //==========
    bool takenLetters[26] = {};
    for(int  l = 9; l < it->setting.length(); l++ ){
        int pos = it->setting[l] - 'A';
        takenLetters[pos] = true;
    }
    //=========

    for(int l1 = 0; l1 < 26; l1++ ) {
        for (int l2 = l1+1; l2 < 26; l2++) {
            if(takenLetters[l1] || takenLetters[l2]) continue;

            string stecker = {alphabet[l1],alphabet[l2]};
            string newSettings = (it->setting)+stecker;
            machine.setSettings( newSettings );
            string crypt = machine.encode(text);
            container.push_back(Result(newSettings,sinkov.score(crypt),0));
        }
    }
    return;

}

void worker_r::process_it(vector<Result>::iterator it, Enigma& machine, Sinkov& sinkov,
                          vector<Result>& container, string text) {

    for(char m = 'A'; m <= 'Z'; m++) {
        for (char r ='A'; r <= 'Z'; r++){

            string setting {it->setting};

            setting[7] = m;
            setting[8] = r;

            machine.setSettings(setting);
            string message_r = machine.encode(text);
            double score_r = sinkov.score(message_r);
            container.push_back(Result(setting,score_r, 0));
        }
    }

}