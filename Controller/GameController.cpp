// Made by Sp1ceForce



#include "GameController.h"
#include <functional>
#include "Player.h"
#include "ConsoleHelpers.h"

GameController::GameController(vector<Player *> &players,int revolverCapacity, int bulletsInDrum)
: _playerList(players), _totalBullets(bulletsInDrum), _revolverCapacity(revolverCapacity)
{
}

void GameController::StartNewGame() {
    _iterator=0;
    alivePlayers = _playerList;

    SetBulletsPosition();
    SpinDrum();
    DrawInterface();
}

void GameController::SetBulletsPosition() {
    srand(time(0));
    _hasBullet.clear();
    _hasBullet.resize(_revolverCapacity, false);
    for(int i = 0; i < _totalBullets; i++)
    {
        int randIndex = rand() % _revolverCapacity;
        if(_hasBullet[randIndex]) i--;
        else _hasBullet[randIndex] = true;
    }
    _bulletsLeft=_totalBullets;
}

void GameController::GameLoop() {
    StartNewGame();
    cin.ignore();
    while(_isPlaying){
        DrawInterface();
        HandleInput(&GameController::Shoot,&GameController::SpinDrum);
    }
}

void GameController::HandleInput(input_func FirstFunction, input_func SecondFunction) {
    string input;
    getline(cin,input);
    int command = atoi(input.c_str());
    switch (command) {
        case 1:
            (this->*FirstFunction)();
            break;
        case 2:
            //std::invoke(SecondFunction,this);
            (this->*SecondFunction)();
            break;
        default:
            printf("WRONG COMMAND, TRY AGAIN \r\n");
            HandleInput(FirstFunction,SecondFunction);
    }
}

void GameController::SpinDrum(){
    _currentPos = rand() % _revolverCapacity;
}

//Shoot from revolver
void GameController::Shoot(){
    if(_hasBullet[_currentPos]) {
        _hasBullet[_currentPos]=false;
        _bulletsLeft--;
        Die();}
    else{
        ProceedTurn();
    }
    if(_currentPos== _revolverCapacity-1) _currentPos=0;
    else _currentPos++;
}

//Pass the turn to next player
void GameController::ProceedTurn() {
    if(_iterator == alivePlayers.size() - 1) _iterator = 0;
    else _iterator++;
}

/*Handle some dying stuff:
 * Removing player from alive list
 * Drawing message about someone's death
 * Checking for conditions to end the game
 */
void GameController::Die() {
    ConsoleHelpers::ClearConsole();
    int playersCount = alivePlayers.size();
    //Draw interface
    DrawHeader();
    printf("BOOOM, %s is dead, %i players left \r\nPress enter to continue\r\n", alivePlayers[_iterator]->PlayerName.c_str(), playersCount - 1);
    DrawRevolver("========= |||) BOOM\"");

    //Remove dead player from alive list
    alivePlayers[_iterator]->lastPlace=playersCount;
    alivePlayers.erase(alivePlayers.begin() + _iterator);
   //Using cin.ignore so it won't be skipped
    cin.ignore();
    cin;
    //Check for endgame conditions
    if(playersCount-1 == 1 || _bulletsLeft==0){
        EndScreen();
    }
}

//Draw endscreen and handle 2 commands
void GameController::EndScreen() {
    ConsoleHelpers::ClearConsole();
    DrawHeader();
    DrawAlivePlayersList();
    printf("The end, there is no more players or bullets\r\nAvailable commands:\r\n1)Restart\r\n2)Exit the game\r\n");
    HandleInput(&GameController::StartNewGame,&GameController::EndGame);
}

//End the game
void GameController::EndGame(){
    _isPlaying= false;
}

//Draw revolver
void GameController::DrawRevolver(string boomSound = "") {
    printf("\r\n\r\n           _                \r\n");
    printf("         __+_____________|_\r\n");
    printf("        / |    |_________|_| %s\r\n",boomSound.c_str());
    printf("       /__|____|\r\n");
    printf("      /  /\r\n");
    printf("     /__/ \r\n\r\n\r\n");
}

//Draw Header
void GameController::DrawHeader() {
    printf("=================================================\r\n");
    printf("RUSSIAN ROULETTE\r\n");
    printf("=================================================\r\n");
}

//Draw full in-game interface
void GameController::DrawInterface() {
    ConsoleHelpers::ClearConsole();
    DrawHeader();
    DrawAlivePlayersList();
    DrawRevolver("");
    printf("Available commands:\r\n1)Shoot\r\n2)Spin revolver's drum\r\n");
}

//Draw every alive player
void GameController::DrawAlivePlayersList() {
    printf("This is %s's turn \r\nList of alive players:\r\n",alivePlayers[_iterator]->PlayerName.c_str());
    for (int i = 0; i < alivePlayers.size(); i++) {
        printf("%i) %s \r\n",i+1, alivePlayers[i]->PlayerName.c_str());
    }
    printf("=================================================\r\n");
}



