
#include "InputManager.h"
#include "PauseScreen.h"
#include <iostream>

InputManager::InputManager(MainManager *_mainManager, TitleScreen *_titleScreen, 
                           PauseScreen *_pauseScreen, GameManager *_gameManager)
    : mainManager(_mainManager),
      titleScreen(_titleScreen),
      pauseScreen(_pauseScreen),
      gameManager(_gameManager)
{
}

// Given an event, determine what to do, if anything
void InputManager::processEvent(const std::optional<sf::Event> &event)
{
    if (event->is<sf::Event::Closed>())
    {
        mainManager->window()->close();
    }

    switch (mainManager->getCurrentState())
    {
    case GameState::Menu:
    {
        processEventInMenu(event);
        break;
    }

    case GameState::Playing:
    {
        processEventWhilePlaying(event);
        break;
    }

    case GameState::Paused:
    {
        processEventWhilePaused(event);
        break;
    }

    case GameState::Controls:
    {
        processEventInControls(event);
        break;
    }

    case GameState::Credits:
    {
        processEventInCredits(event);
        break;
    }
    }
}

void InputManager::processEventInMenu(const std::optional<sf::Event> &event)
{
    if (event->is<sf::Event::KeyPressed>())
    {
        auto keyEvent = event->getIf<sf::Event::KeyPressed>();

        // Check for moving up or down in menu
        if (keyEvent->scancode == sf::Keyboard::Scancode::Up)
        {
            titleScreen->moveSelectionUp();
        }
        else if (keyEvent->scancode == sf::Keyboard::Scancode::Down)
        {
            titleScreen->moveSelectionDown();
        }

        // Check for menu button selection
        else if (keyEvent->scancode == sf::Keyboard::Scancode::Enter)
        {
            titleScreen->select(mainManager);
        }
    }
}

void InputManager::processEventWhilePlaying(const std::optional<sf::Event> &event)
{
    if (event->is<sf::Event::KeyPressed>())
    {
        auto keyEvent = event->getIf<sf::Event::KeyPressed>();

        // Check for moving the pad right or left
        if (keyEvent->scancode == sf::Keyboard::Scancode::Left)
        {
            gameManager->pad().moveLeft();
        }
        else if (keyEvent->scancode == sf::Keyboard::Scancode::Right)
        {
            gameManager->pad().moveRight();
        }
        else if (keyEvent->scancode == sf::Keyboard::Scancode::Escape)
        {
            mainManager->setCurrentState(GameState::Paused);
        }
    }
}

void InputManager::processEventWhilePaused(const std::optional<sf::Event> &event)
{
    if (event->is<sf::Event::KeyPressed>())
    {
        auto keyEvent = event->getIf<sf::Event::KeyPressed>();

        if (keyEvent->scancode == sf::Keyboard::Scancode::Up)
        {
            pauseScreen->moveSelectionUp();
        }
        else if (keyEvent->scancode == sf::Keyboard::Scancode::Down)
        {
            pauseScreen->moveSelectionDown();
        }
        else if (keyEvent->scancode == sf::Keyboard::Scancode::Enter)
        {
            pauseScreen->select(mainManager, gameManager);
        }
        else if (keyEvent->scancode == sf::Keyboard::Scancode::Escape)
        {
            // Resume game
            mainManager->setCurrentState(GameState::Playing);
            pauseScreen->resetSelection();  // Reset selection to Restart
        }
    }
}

void InputManager::processEventInControls(const std::optional<sf::Event> &event)
{
    // Controls menu input here
}

void InputManager::processEventInCredits(const std::optional<sf::Event> &event)
{
    // Credits input here
}
