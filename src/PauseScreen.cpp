#include "PauseScreen.h"
#include "MainManager.h"
#include "GameManager.h"
#include <iostream>

PauseScreen::PauseScreen(sf::RenderWindow* window, unsigned int WIDTH, unsigned int HEIGHT)
    : _window(window), 
    _selectedOption(0),
    _pauseText(_font),
    _resumeText(_font),
    _restartText(_font),
    _quitText(_font)
{
    // Load font (same as TitleScreen)
    std::string fontPath = "../../../assets/fonts/RetroRegular.ttf";
    if (!_font.openFromFile(fontPath))
    {
        std::cerr << "Failed to load assets/fonts/RetroRegular.ttf\n";
    }

    // Create semi-transparent overlay
    _overlay.setSize(sf::Vector2f((float)WIDTH, (float)HEIGHT));
    _overlay.setFillColor(sf::Color(0, 0, 0, 153)); // Black with 60% opacity (153/255)

    // Pause title
    _pauseText.setFont(_font);
    _pauseText.setString("PAUSED");
    _pauseText.setCharacterSize(120);
    _pauseText.setFillColor(sf::Color::White);
    centerOrigin(_pauseText);
    _pauseText.setPosition({WIDTH * 0.5f, HEIGHT * 0.3f});

    // Menu options
    _resumeText.setFont(_font);
    _resumeText.setString("Resume");
    _resumeText.setCharacterSize(50);
    _resumeText.setFillColor(sf::Color::White);
    centerOrigin(_resumeText);
    _resumeText.setPosition({WIDTH * 0.5f, HEIGHT * 0.45f});

    _restartText.setFont(_font);
    _restartText.setString("Restart");
    _restartText.setCharacterSize(50);
    _restartText.setFillColor(sf::Color::White);
    centerOrigin(_restartText);
    _restartText.setPosition({WIDTH * 0.5f, HEIGHT * 0.55f});

    _quitText.setFont(_font);
    _quitText.setString("Quit to Menu");
    _quitText.setCharacterSize(50);
    _quitText.setFillColor(sf::Color::White);
    centerOrigin(_quitText);
    _quitText.setPosition({WIDTH * 0.5f, HEIGHT * 0.65f});
}

void PauseScreen::centerOrigin(sf::Text& text)
{
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin({bounds.position.x + bounds.size.x / 2.f,
                    bounds.position.y + bounds.size.y / 2.f});
}

void PauseScreen::draw()
{
    // Draw semi-transparent overlay first
    _window->draw(_overlay);

    // Draw pause title
    _window->draw(_pauseText);

    // Draw menu options with highlighting
    sf::Text* options[3] = {&_resumeText, &_restartText, &_quitText};
    sf::Color highlightColor = sf::Color::Cyan; // Use neonMain from TitleScreen
    
    for (int i = 0; i < 3; i++)
    {
        if (i == _selectedOption)
        {
            options[i]->setFillColor(sf::Color(255,200,0));
            options[i]->setCharacterSize(60);
        }
        else
        {
            options[i]->setFillColor(sf::Color::White);
            options[i]->setCharacterSize(50);
        }
        centerOrigin(*options[i]);
        _window->draw(*options[i]);
    }
}

void PauseScreen::moveSelectionUp()
{
    _selectedOption = (_selectedOption - 1 + _numOptions) % _numOptions;
}

void PauseScreen::moveSelectionDown()
{
    _selectedOption = (_selectedOption + 1) % _numOptions;
}

void PauseScreen::select(MainManager* mainManager, GameManager* gameManager)
{
    switch (_selectedOption)
    {
        case 0: // Resume
            mainManager->setCurrentState(GameState::Playing);
            break;
        case 1: // Restart
            // Reset game (need to add a reset method to GameManager)
            // gameManager->reset();
            mainManager->setCurrentState(GameState::Playing);
            break;
        case 2: // Quit to Menu
            mainManager->setCurrentState(GameState::Menu);
            break;
    }

    // Reset selection to Resume for next time
    _selectedOption = 0;
}

void PauseScreen::resetSelection()
{
    _selectedOption = 0;
}