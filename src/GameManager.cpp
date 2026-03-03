#include "GameManager.h"
#include <iostream>

GameManager::GameManager(sf::RenderWindow *_window, unsigned int WIDTH, unsigned int HEIGHT)
    : window(_window),
      gamePad(_window, WIDTH, HEIGHT),
      gameBall(_window, WIDTH, HEIGHT)
{
}

// Process automatic updates
void GameManager::updateGame(float timeSinceLastUpdate)
{
    gameBall.move(timeSinceLastUpdate);
}

// Draw the game
void GameManager::drawGame()
{
    gamePad.drawPad();
    gameBall.drawBall();
}

Pad &GameManager::pad() { return gamePad; }
Ball &GameManager::ball() { return gameBall; }