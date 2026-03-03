#ifndef MAIN_MANAGER_H
#define MAIN_MANAGER_H

#include "TitleScreen.h"
#include "GameManager.h"
#include "GameState.h"

class MainManager
{
public:
    MainManager(sf::RenderWindow *window, TitleScreen *titleScreen,
                GameManager *gameManager);

    void updateGame(float timeSinceLastUpdate);
    void updateWindow();

    sf::RenderWindow *window();
    TitleScreen *titleScreen();
    GameManager *gameManager();
    GameState getCurrentState();
    void setCurrentState(const GameState &state);

private:
    sf::RenderWindow *_window;
    TitleScreen *_titleScreen;
    GameManager *_gameManager;

    GameState currentState;
};

#endif