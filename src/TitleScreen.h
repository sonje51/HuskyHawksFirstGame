#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include <SFML/Graphics.hpp>

class TitleScreen
{
public:
    TitleScreen(sf::RenderWindow *_window, unsigned int WIDTH, unsigned int HEIGHT);
    void drawTitleScreen();

private:
    sf::RenderWindow *window;

    // Colors for neon retro
    const sf::Color bgTop;      // deep purple
    const sf::Color bgBottom;   // dark blue
    const sf::Color neonMain;   // cyan-green neon
    const sf::Color neonAccent; // magenta accent
    const sf::Color textFill;

    sf::RectangleShape topRect;
    sf::RectangleShape bottomRect;
    sf::RectangleShape leftNeon;
    sf::RectangleShape rightNeon;
    sf::RectangleShape neonBar;

    sf::Font font;
    sf::Text titleText;
    sf::Text subtitleText;
    sf::Text promptText;
    sf::RectangleShape titlePlaceholder;

    float alpha;
    const float alphaSpeed;
};

#endif