#include "MainManager.h"

MainManager::MainManager(sf::RenderWindow *window, TitleScreen *titleScreen,
                         GameManager *gameManager)
    : _window(window),
      _titleScreen(titleScreen),
      _gameManager(gameManager),
      _showingTitleScreen(true),
      _playingGame(false)
{
}

// Update the window
void MainManager::updateWindow()
{
    if (_showingTitleScreen)
    {
        _titleScreen->drawTitleScreen();
    }
    if (_playingGame)
    {
        _gameManager->drawGame();
    }
}

// Advance the game from being in the title screen
void MainManager::continueFromTitleScreen()
{
    _showingTitleScreen = false;
    _playingGame = true;
}

// Getters
sf::RenderWindow *MainManager::window() { return _window; }
TitleScreen *MainManager::titleScreen() { return _titleScreen; }
GameManager *MainManager::gameManager() { return _gameManager; }
bool MainManager::showingTitleScreen() { return _showingTitleScreen; }
bool MainManager::playingGame() { return _playingGame; }