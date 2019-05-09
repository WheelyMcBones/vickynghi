//
// Created by freddy on 08/05/19.
//

#ifndef OSARRACINO_CONFIGSET_H
#define OSARRACINO_CONFIGSET_H

#include <iostream>
#include "../Player.h"

struct ConfigSet {
    int timeout = 5;
    Player player = Player::WHITE;
    std::string profile = "default";
    std::string host = "localhost";
    int port = -1;

    void print() {
        std::cout << "Player: "<<player<< std::endl;
        std::cout << "Timeout: "<<timeout << std::endl;
        std::cout << "Host: "<<host<< std::endl;
        std::cout << "Port: "<<port<<std::endl;
    }
};

#endif //OSARRACINO_CONFIGSET_H