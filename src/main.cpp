#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cmath>
#include "InputManager.h"
#include "MainManager.h"
#include "GameManager.h"
#include "GameColors.h"
#include "TitleScreen.h"
#include "Pad.h"
#include "Block.h"

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
    blocks.push_back(Block(&window, 1250, 50, 150, 150, GameColors::blockRedDim, GameColors::blockRed));
    blocks.push_back(Block(&window, 1500, 50, 150, 150, GameColors::blockGreenDim, GameColors::blockGreen));
    blocks.push_back(Block(&window, 250, 50, 150, 150, GameColors::blockBlueDim, GameColors::blockBlue));
    blocks.push_back(Block(&window, 750, 50, 150, 150, GameColors::blockYellowDim, GameColors::blockYellow));
    for (int i = 0; i < 6; i++)
    {
        blocks.push_back(Block(&window, 250 * i - 200, 350, 150, 150, GameColors::blockWhiteDim, GameColors::blockWhite));
    }

    TitleScreen titleScreen(&window, WIDTH, HEIGHT);
    PauseScreen pauseScreen(&window, WIDTH, HEIGHT);
    GameManager gameManager(&window, WIDTH, HEIGHT, blocks);
    MainManager mainManager(&window, &titleScreen, &pauseScreen, &gameManager);
    InputManager inputManager(&mainManager, &titleScreen, &pauseScreen, &gameManager);

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