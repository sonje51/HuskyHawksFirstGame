//TitleScreen.h

#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include <SFML/Graphics.hpp>
class MainManager; // Forward declaration to avoid circular inclusion
#include "GameState.h"

/*
// TitleScreen Class
// Handles the game's title screen menu, including visual design and user selection.
// Responsible for drawing the menu, highlighting options, and navigating selections.
*/
class TitleScreen
{

/*
// Constructor
// _window: pointer to the SFML window
// WIDTH, HEIGHT: dimensions of the window
*/
public:
    TitleScreen(sf::RenderWindow *_window, unsigned int WIDTH, unsigned int HEIGHT);
    void drawTitleScreen();
    void moveSelectionUp();
    void moveSelectionDown();
    int getSelectedOption();
    void select(MainManager *mainManager);

/*
//Window Pointer
*/
private:
    sf::RenderWindow *window;

    // Colors for neon retro
    const sf::Color bgTop;      // deep purple
    const sf::Color bgBottom;   // dark blue
    const sf::Color neonMain;   // cyan-green neon
    const sf::Color neonAccent; // magenta accent
    const sf::Color neonSelect; // neon orange
    const sf::Color textFill;

    // SFML Shapes for UI elements
    sf::RectangleShape topRect;
    sf::RectangleShape bottomRect;
    sf::RectangleShape leftNeon;
    sf::RectangleShape rightNeon;
    sf::RectangleShape neonBar;

    // Text elements
    sf::Font font;
    sf::Text titleText;
    sf::Text subtitleText;
    sf::Text promptText;
    sf::Text playText;
    sf::Text controlsText;
    sf::Text creditsText;
    sf::Text quitText;
    sf::RectangleShape titlePlaceholder;

    // Menu selection
    float alpha;
    const float alphaSpeed;
    const int numMenuOptions;
    int selectedOption;
};

#endif