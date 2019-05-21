//
// Created by angel on 5/17/19.
//

#include <iostream>
#include "Settings.h"

Settings::Settings() {settings="AAAAAAAAA";}

Settings::Settings(int w0, int w1, int w2, char r0, char r1, char r2, char g0, char g1, char g2, std::string stecker) {
    settings.resize(9+stecker.length(),'A');
    settings[0] = '0' + w0;
    settings[1] = '0' + w1;
    settings[2] = '0' + w2;
    settings[3] = r0;
    settings[4] = r1;
    settings[5] = r2;
    settings[6] = g0;
    settings[7] = g1;
    settings[8] = g2;
    settings.append(stecker);
}

std::string Settings::generateSettingsStr(int w0, int w1, int w2, char r0, char r1, char r2, char g0, char g1, char g2,
                                          std::string stecker) {

    std::string str;
    str.resize(9+stecker.length(),'A');
    str[0] = '0' + w0;
    str[1] = '0' + w1;
    str[2] = '0' + w2;
    str[3] = r0;
    str[4] = r1;
    str[5] = r2;
    str[6] = g0;
    str[7] = g1;
    str[8] = g2;
    str.append(stecker);

    return str;
}

