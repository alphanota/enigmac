//
// Created by angel on 5/17/19.
//

#include "Crack.h"
#include "enigma.h"
#include "Sinkov.h"
#include "Settings.h"
#include "ResultContainer.h"

ResultContainer checkRingstellung(string text, ResultContainer previousResults) {
    std::multiset<Result> results = previousResults.getResults();
    std::multiset<Result>::iterator it;
    Enigma machine;
    ResultContainer newResults(100000);
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
        cout << c << "/" << size << endl;
    }
    newResults.save("step2_nr.txt");
    return newResults;
}

ResultContainer checkGrundstellung(string text) {
    Enigma machine;
    Sinkov sinkov;
    ResultContainer container(100000);
    for(int i = 0; i < 1008; i+=3 ) {
        for(int l = 0; l < 26; l++) {
            for(int m = 0; m < 26; m++) {
                for (int r =0; r < 26; r++){
                    machine.setSettings(rotorCombinations[i],rotorCombinations[i+1],rotorCombinations[i+2],
                                        alphabet[l],alphabet[m],alphabet[r],
                                        'A','A','A',"");
                    string message = machine.encode(text);
                    double score = sinkov.score(message);
                    string settings = Settings::generateSettingsStr(rotorCombinations[i],rotorCombinations[i+1],rotorCombinations[i+2],
                                                                    alphabet[l],alphabet[m],alphabet[r],
                                                                    'A','A','A',"");
                    container.insert(Result(settings,score, i/3));

                }
            }
        }
        cout << "grundstellung: " << i << endl;
    }
    container.save("step1_g.txt");
    return container;
}

ResultContainer checkStecker(string text, ResultContainer r) {

    std::multiset<Result> results = r.getResults();
    std::multiset<Result>::iterator it;
    Enigma machine;
    ResultContainer newResults(100000);
    Sinkov sinkov;
    int size = results.size();
    int c = 0;
    for(it = results.begin(); it != results.end(); ++it){

        for(int l1 = 0; l1 < 26; l1++ ) {
            for (int l2 = l1+1; l2 < 26; l2++) {
                string stecker = {alphabet[l1],alphabet[l2]};
                string newSettings = (it->setting)+stecker;
                machine.setSettings( newSettings );
                string crypt = machine.encode(text);
                newResults.insert(Result(newSettings,sinkov.score(crypt),0));
            }
        }
        c++;
        cout << c << "/" << size << endl;
    }

    newResults.save("step2_stecker_1.txt");
    return newResults;


}

void Crack::decipher(string text) {
    ResultContainer result(100000);
    result = checkGrundstellung(text);
    result = checkStecker(text,result);
    result = checkRingstellung(text,result);
    result = checkStecker(text,result);
    result = checkStecker(text,result);
    result.save("step3.txt");
}
