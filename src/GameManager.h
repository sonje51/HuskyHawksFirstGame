#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "Pad.h"
#include "Ball.h"

class GameManager
{
public:
    GameManager(sf::RenderWindow *window, unsigned int WIDTH, unsigned int HEIGHT);
    void updateGame(float timeSinceLastUpdate);
    void drawGame();
    Pad &pad();
    Ball &ball();

private:
    sf::RenderWindow *window;
    Pad gamePad;
    Ball gameBall;
};

#endif