//MainManager.cpp

#include "MainManager.h"

/*
// Constructor
// Initializes MainManager with pointers to the window, TitleScreen, and GameManager.
// Sets the initial game state to the Menu Page.
*/
MainManager::MainManager(sf::RenderWindow *window, TitleScreen *titleScreen,
                         GameManager *gameManager)
    : _window(window),
      _titleScreen(titleScreen),
      _gameManager(gameManager),
      currentState(GameState::Menu) //Game starts on the Menu Page
{
}

/*
// updateGame
// Processes automatic updates depending on the current game state
// timeSinceLastUpdate: elapsed time since the last frame
*/
void MainManager::updateGame(float timeSinceLastUpdate)
{
    if (currentState == GameState::Playing) //if user is playing the game
    {
        _gameManager->updateGame(timeSinceLastUpdate); //then the game updates
    }
}

/*
// updateWindow
// Updates what is drawn to the window depending on the current game state
*/
void MainManager::updateWindow()
{
    if (currentState == GameState::Menu) //if the state is menu
    {
        _titleScreen->drawTitleScreen(); // then draws the title screen
    }
    if (currentState == GameState::Playing) //if the state is playing
    {
        _gameManager->drawGame(); //then the game is drawn
    }
}

// Getters and Setters
sf::RenderWindow *MainManager::window() { return _window; } //returns window
TitleScreen *MainManager::titleScreen() { return _titleScreen; } //return title screen manager
GameManager *MainManager::gameManager() { return _gameManager; } //returns game manager 
GameState MainManager::getCurrentState() { return currentState; } //returns current state
void MainManager::setCurrentState(const GameState &state) { currentState = state; } //sets current game state