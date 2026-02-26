#include "MainManager.h"

MainManager::MainManager(sf::RenderWindow *window, TitleScreen *titleScreen,
                         GameManager *gameManager)
    : _window(window),
      _titleScreen(titleScreen),
      _gameManager(gameManager),
      currentState(GameState::Menu)
{
}

// Update the window
void MainManager::updateWindow()
{
    if (currentState == GameState::Menu)
    {
        _titleScreen->drawTitleScreen();
    }
    if (currentState == GameState::Playing)
    {
        _gameManager->drawGame();
    }
}

// Getters and setters
sf::RenderWindow *MainManager::window() { return _window; }
TitleScreen *MainManager::titleScreen() { return _titleScreen; }
GameManager *MainManager::gameManager() { return _gameManager; }
GameState MainManager::getCurrentState() { return currentState; }
void MainManager::setCurrentState(const GameState &state) { currentState = state; }