//
// Created by angel on 7/1/19.
//

#ifndef ENIGMAC_SETTINGSITERATOR_H
#define ENIGMAC_SETTINGSITERATOR_H

#include <vector>
#include <string>

class SettingsIterator{
private:
    int rotorCombo;
    int leftGS;
    int middleGS;
    int rightGS;


public:
    SettingsIterator();
    SettingsIterator(int rotorCombo, int l, int m, int r);
    std::vector<std::string> next(int n);

    std::vector<std::string> next(int rStart, int rEnd);
};

#endif //ENIGMAC_SETTINGSITERATOR_H
