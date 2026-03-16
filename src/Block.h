#ifndef BLOCK_H
#define BLOCK_H

#include <SFML/Graphics.hpp>
#include "GameColors.h"
using namespace std;

class Block
{
public:
    Block(sf::RenderWindow *_window, int posX_, int posY_, unsigned int blockWidth_,
          unsigned int blockHeight_, sf::Color innerColor_, sf::Color outerColor_);
    void drawBlock();
    sf::FloatRect getBounds() const;

private:
    static float edgeSize;

    sf::RenderWindow *window;

    int blockWidth;
    int blockHeight;
    float posY;
    float posX;

    sf::Color outerColor;
    sf::Color innerColor;
    sf::RectangleShape outerRect;
    sf::RectangleShape innerRect;
};

#endif