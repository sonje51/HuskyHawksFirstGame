//MainManager.h

#ifndef MAIN_MANAGER_H
#define MAIN_MANAGER_H

#include "TitleScreen.h"
#include "GameManager.h"
#include "GameState.h"


/*
// MainManager Class
// main coordinator between the different game contents.
// Manages the current game state, updates game logic, and updates rendering.
*/
class MainManager
{

/*
// Constructor
// window: pointer to the SFML window
// titleScreen: pointer to the TitleScreen manager
// gameManager: pointer to the GameManager
*/
public:
    MainManager(sf::RenderWindow *window, TitleScreen *titleScreen,
                GameManager *gameManager);

    void updateGame(float timeSinceLastUpdate); //updates game from current state
    void updateWindow(); //updates the window from current state

    /*
    Accessors
    */
    sf::RenderWindow *window(); //points to window
    TitleScreen *titleScreen(); //points to title screen
    GameManager *gameManager(); // points to game manager
    GameState getCurrentState();
    void setCurrentState(const GameState &state);

/*
//Private Variables
*/
private:
    sf::RenderWindow *_window;
    TitleScreen *_titleScreen;
    GameManager *_gameManager;

    GameState currentState; //tracking of the current state of the game
};

#endif