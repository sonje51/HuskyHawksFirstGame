#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "Pad.h"
#include "Ball.h"
#include "Block.h"
#include <vector>
using namespace std;

class GameManager
{
public:
    GameManager(sf::RenderWindow *window, unsigned int WIDTH, unsigned int HEIGHT,
                vector<Block> blocks);
    void updateGame(float timeSinceLastUpdate);
    void drawGame();
    Pad &pad();
    Ball &ball();

private:
    sf::RenderWindow *window;
    Pad gamePad;
    Ball gameBall;
    vector<Block> blocks;
};

#endif