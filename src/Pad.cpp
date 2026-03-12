//Pad.cpp

#include <SFML/Graphics.hpp>
#include "Pad.h"
#include <iostream>

/*
// Constructor
// Initializes the paddle with its starting position, size, color, and movement
// boundaries. Positions the paddle horizontally centered near the bottom.
// Parameters:
// _window - pointer to the SFML window for drawing
// WIDTH - width of the game window
// HEIGHT - height of the game window
*/
Pad::Pad(sf::RenderWindow *_window, unsigned int WIDTH, unsigned int HEIGHT)
    : window(_window),
      padWidth(200),
      padHeight(40),
      posX((WIDTH - padWidth) / 2),
      posY(HEIGHT - padHeight - 100),
      minPosX(25),
      maxPosX(WIDTH - padWidth - 25),
      moveSpeed(20),
      padColor(10, 200, 10),
      padRect(sf::Vector2f(padWidth, padHeight))
{
    //Sets initial position and color of the paddle
    padRect.setPosition({posX, posY});
    padRect.setFillColor(padColor);
}

/*
// drawPad
// Draws the paddle on the SFML window
*/
void Pad::drawPad()
{
    window->draw(padRect);
}

/*
// moveRight
// Moves the paddle to the right. Stops at maxPosX to prevent leaving the window.
*/
void Pad::moveRight()
{
    posX = std::min(posX + moveSpeed, maxPosX);
    padRect.setPosition({posX, posY});
}

/*
// moveLeft
// Moves the paddle to the left. Stops at minPosX to prevent paddle from going outside window.
*/
void Pad::moveLeft()
{
    posX = std::max(posX - moveSpeed, minPosX);
    padRect.setPosition({posX, posY});
}

/*
// getBounds
// Returns the paddle's bounding rectangle for collision detection
*/
sf::FloatRect Pad::getBounds() const
{
    return padRect.getGlobalBounds();
}