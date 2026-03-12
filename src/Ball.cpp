//Ball.cpp

#include "Ball.h"
#include <iostream>

/*
// Constructor
// Initializes the ball with its starting position, color, speed, and direction
// Parameters:
//   _window - pointer to the SFML window to draw the ball
//   WIDTH   - width of the game window
//   HEIGHT  - height of the game window
*/
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
    //initial position and color of the ball
    ballCircle.setPosition({posX, posY});
    ballCircle.setFillColor(ballColor);
}

// Draws itself
void Ball::drawBall()
{
    window->draw(ballCircle);
}

/*
// move
// Updates the ball's position based on speed, direction, and elapsed time.
// deltaTime - time elapsed since last frame (in seconds) for smooth movement
*/
void Ball::move(float deltaTime)
{
    // Update position
    posX = std::max(std::min(posX + (moveSpeed * deltaTime * directionX), maxPosX), minPosY);
    posY = std::max(std::min(posY + (moveSpeed * deltaTime * directionY), maxPosY), minPosY);
    std::cout << "time " << deltaTime << " move speed " << moveSpeed << " direction " << directionX << std::endl;
    std::cout << "setting pos x to " << posX << std::endl;
    ballCircle.setPosition({posX, posY});

    // If hit the edge, switch directions, reverse horizonal direction
    if (posX == minPosX || posX == maxPosX)
    {
        directionX *= -1;
    }
    if (posY == minPosY || posY == maxPosY)
    {
        directionY *= -1;
    }
}

/*
// checkPadCollision
// Checks for collision between the ball and the paddle
// padBounds - SFML FloatRect representing the paddle's position and size
*/
void Ball::checkPadCollision(sf::FloatRect padBounds)
{
    //ball's edges
    float ballLeft = posX;
    float ballRight = posX + (ballRadius * 2);
    float ballTop = posY;
    float ballBottom = posY + (ballRadius * 2);

    //paddle's edges
    float padLeft = padBounds.position.x;
    float padRight = padBounds.position.x + padBounds.size.x;
    float padTop = padBounds.position.y;
    float padBottom = padBounds.position.y + padBounds.size.y;

    // Checks overlap between the ball and the paddle
    if (ballRight > padLeft && ballLeft < padRight &&
        ballBottom > padTop && ballTop < padBottom)
    {
        posY = padTop - (ballRadius * 2);
        ballCircle.setPosition({posX, posY});
        directionY *= -1; //reverse vertical direction of ball
    }
}