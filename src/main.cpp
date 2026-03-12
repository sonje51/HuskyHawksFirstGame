//main.cpp

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cmath>
#include "TitleScreen.h"
#include "Pad.h"
#include "GameManager.h"
#include "InputManager.h"
#include "MainManager.h"

/**
// Main function
// Initializes the game window, sets up game managers, and runs the main loop.
 */
int main()
{
    const unsigned int WIDTH = 1920; //window width
    const unsigned int HEIGHT = 1080; //window height
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Breakout by HuskyHawks");
    window.setFramerateLimit(60); //Limit the framerate to 60 frames per second

    sf::Clock clock;

    /*
    // Game component initializations
    */
    TitleScreen titleScreen(&window, WIDTH, HEIGHT); //title screen with game title and menu
    GameManager gameManager(&window, WIDTH, HEIGHT); //game logic, ball, boxes, etc.
    MainManager mainManager(&window, &titleScreen, &gameManager); //management for title screen and game manager
    InputManager inputManager(&mainManager, &titleScreen, &gameManager); //players inputs to game logic

    /*
    //Main Game Loop
    */
    while (window.isOpen())
    {
        float timeSinceLastFrame = clock.restart().asSeconds(); 
        mainManager.updateGame(timeSinceLastFrame);

        while (const std::optional event = window.pollEvent())
        {
            inputManager.processEvent(event);
        }

        //Rendering
        window.clear();
        mainManager.updateWindow();
        window.display();
    }
}