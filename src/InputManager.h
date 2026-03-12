//InputManager.h

#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "MainManager.h"
#include "TitleScreen.h"
#include "GameManager.h"
#include <optional>

/*
// InputManager Class
// Handles player input and appropriate game components
// depending on the current game state (menu, playing, paused, etc.).
*/
class InputManager
{

/*
// _mainManager: pointer to the MainManager (game state)
// _titleScreen: pointer to the TitleScreen manager (menu)
// _gameManager: pointer to the GameManager 
*/
public:
    InputManager(MainManager *_mainManager, TitleScreen *_titleScreen, GameManager *_gameManager);

    void processEvent(const std::optional<sf::Event> &event); //general event processing

    /*
    //More Specific Game Processing
    */
    void processEventInMenu(const std::optional<sf::Event> &event); //Menu input
    void processEventWhilePlaying(const std::optional<sf::Event> &event); //Playing game input
    void processEventWhilePaused(const std::optional<sf::Event> &event); //Paused input
    void processEventInControls(const std::optional<sf::Event> &event); //Controls screen input
    void processEventInCredits(const std::optional<sf::Event> &event); //Credits screen input

/*
//Private Variables
*/
private:
    MainManager *mainManager; //points to MainManager
    TitleScreen *titleScreen; //points to TitleScreen Manager
    GameManager *gameManager; //points to GameManager
};

#endif