#ifndef PAD_H
#define PAD_H

#include <SFML/Graphics.hpp>

class Pad
{
public:
    Pad(sf::RenderWindow *_window, unsigned int WIDTH, unsigned int HEIGHT);
    void drawPad();
    void moveRight();
    void moveLeft();
    sf::FloatRect getBounds() const;

private:
    sf::RenderWindow *window;

    const int padWidth;
    const int padHeight;
    const float posY;
    float posX;
    const float minPosX;
    const float maxPosX;
    const int moveSpeed;

    const sf::Color padColor;
    sf::RectangleShape padRect;
};

#endif