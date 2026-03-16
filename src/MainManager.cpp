#include "MainManager.h"

MainManager::MainManager(sf::RenderWindow *window, TitleScreen *titleScreen,
                         PauseScreen *pauseScreen, GameManager *gameManager)
    : _window(window),
      _titleScreen(titleScreen),
      _gameManager(gameManager),
      _pauseScreen(pauseScreen),
      currentState(GameState::Menu)
{
}

// Process automatic updates
void MainManager::updateGame(float timeSinceLastUpdate)
{
    if (currentState == GameState::Playing)
    {
        _gameManager->updateGame(timeSinceLastUpdate);
    }
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
    if (currentState == GameState::Paused)
    {
        _gameManager->drawGame();
        _pauseScreen->draw();
    }
}

// Getters and setters
sf::RenderWindow *MainManager::window() { return _window; }
TitleScreen *MainManager::titleScreen() { return _titleScreen; }
GameManager *MainManager::gameManager() { return _gameManager; }
GameState MainManager::getCurrentState() { return currentState; }
void MainManager::setCurrentState(const GameState &state) { currentState = state; }