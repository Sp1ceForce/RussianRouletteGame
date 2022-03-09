// Made by Sp1ceForce

#ifndef RUSSIANROULETTE_GAMECONTROLLER_H
#define RUSSIANROULETTE_GAMECONTROLLER_H
#include <iostream>
#include <vector>
#include <string>
#include <random>
class Player;
using namespace std;

class GameController {
    typedef void (GameController::*input_func)();
private:
    //Bool that defines if game should continue
    bool _isPlaying;
    //Index of current player
    int _iterator;
    //Vector with all ALIVE players
    vector<Player*> alivePlayers;
    //Vector with all players
    vector<Player*> _playerList;
    //Current drum position
    int _currentPos;
    //How many bullets left
    int _bulletsLeft;
    //Int that says how many bullets should be in the drum
    int _totalBullets;
    //Maximum capacity of revolver drum
    int _revolverCapacity;
    //Vector that represents revolver drum
    //True - if bullet inside
    //False - if it's empty
    vector<bool> _hasBullet;
public:
    void GameLoop();
    GameController(vector<Player*>& players, int revolverCapacity, int bulletsInDrum);
private:

    void DrawRevolver(string boomSound);

    void DrawHeader();

    void StartNewGame();

    void ProceedTurn();

    void SetBulletsPosition();

    void Die();

    void Shoot();

    void SpinDrum();

    void HandleInput(input_func FirstFunc, input_func SecondFunction);

    void DrawInterface();

    void EndScreen();

    void DrawAlivePlayersList();

    void EndGame();
};


#endif //RUSSIANROULETTE_GAMECONTROLLER_H
