#include "InputManager.h"

InputManager::InputManager(MainManager *_mainManager, TitleScreen *_titleScreen, GameManager *_gameManager)
    : mainManager(_mainManager),
      titleScreen(_titleScreen),
      gameManager(_gameManager)
{
}

// Given an event, determine what to do, if anything
void InputManager::processEvent(const std::optional<sf::Event> event)
{
    if (event->is<sf::Event::Closed>())
    {
        mainManager->window()->close();
    }

    if (mainManager->showingTitleScreen() && event->is<sf::Event::KeyPressed>())
    {
        mainManager->continueFromTitleScreen();
    }
}

// Do the updates that don't require an event object
void InputManager::update()
{
    if (gameManager != nullptr)
    {
        // Look for movement input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            gameManager->pad().moveLeft();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            gameManager->pad().moveRight();
        }
    }
}