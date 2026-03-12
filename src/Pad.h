//Pad.h

#ifndef PAD_H
#define PAD_H

#include <SFML/Graphics.hpp>

/*
// Pad Class
// Represents the player paddle in a breakout-style game. Handles rendering,
// horizontal movement, and provides bounding information for collision detection.
*/
class Pad
{

/*
//Constructor
//_window: Pointer to the SFML window to draw the paddle
//WIDTH, HEIGHT: Dimensions of the game window to constrain paddle movement
*/
public:
    Pad(sf::RenderWindow *_window, unsigned int WIDTH, unsigned int HEIGHT);
    void drawPad();
    void moveRight();
    void moveLeft();
    sf::FloatRect getBounds() const; //used for collision detection

/*
//Private Variables
*/
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