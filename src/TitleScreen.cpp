#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cmath>
#include "TitleScreen.h"
#include "MainManager.h"

// Default constructor
TitleScreen::TitleScreen(sf::RenderWindow *_window, unsigned int WIDTH, unsigned int HEIGHT)
    : window(_window),
      topRect(sf::Vector2f((float)WIDTH, (float)HEIGHT / 2.f)),
      bottomRect(sf::Vector2f((float)WIDTH, (float)HEIGHT / 2.f)),
      leftNeon(sf::Vector2f(6.f, (float)HEIGHT * 0.6f)),
      neonBar(sf::Vector2f(WIDTH * 0.6f, 6.f)),
      rightNeon(leftNeon),
      titleText(font),
      subtitleText(font),
      promptText(font),
      playText(font),
      controlsText(font),
      creditsText(font),
      quitText(font),
      titlePlaceholder(sf::Vector2f(900.f, 160.f)),
      alpha(0.f),
      alphaSpeed(1.5f), // Increase for faster fade
      numMenuOptions(4),
      selectedOption(0)
{
    // Background gradient using two rectangles
    topRect.setPosition({0.f, 0.f});
    topRect.setFillColor(GameColors::bgTop);

    bottomRect.setPosition({0.f, (float)HEIGHT / 2.f});
    bottomRect.setFillColor(GameColors::bgBottom);

    // Decorative neon lines
    leftNeon.setPosition({80.f, (float)HEIGHT * 0.2f});
    leftNeon.setFillColor(GameColors::neonAccent);
    leftNeon.setOutlineThickness(2.f);
    leftNeon.setOutlineColor(sf::Color(255, 255, 255, 30));

    rightNeon.setPosition({(float)WIDTH - 86.f, (float)HEIGHT * 0.2f});
    rightNeon.setFillColor(GameColors::neonAccent);

    neonBar.setOrigin({neonBar.getSize().x / 2.f, neonBar.getSize().y / 2.f});
    neonBar.setPosition({WIDTH * 0.5f, HEIGHT * 0.58f});

    // Try to load a font from assets; if missing, we'll use a placeholder title shape
    bool fontLoaded = false;
    if (!font.openFromFile("../../../assets/fonts/RetroRegular.ttf"))
    {
        std::cerr << "Failed to load assets/fonts/RetroRegular.ttf\n";
        assert(false);
    }

    // titleText.setFont(font);
    titleText.setString("BREAKOUT");
    titleText.setCharacterSize(160);
    titleText.setFillColor(GameColors::textFill);
    titleText.setStyle(sf::Text::Bold);

    // Neon glow effect by outline and duplicated draws (we'll draw glow manually)
    titleText.setOutlineThickness(0.f);

    // subtitleText.setFont(font);
    subtitleText.setString("A HuskyHawks take on Breakout");
    subtitleText.setCharacterSize(36);
    subtitleText.setFillColor(GameColors::subtitleFill);

    // promptText.setFont(font);
    promptText.setString("Press any key to start");
    promptText.setCharacterSize(50);
    promptText.setFillColor(GameColors::promptFill);

    // Menu Options
    // playText
    playText.setString("Play");
    playText.setCharacterSize(50);
    playText.setFillColor(GameColors::textFill);
    // controlsText
    controlsText.setString("Controls");
    controlsText.setCharacterSize(50);
    controlsText.setFillColor(GameColors::textFill);
    // creditsText
    creditsText.setString("Credits");
    creditsText.setCharacterSize(50);
    creditsText.setFillColor(GameColors::textFill);
    // quitText
    quitText.setString("Quit");
    quitText.setCharacterSize(50);
    quitText.setFillColor(GameColors::textFill);

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

    centerOrigin(playText);
    playText.setPosition({WIDTH * 0.5f, HEIGHT * 0.65f});

    centerOrigin(controlsText);
    controlsText.setPosition({WIDTH * 0.5f, HEIGHT * 0.70f});

    centerOrigin(creditsText);
    creditsText.setPosition({WIDTH * 0.5f, HEIGHT * 0.75f});

    centerOrigin(quitText);
    quitText.setPosition({WIDTH * 0.5f, HEIGHT * 0.80f});

    // Placeholder title rectangle
    titlePlaceholder.setFillColor(sf::Color::Transparent);
    titlePlaceholder.setOutlineThickness(6.f);
    titlePlaceholder.setOutlineColor(GameColors::neonMain);
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

    topRect.setFillColor(applyAlpha(GameColors::bgTop));
    bottomRect.setFillColor(applyAlpha(GameColors::bgBottom));
    leftNeon.setFillColor(applyAlpha(GameColors::neonAccent));
    rightNeon.setFillColor(applyAlpha(GameColors::neonAccent));
    neonBar.setFillColor(applyAlpha(GameColors::neonMain));
    titlePlaceholder.setOutlineColor(applyAlpha(GameColors::neonMain));
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
        sf::Color glowColor = GameColors::neonMain;
        glowColor.a = static_cast<uint8_t>(std::max(0.f, alpha - i * 20.f));
        glow.setFillColor(glowColor);
        window->draw(glow);
    }
    // Final crisp title
    titleText.setFillColor(applyAlpha(GameColors::textFill));
    window->draw(titleText);

    // Subtitle and prompt
    subtitleText.setFillColor(applyAlpha(subtitleText.getFillColor()));
    window->draw(subtitleText);

    // promptText.setFillColor(applyAlpha(promptText.getFillColor()));
    // window->draw(promptText);

    // TODO: merge both centerOrigins into one private method
    auto centerOrigin = [](sf::Text &t)
    {
        sf::FloatRect b = t.getLocalBounds();
        sf::Vector2f origin(
            static_cast<float>(std::floor(b.position.x + b.size.x / 2.f)),
            static_cast<float>(std::floor(b.position.y + b.size.y / 2.f)));
        t.setOrigin(origin);
    };

    // Menu options
    if (selectedOption == 0)
    {
        playText.setFillColor(GameColors::neonSelect);
        playText.setCharacterSize(75);
    }
    else
    {
        playText.setFillColor(GameColors::textFill);
        playText.setCharacterSize(50);
    }
    centerOrigin(playText);
    playText.setFillColor(applyAlpha(playText.getFillColor()));
    window->draw(playText);

    if (selectedOption == 1)
    {
        controlsText.setFillColor(GameColors::neonSelect);
        controlsText.setCharacterSize(75);
    }
    else
    {
        controlsText.setFillColor(GameColors::textFill);
        controlsText.setCharacterSize(50);
    }
    centerOrigin(controlsText);
    controlsText.setFillColor(applyAlpha(controlsText.getFillColor()));
    window->draw(controlsText);

    if (selectedOption == 2)
    {
        creditsText.setFillColor(GameColors::neonSelect);
        creditsText.setCharacterSize(75);
    }
    else
    {
        creditsText.setFillColor(GameColors::textFill);
        creditsText.setCharacterSize(50);
    }
    centerOrigin(creditsText);
    creditsText.setFillColor(applyAlpha(creditsText.getFillColor()));
    window->draw(creditsText);

    if (selectedOption == 3)
    {
        quitText.setFillColor(GameColors::neonSelect);
        quitText.setCharacterSize(75);
    }
    else
    {
        quitText.setFillColor(GameColors::textFill);
        quitText.setCharacterSize(50);
    }
    centerOrigin(quitText);
    quitText.setFillColor(applyAlpha(quitText.getFillColor()));
    window->draw(quitText);
}

void TitleScreen::moveSelectionUp()
{
    selectedOption = (selectedOption - 1 + numMenuOptions) % numMenuOptions;
}

void TitleScreen::moveSelectionDown()
{
    selectedOption = (selectedOption + 1) % numMenuOptions;
}

// Select the currently highlighted option
void TitleScreen::select(MainManager *mainManager)
{
    // Handle menu selection
    switch (selectedOption)
    {
    case 0:
        mainManager->setCurrentState(GameState::Playing);
        break;
    case 1:
        mainManager->setCurrentState(GameState::Controls);
        break;
    case 2:
        mainManager->setCurrentState(GameState::Credits);
        break;
    case 3:
        mainManager->window()->close();
        break;
    }
}