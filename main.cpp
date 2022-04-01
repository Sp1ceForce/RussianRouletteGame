
// Made by Sp1ceForce

#include "GameController.h"
#include "Player.h"
int main() {
    vector<Player*> playerList;
    int plCount;
    int totalBullets;
    int drumCapacity;
    srand(time(0));
    printf("=================================================\r\n");
    printf("RUSSIAN ROULETTE\r\n");
    printf("=================================================\r\n");
    printf("\r\n\r\n           _                \r\n");
    printf("         __+_____________|_\r\n");
    printf("        / |    |_________|_|\r\n");
    printf("       /__|____|\r\n");
    printf("      /  /\r\n");
    printf("     /__/ \r\n\r\n\r\n");
    printf("How many players will play: ");
    cin >> plCount;
    printf("Enter new player's names\r\n");
    for (int i = 0; i < plCount; ++i) {
        string name;
        printf("%i player's name:", i+1);
        cin >> name;
        playerList.push_back(new Player(name));
    }
    printf("How many bullets can revolver hold: ");
    cin >> drumCapacity;
    printf("How many bullets should be in the drum: ");
    cin >> totalBullets;
    GameController* controller = new GameController(playerList,drumCapacity,totalBullets);
    controller->GameLoop();
    return 0;
}
