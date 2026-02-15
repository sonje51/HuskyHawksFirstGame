#ifndef MAIN_MANAGER_H
#define MAIN_MANAGER_H

#include "TitleScreen.h"
#include "GameManager.h"
#include "InputManager.h"

class MainManager
{
public:
    MainManager(sf::RenderWindow *window, TitleScreen *titleScreen,
                GameManager *gameManager);

    void updateWindow();

    void continueFromTitleScreen();

    sf::RenderWindow *window();
    TitleScreen *titleScreen();
    GameManager *gameManager();
    bool showingTitleScreen();
    bool playingGame();

private:
    sf::RenderWindow *_window;
    TitleScreen *_titleScreen;
    GameManager *_gameManager;

    bool _showingTitleScreen;
    bool _playingGame;
};

#include "MainManager.cpp"
#endif