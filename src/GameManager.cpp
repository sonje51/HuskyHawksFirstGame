#include "GameManager.h"

GameManager::GameManager(sf::RenderWindow *_window, unsigned int WIDTH, unsigned int HEIGHT)
    : window(_window),
      gamePad(_window, WIDTH, HEIGHT)
{
}

// Draw the game
void GameManager::drawGame()
{
    gamePad.drawPad();
}

Pad &GameManager::pad() { return gamePad; }