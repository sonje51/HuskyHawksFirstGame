#include "Ball.h"
#include <iostream>

Ball::Ball(sf::RenderWindow *_window, unsigned int WIDTH, unsigned int HEIGHT)
    : window(_window),
      ballRadius(15),
      posX((WIDTH / 2) - ballRadius),
      posY((HEIGHT / 2) - ballRadius),
      minPosX(25),
      maxPosX(WIDTH - (ballRadius * 2) - 25),
      minPosY(25),
      maxPosY(HEIGHT - (ballRadius * 2) - 25),
      moveSpeed(150),
      ballColor(10, 10, 200),
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
    std::cout << "time " << deltaTime << " move speed " << moveSpeed << " direction " << directionX << std::endl;
    std::cout << "setting pos x to " << posX << std::endl;
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