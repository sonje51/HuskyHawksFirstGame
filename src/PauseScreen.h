#ifndef PAUSE_SCREEN_H
#define PAUSE_SCREEN_H

#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "GameColors.h"

// // Forward declaration
class MainManager;
class GameManager;

class PauseScreen
{
private:
    sf::RenderWindow* _window;
    sf::Font _font;
    sf::Text _pauseText;
    sf::Text _resumeText;
    sf::Text _restartText;
    sf::Text _quitText;
    sf::RectangleShape _overlay;
    
    int _selectedOption;
    const int _numOptions = 3; // Resume, Restart, Quit
    
    void centerOrigin(sf::Text& text);
    
public:
    PauseScreen(sf::RenderWindow* window, unsigned int WIDTH, unsigned int HEIGHT);
    void draw();
    void moveSelectionUp();
    void moveSelectionDown();
    void select(MainManager* mainManager, GameManager* gameManager);
    void resetSelection();
};

#endif