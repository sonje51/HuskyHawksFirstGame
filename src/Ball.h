#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>

class Ball
{
public:
    Ball(sf::RenderWindow *_window, unsigned int WIDTH, unsigned int HEIGHT);
    void drawBall();
    void move(float deltaTime);
    void checkPadCollision(sf::FloatRect padBounds);

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