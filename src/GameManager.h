#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "Pad.h"

class GameManager
{
public:
    GameManager(sf::RenderWindow *window, unsigned int WIDTH, unsigned int HEIGHT);
    void drawGame();
    Pad &pad();

private:
    sf::RenderWindow *window;
    Pad gamePad;
};

#endif