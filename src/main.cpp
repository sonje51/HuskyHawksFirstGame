#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cmath>
#include "TitleScreen.h"
#include "Pad.h"
#include "GameManager.h"
#include "InputManager.h"
#include "MainManager.h"

int main()
{
    const unsigned int WIDTH = 1920;
    const unsigned int HEIGHT = 1080;
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Breakout by HuskyHawks");
    window.setFramerateLimit(60);

    TitleScreen titleScreen(&window, WIDTH, HEIGHT);
    GameManager gameManager(&window, WIDTH, HEIGHT);
    MainManager mainManager(&window, &titleScreen, &gameManager);
    InputManager inputManager(&mainManager, &titleScreen, &gameManager);

    // Main loop
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            inputManager.processEvent(event);
        }

        window.clear();
        mainManager.updateWindow();
        window.display();
    }
}