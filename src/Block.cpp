#include "Block.h"

float Block::edgeSize = 10;

Block::Block(sf::RenderWindow *_window, int posX_, int posY_, unsigned int blockWidth_, unsigned int blockHeight_, sf::Color outerColor_, sf::Color innerColor_)
    : window(_window),
      blockWidth(blockWidth_),
      blockHeight(blockHeight_),
      posX(posX_),
      posY(posY_),
      outerColor(outerColor_),
      innerColor(innerColor_),
      innerRect(sf::Vector2f(blockWidth - (edgeSize * 2), blockHeight - (edgeSize * 2))),
      outerRect(sf::Vector2f(blockWidth, blockHeight))
{
    outerRect.setPosition({posX, posY});
    outerRect.setFillColor(outerColor);
    innerRect.setPosition({posX + edgeSize, posY + edgeSize});
    innerRect.setFillColor(innerColor);
}

// Draw the block to the window
void Block::drawBlock()
{
    window->draw(outerRect);
    window->draw(innerRect);
}

sf::FloatRect Block::getBounds() const { return outerRect.getGlobalBounds(); }