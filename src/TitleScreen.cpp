#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cmath>
#include "TitleScreen.h"

// Default constructor
TitleScreen::TitleScreen(sf::RenderWindow *_window, unsigned int WIDTH, unsigned int HEIGHT)
    : window(_window),
      bgTop(10, 6, 25),
      bgBottom(6, 20, 40),
      neonMain(0, 255, 200),
      neonAccent(255, 0, 200),
      textFill(230, 230, 255),
      topRect(sf::Vector2f((float)WIDTH, (float)HEIGHT / 2.f)),
      bottomRect(sf::Vector2f((float)WIDTH, (float)HEIGHT / 2.f)),
      leftNeon(sf::Vector2f(6.f, (float)HEIGHT * 0.6f)),
      neonBar(sf::Vector2f(WIDTH * 0.6f, 6.f)),
      rightNeon(leftNeon),
      titleText(font),
      subtitleText(font),
      promptText(font),
      titlePlaceholder(sf::Vector2f(900.f, 160.f)),
      alpha(0.f),
      alphaSpeed(1.5f) // Increase for faster fade
{
    // Background gradient using two rectangles
    topRect.setPosition({0.f, 0.f});
    topRect.setFillColor(bgTop);

    bottomRect.setPosition({0.f, (float)HEIGHT / 2.f});
    bottomRect.setFillColor(bgBottom);

    // Decorative neon lines
    leftNeon.setPosition({80.f, (float)HEIGHT * 0.2f});
    leftNeon.setFillColor(neonAccent);
    leftNeon.setOutlineThickness(2.f);
    leftNeon.setOutlineColor(sf::Color(255, 255, 255, 30));

    rightNeon.setPosition({(float)WIDTH - 86.f, (float)HEIGHT * 0.2f});
    rightNeon.setFillColor(neonMain);

    neonBar.setOrigin({neonBar.getSize().x / 2.f, neonBar.getSize().y / 2.f});
    neonBar.setPosition({WIDTH * 0.5f, HEIGHT * 0.58f});

    // Try to load a font from assets; if missing, we'll use a placeholder title shape
    bool fontLoaded = false;
    if (!font.openFromFile("assets/fonts/RetroRegular.ttf"))
    {
        std::cerr << "Failed to load assets/fonts/RetroRegular.ttf\n";
        assert(false);
    }

    // titleText.setFont(font);
    titleText.setString("BREAKOUT");
    titleText.setCharacterSize(160);
    titleText.setFillColor(textFill);
    titleText.setStyle(sf::Text::Bold);

    // Neon glow effect by outline and duplicated draws (we'll draw glow manually)
    titleText.setOutlineThickness(0.f);

    // subtitleText.setFont(font);
    subtitleText.setString("A HuskyHawks take on Breakout");
    subtitleText.setCharacterSize(36);
    subtitleText.setFillColor(sf::Color(200, 200, 220));

    // promptText.setFont(font);
    promptText.setString("Press any key to start");
    promptText.setCharacterSize(50);
    promptText.setFillColor(sf::Color(220, 220, 255));

    // Positioning helper (center)
    auto centerOrigin = [](sf::Text &t)
    {
        sf::FloatRect b = t.getLocalBounds();
        sf::Vector2f origin(
            static_cast<float>(std::floor(b.position.x + b.size.x / 2.f)),
            static_cast<float>(std::floor(b.position.y + b.size.y / 2.f)));
        t.setOrigin(origin);
    };

    centerOrigin(titleText);
    titleText.setPosition({WIDTH * 0.5f, HEIGHT * 0.28f});

    centerOrigin(subtitleText);
    subtitleText.setPosition({WIDTH * 0.5f, HEIGHT * 0.4f});

    centerOrigin(promptText);
    promptText.setPosition({WIDTH * 0.5f, HEIGHT * 0.82f});

    // Placeholder title rectangle
    titlePlaceholder.setFillColor(sf::Color::Transparent);
    titlePlaceholder.setOutlineThickness(6.f);
    titlePlaceholder.setOutlineColor(neonMain);
    titlePlaceholder.setPosition({WIDTH * 0.5f - titlePlaceholder.getSize().x / 2.f, HEIGHT * 0.22f});
}

// Draw the title screen on the window
void TitleScreen::drawTitleScreen()
{
    // Update fade-in alpha
    if (alpha < 255.f)
        alpha = std::min(255.f, alpha + alphaSpeed);

    // Apply alpha to elements
    auto applyAlpha = [&](sf::Color c)
    {
        c.a = static_cast<uint8_t>(alpha);
        return c;
    };

    topRect.setFillColor(applyAlpha(bgTop));
    bottomRect.setFillColor(applyAlpha(bgBottom));
    leftNeon.setFillColor(applyAlpha(neonAccent));
    rightNeon.setFillColor(applyAlpha(neonMain));
    neonBar.setFillColor(applyAlpha(neonMain));
    titlePlaceholder.setOutlineColor(applyAlpha(neonMain));
    promptText.setFillColor(applyAlpha(promptText.getFillColor()));

    // Render
    window->draw(topRect);
    window->draw(bottomRect);

    // Decorative neon lines
    window->draw(leftNeon);
    window->draw(rightNeon);

    // Center decorative horizontal neon bar
    window->draw(neonBar);

    // Neon glow effect: draw several layers of the title with increasing blur-like offsets
    sf::Text glow = titleText;
    for (int i = 6; i >= 1; --i)
    {
        float scale = 1.f + i * 0.0025f;
        glow.setScale({scale, scale});
        sf::Color glowColor = neonMain;
        glowColor.a = static_cast<uint8_t>(std::max(0.f, alpha - i * 20.f));
        glow.setFillColor(glowColor);
        window->draw(glow);
    }
    // Final crisp title
    titleText.setFillColor(applyAlpha(textFill));
    window->draw(titleText);

    // Subtitle and prompt
    subtitleText.setFillColor(applyAlpha(subtitleText.getFillColor()));
    window->draw(subtitleText);

    promptText.setFillColor(applyAlpha(promptText.getFillColor()));
    window->draw(promptText);
}