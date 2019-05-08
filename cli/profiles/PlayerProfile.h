//
// Created by freddy on 23/04/19.
//

#ifndef OSARRACINO_PLAYERPROFILE_H
#define OSARRACINO_PLAYERPROFILE_H

#include <model/Board.h>
#include <string>

class PlayerProfile {
public:
    virtual std::string get_profile_name() = 0;
    virtual void print_configuration() = 0;
    virtual std::string calculate_move(const Board &b) = 0;
};

#endif //OSARRACINO_PLAYERPROFILE_H
