#include <SFML/Graphics.hpp>
#include "Pad.h"
#include <iostream>

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
    padRect.setPosition({posX, posY});
    padRect.setFillColor(padColor);
}

// Draws itself
void Pad::drawPad()
{
    window->draw(padRect);
}

// Moves right unless too far right
void Pad::moveRight()
{
    posX = std::min(posX + moveSpeed, maxPosX);
    padRect.setPosition({posX, posY});
}

// Moves left unless too far left
void Pad::moveLeft()
{
    posX = std::max(posX - moveSpeed, minPosX);
    padRect.setPosition({posX, posY});
}

sf::FloatRect Pad::getBounds() const
{
    return padRect.getGlobalBounds();
}