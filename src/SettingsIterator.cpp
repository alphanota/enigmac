//
// Created by angel on 7/1/19.
//

#include <iostream>
#include "SettingsIterator.h"
#include "Crack.h"
#include "Settings.h"

SettingsIterator::SettingsIterator(int rotorComboStartrotorCombo, int l, int m, int r) :
rotorCombo(rotorCombo), leftGS(l), middleGS(m), rightGS(r) {}

std::vector<std::string> SettingsIterator::next(int n) {
    int limit = 0;
    std::vector<std::string> settings;
    settings.reserve(limit);
    for(rotorCombo; rotorCombo < 1008; rotorCombo+=3 ) {
        for(leftGS; leftGS < 26; leftGS++) {
            for(middleGS; middleGS < 26; middleGS++) {
                for (rightGS; rightGS < 26; rightGS++){

                    if (limit > n) {
                        return settings;
                    }



                    string setting = Settings::generateSettingsStr(
                            rotorCombinations[rotorCombo],
                            rotorCombinations[rotorCombo+1],
                            rotorCombinations[rotorCombo+2],
                            alphabet[leftGS],
                            alphabet[middleGS],
                            alphabet[rightGS],
                            'A','A','A',"");
                    settings.push_back(setting);
                    limit +=1;
                }
                rightGS = 0;
            }
            middleGS = 0;
        }
            leftGS = 0;
    }
    rotorCombo = 0;

    return settings;
}


std::vector<std::string> SettingsIterator::next(int rStart, int rEnd) {

    std::vector<std::string> settings;
    settings.reserve((rEnd-rStart)*3);
    for(int rotorCombo = rStart*3; rotorCombo < rEnd*3; rotorCombo+=3 ) {
        for(int l = 0; l < 26; l++) {
            for(int m = 0; m < 26; m++) {
                for (int r =0; r < 26; r++){


                    string setting = Settings::generateSettingsStr(
                            rotorCombinations[rotorCombo],
                            rotorCombinations[rotorCombo+1],
                            rotorCombinations[rotorCombo+2],
                            alphabet[l],
                            alphabet[m],
                            alphabet[r],
                            'A','A','A',"");
                    settings.push_back(setting);


                    //cout << "rstart: " << rStart << " " << "rEnd: " << rEnd << " , " << setting << std::endl;
                }
            }
        }

    }
    cout << "settingsIt: " << settings.size() << endl;

    return settings;
}


SettingsIterator::SettingsIterator() : rotorCombo(0), leftGS(0), middleGS(0), rightGS(0) {}

