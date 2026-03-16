#include "Ball.h"
#include <iostream>
#include <cmath>

const float PI = 3.14159265358979323846;

Ball::Ball(sf::RenderWindow *_window, unsigned int WIDTH, unsigned int HEIGHT)
    : window(_window),
      ballRadius(15),
      posX((WIDTH / 2) - ballRadius),
      posY((HEIGHT / 2) - ballRadius),
      minPosX(25),
      maxPosX(WIDTH - (ballRadius * 2) - 25),
      minPosY(25),
      maxPosY(HEIGHT - (ballRadius * 2) - 25),
      moveSpeed(300),
      ballColor(0, 255, 200),
      ballCircle(ballRadius),
      directionX(1),
      directionY(1)
{
    ballCircle.setPosition({posX, posY});
    ballCircle.setFillColor(ballColor);
}

// Draws itself
void Ball::drawBall()
{
    window->draw(ballCircle);
}

// Moves the ball in the direction it is currently going
void Ball::move(float deltaTime)
{
    // Update position
    posX = std::max(std::min(posX + (moveSpeed * deltaTime * directionX), maxPosX), minPosY);
    posY = std::max(std::min(posY + (moveSpeed * deltaTime * directionY), maxPosY), minPosY);
    ballCircle.setPosition({posX, posY});

    // If hit the edge, switch directions
    if (posX == minPosX || posX == maxPosX)
    {
        directionX *= -1;
    }
    if (posY == minPosY || posY == maxPosY)
    {
        directionY *= -1;
    }
}

void Ball::checkPadCollision(sf::FloatRect padBounds)
{
    float ballLeft = posX;
    float ballRight = posX + (ballRadius * 2);
    float ballTop = posY;
    float ballBottom = posY + (ballRadius * 2);

    float padLeft = padBounds.position.x;
    float padRight = padBounds.position.x + padBounds.size.x;
    float padTop = padBounds.position.y;
    float padBottom = padBounds.position.y + padBounds.size.y;

    if (ballRight > padLeft && ballLeft < padRight &&
        ballBottom > padTop && ballTop < padBottom)
    {
        posY = padTop - (ballRadius * 2);
        ballCircle.setPosition({posX, posY});
        directionY *= -1;
    }
}

// Checks for collisions with all blocks in the given vector
// Returns the index of the block it collides with, if any
int Ball::checkBlockCollision(vector<Block> &blocks)
{
    sf::FloatRect ballBound = ballCircle.getGlobalBounds();

    // Go through all blocks
    for (int i = 0; i < blocks.size(); i++)
    {
        sf::FloatRect blockBounds = blocks[i].getBounds();

        // If ball collides with the block, bounce and return the index of block
        if (blockBounds.findIntersection(ballBound))
        {
            // Get the angle between the two shapes
            sf::Vector2f blockCenter = blockBounds.getCenter();
            sf::Vector2f ballCenter = ballBound.getCenter();
            float angle = atan2(ballCenter.y - blockCenter.y,
                                ballCenter.x - blockCenter.x) *
                          180 / PI;

            // Use the angle to determine which way the ball should bounce
            if ((blockCenter.x < ballCenter.x && abs(angle) < 45) || (blockCenter.x > ballCenter.x && abs(angle) > 135))
            {
                directionX *= -1;
            }
            else
            {
                directionY *= -1;
            }

            return i;
        }
    }

    return -1; // No collisions
}