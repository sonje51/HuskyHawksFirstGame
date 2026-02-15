#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "MainManager.h"
#include "TitleScreen.h"
#include "GameManager.h"

class InputManager
{
public:
    InputManager(MainManager *_mainManager, TitleScreen *_titleScreen, GameManager *_gameManager);

    void s(MainManager *ts);

    void processEvent(const std::optional<sf::Event> event);
    void update();

private:
    MainManager *mainManager;
    TitleScreen *titleScreen;
    GameManager *gameManager;
};

#include "InputManager.cpp"
#endif