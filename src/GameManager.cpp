#include "GameManager.h"
#include <iostream>

GameManager::GameManager(sf::RenderWindow *_window, unsigned int WIDTH, unsigned int HEIGHT,
                         vector<Block> blocks_)
    : window(_window),
      gamePad(_window, WIDTH, HEIGHT),
      gameBall(_window, WIDTH, HEIGHT),
      blocks(blocks_)
{
}

// Process automatic updates
void GameManager::updateGame(float timeSinceLastUpdate)
{
    gameBall.move(timeSinceLastUpdate);
    gameBall.checkPadCollision(gamePad.getBounds());

    // Process collisions with blocks, and destroy any box it collides with
    int collisionIndex = gameBall.checkBlockCollision(blocks);
    if (collisionIndex != -1)
    {
        blocks.erase(blocks.begin() + collisionIndex);
    }
}

// Draw the game
void GameManager::drawGame()
{
    gamePad.drawPad();
    gameBall.drawBall();
    for (Block block : blocks)
    {
        block.drawBlock();
    }
}

Pad &GameManager::pad() { return gamePad; }
Ball &GameManager::ball() { return gameBall; }
