// Made by Sp1ceForce

#ifndef RUSSIANROULETTE_PLAYER_H
#define RUSSIANROULETTE_PLAYER_H
#include <string>

class Player {
public:
    const std::string PlayerName;
    int lastPlace;
private:

public:
    Player(std::string name);

};


#endif //RUSSIANROULETTE_PLAYER_H
