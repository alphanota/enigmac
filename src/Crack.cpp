//
// Created by angel on 5/17/19.
//

#include <vector>
#include "Crack.h"
#include "enigma.h"
#include "Sinkov.h"
#include "Settings.h"
#include "ResultContainer.h"
#include "multi/multi.h"
#include "multi/worker_p.h"
#include "multi/worker_r.h"


ResultContainer checkRingstellung(string text, ResultContainer previousResults) {
    std::multiset<Result> results = previousResults.getResults();
    std::multiset<Result>::iterator it;
    Enigma machine;
    ResultContainer newResults(1000);
    Sinkov sinkov;
    int size = results.size();
    int c = 0;
    for(it = results.begin(); it != results.end(); ++it){
            for(char m = 'A'; m <= 'Z'; m++) {
                for (char r ='A'; r <= 'Z'; r++){

                    string setting {it->setting};

                    setting[7] = m;
                    setting[8] = r;

                    machine.setSettings(setting);
                    string message_r = machine.encode(text);
                    double score_r = sinkov.score(message_r);
                    newResults.insert(Result(setting,score_r, c));
                }
            }
        c++;
        cout << "finding ringstellung, trial" << c << "/" << size << endl;
    }
    return newResults;
}

ResultContainer checkGrundstellung(string text) {
    Enigma machine;
    Sinkov sinkov;
    ResultContainer mContainer(100000);
    int count;
    for(int i = 0; i < 1008; i+=3 ) {
        for(int l = 0; l < 26; l++) {
            for(int m = 0; m < 26; m++) {
                for (int r =0; r < 26; r++){
                    machine.setSettings(rotorCombinations[i],rotorCombinations[i+1],rotorCombinations[i+2],
                                        alphabet[l],alphabet[m],alphabet[r],
                                        'A','A','A',"");
                    string message = machine.encode(text);
                    double score = sinkov.score(message);
                    string mSettings = Settings::generateSettingsStr(rotorCombinations[i],rotorCombinations[i+1],rotorCombinations[i+2],
                                                                    alphabet[l],alphabet[m],alphabet[r],
                                                                    'A','A','A',"");
                    mContainer.insert(Result(mSettings,score, i/3));
                    count++;

                }
            }
        }
        //cout << "finding grundstellung: trial " << i << endl;
    }
    cout << "# of mSettings checked : " << count << endl;

    //mContainer.list();
    int x;
    cin >> x;
    return mContainer;
}

ResultContainer checkStecker(string text, ResultContainer r) {

    std::multiset<Result> results = r.getResults();
    std::multiset<Result>::iterator it;
    Enigma machine;
    ResultContainer newResults(1000);
    Sinkov sinkov;


    int size = results.size();
    int c = 0;
    for(it = results.begin(); it != results.end(); ++it){
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
                newResults.insert(Result(newSettings,sinkov.score(crypt),0));
            }
        }
        c++;
        cout << "Finding plug pair, trial: " << c << "/" << size << endl;
    }
    return newResults;
}

void decodeFromResults(ResultContainer results, int lines, string text) {
    std::multiset<Result> settings = results.getResults();
    std::multiset<Result>::iterator it = settings.begin();
    Enigma machine;
    for(int i =0; i < lines; i++){
        machine.setSettings(it->setting);
        cout << it->setting << " " << machine.encode(text) << endl;
        it++;
    }
}

void decodeFromResults(std::vector<Result> results, int lines, string text) {
    Enigma machine;
    std::vector<Result>::iterator it = results.begin();
    for(int i =0; i < lines; i++){
        machine.setSettings(it->setting);
        cout << it->setting << " " << machine.encode(text) << endl;
        it++;
    }
}


vector<Result> checkGrundstellungParallel(string text) {
    return a11c(text);
}

vector<Result> checkSteckerParallel(string basicString, vector<Result> vector) {
    return checkFromPreviousResult(basicString, vector, new worker_p);
}

vector<Result> checkRingstellungParallel(string basicString, vector<Result> vector) {
    return checkFromPreviousResult(basicString, vector, new worker_r);
}


void Crack::decipher(string text, int numSteckers) {
    vector<Result> result = checkGrundstellungParallel(text);
    int plugsLeft = numSteckers;
    if (plugsLeft > 0) {
        result = checkSteckerParallel(text,result);
        plugsLeft -= 1;
    }

    result = checkRingstellungParallel(text,result);

    for(int pair = 0; pair < plugsLeft; pair++) {
        result = checkSteckerParallel(text,result);
    }

    //result.save("phase3_results.txt");
    decodeFromResults(result,20, text);
}

void Crack::findStecker(string filename, string text) {
    ResultContainer result(filename);
    result = checkStecker(text,result);
    result.list();
    result.save("step4.txt");
}


