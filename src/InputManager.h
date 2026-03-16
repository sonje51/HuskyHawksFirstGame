#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "MainManager.h"
#include "TitleScreen.h"
#include "GameManager.h"
#include <optional>

class PauseScreen;

class InputManager
{
public:
    InputManager(MainManager *_mainManager, TitleScreen *_titleScreen, 
                PauseScreen *_pauseScreen, GameManager *_gameManager);

    void processEvent(const std::optional<sf::Event> &event);

    void processEventInMenu(const std::optional<sf::Event> &event);
    void processEventWhilePlaying(const std::optional<sf::Event> &event);
    void processEventWhilePaused(const std::optional<sf::Event> &event);
    void processEventInControls(const std::optional<sf::Event> &event);
    void processEventInCredits(const std::optional<sf::Event> &event);

private:
    MainManager *mainManager;
    TitleScreen *titleScreen;
    PauseScreen *pauseScreen;
    GameManager *gameManager;
};

#endif