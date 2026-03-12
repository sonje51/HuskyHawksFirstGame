//Ball.h

#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>

/*
// Ball Class
// Represents the ball in a breakout-style game. Handles rendering, movement,
// and collisions with the paddle. The ball moves within a constrained window
// and bounces off walls and the paddle.
*/
class Ball
{

/*
// Constructor
//
// _window: Pointer to the SFML window where the ball will be drawn.
// WIDTH, HEIGHT: Dimensions of the game window, used to set movement limits.
*/
public:
    Ball(sf::RenderWindow *_window, unsigned int WIDTH, unsigned int HEIGHT);
    void drawBall(); //Draws the ball on the window using the SFML CircleShape.
    void move(float deltaTime); //Moves the ball according to its speed and current direction.
    void checkPadCollision(sf::FloatRect padBounds); //Checks if the ball collides with the paddle and adjusts direction if it does.

//Variables
private:
    sf::RenderWindow *window;
    const int ballRadius; 
    float posY; 
    float posX;
    const float minPosX;
    const float maxPosX;
    const float minPosY;
    const float maxPosY;
    int directionX;      // 1 or -1
    int directionY;      // 1 or -1
    const int moveSpeed; // In pixels/second

    const sf::Color ballColor;
    sf::CircleShape ballCircle;
};

#endif