#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cmath>
#include "TitleScreen.h"
#include "Pad.h"
#include "GameManager.h"
#include "Block.h"
#include "InputManager.h"
#include "MainManager.h"

int main()
{
    const unsigned int WIDTH = 1920;
    const unsigned int HEIGHT = 1080;
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Breakout by HuskyHawks");
    window.setFramerateLimit(60);

    sf::Clock clock;

    // Create the list of blocks to be in the game
    // (in future, this should happen in some sort of level creator)
    vector<Block> blocks;
    blocks.push_back(Block(&window, 1250, 50, 150, 150, sf::Color(200, 0, 0), sf::Color(255, 0, 0)));
    blocks.push_back(Block(&window, 1500, 50, 150, 150, sf::Color(0, 200, 0), sf::Color(0, 255, 0)));
    blocks.push_back(Block(&window, 250, 50, 150, 150, sf::Color(0, 0, 200), sf::Color(0, 0, 255)));
    blocks.push_back(Block(&window, 750, 50, 150, 150, sf::Color(200, 200, 0), sf::Color(255, 255, 0)));
    for (int i = 0; i < 6; i++)
    {
        blocks.push_back(Block(&window, 250 * i - 200, 350, 150, 150, sf::Color(200, 200, 200), sf::Color(255, 255, 255)));
    }

    TitleScreen titleScreen(&window, WIDTH, HEIGHT);
    GameManager gameManager(&window, WIDTH, HEIGHT, blocks);
    MainManager mainManager(&window, &titleScreen, &gameManager);
    InputManager inputManager(&mainManager, &titleScreen, &gameManager);

    // Main loop
    while (window.isOpen())
    {
        float timeSinceLastFrame = clock.restart().asSeconds();
        mainManager.updateGame(timeSinceLastFrame);

        while (const std::optional event = window.pollEvent())
        {
            inputManager.processEvent(event);
        }

        window.clear();
        mainManager.updateWindow();
        window.display();
    }
}