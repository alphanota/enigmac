//
// Created by angel on 5/17/19.
//

#ifndef ENIGMAC_SETTINGS_H
#define ENIGMAC_SETTINGS_H
#include <string>

class Settings {

private:
    std::string settings;

public:
    

    Settings();

    Settings(int w0, int w1, int w2, 
            char r0, char r1, char r2, 
            char g0, char g1, char g2,
            std::string stecker);

    static std::string generateSettingsStr(int w0, int w1, int w2,
                                          char r0, char r1, char r2,
                                          char g0, char g1, char g2,
                                          std::string stecker);


    Settings(std::string settings);


};


#endif //ENIGMAC_SETTINGS_H
