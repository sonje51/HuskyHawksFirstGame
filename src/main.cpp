#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cmath>

enum class GameState {
    Menu,
    Playing,
    Controls,
    Credits,
    Paused
};

int main() {
    const unsigned int WIDTH  = 1920;
    const unsigned int HEIGHT = 1080;
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Breakout by HuskyHawks");
    window.setFramerateLimit(60);

    // Colors for neon retro
    const sf::Color bgTop(10, 6, 25);        // deep purple
    const sf::Color bgBottom(6, 20, 40);     // dark blue
    const sf::Color neonMain(0, 255, 200);   // cyan/neon blue
    const sf::Color neonAccent(255, 0, 200); // magenta accent
    const sf::Color neonSelect(255, 200, 0); // neon orange
    const sf::Color textFill(230, 230, 255);

    // Background gradient using two rectangles
    sf::RectangleShape topRect(sf::Vector2f((float)WIDTH, (float)HEIGHT / 2.f));
    topRect.setPosition({0.f, 0.f});
    topRect.setFillColor(bgTop);

    sf::RectangleShape bottomRect(sf::Vector2f((float)WIDTH, (float)HEIGHT / 2.f));
    bottomRect.setPosition({0.f, (float)HEIGHT / 2.f});
    bottomRect.setFillColor(bgBottom);

    // Decorative neon lines
    sf::RectangleShape leftNeon(sf::Vector2f(6.f, (float)HEIGHT * 0.6f));
    leftNeon.setPosition({80.f, (float)HEIGHT * 0.2f});
    leftNeon.setFillColor(neonAccent);
    leftNeon.setOutlineThickness(2.f);
    leftNeon.setOutlineColor(sf::Color(255, 255, 255, 30));

    sf::RectangleShape rightNeon = leftNeon;
    rightNeon.setPosition({(float)WIDTH - 86.f, (float)HEIGHT * 0.2f});
    rightNeon.setFillColor(neonAccent);

    // Try to load a font from assets; if missing, we'll use a placeholder title shape
    sf::Font font;
    bool fontLoaded = false;
    if (!font.openFromFile("../../../assets/fonts/RetroRegular.ttf")) {
        std::cerr << "Failed to load assets/fonts/RetroRegular.ttf\n";
        return EXIT_FAILURE;
    }

    // Title, subtitle, and options
    sf::Text titleText(font);
    sf::Text subtitleText(font);
    sf::Text promptText(font);
    sf::Text playText(font);
    sf::Text controlsText(font);
    sf::Text creditsText(font);
    sf::Text quitText(font);


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

    // Menu Options
    // playText
    playText.setString("Play");
    playText.setCharacterSize(50);
    playText.setFillColor(textFill);
    // controlsText
    controlsText.setString("Controls");
    controlsText.setCharacterSize(50);
    controlsText.setFillColor(textFill);
    // creditsText
    creditsText.setString("Credits");
    creditsText.setCharacterSize(50);
    creditsText.setFillColor(textFill);
    // quitText
    quitText.setString("Quit");
    quitText.setCharacterSize(50);
    quitText.setFillColor(textFill);


    // Positioning helper (center)
    auto centerOrigin = [](sf::Text& t) {
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
    sf::RectangleShape titlePlaceholder(sf::Vector2f(900.f, 160.f));
    titlePlaceholder.setFillColor(sf::Color::Transparent);
    titlePlaceholder.setOutlineThickness(6.f);
    titlePlaceholder.setOutlineColor(neonMain);
    titlePlaceholder.setPosition({WIDTH * 0.5f - titlePlaceholder.getSize().x / 2.f, HEIGHT * 0.22f});


    // Loop variables
    // Fade-in control
    float alpha = 0.f;
    const float alphaSpeed = 1.5f; // increase for faster fade

    // Menu variables
    GameState currentState = GameState::Menu;
    const int numMenuOptions = 4;
    int selectedOption = 0;    // 0=Play, 1=Controls, 2=Credits, 3=Quit



    // Main loop
    while (window.isOpen()) {
        // Event handling
        while (const std::optional event = window.pollEvent()) {
            // Window close event
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            switch (currentState) {
                case GameState::Menu:
                {
                    if (event->is<sf::Event::KeyPressed>()) {
                        auto keyEvent = event->getIf<sf::Event::KeyPressed>();

                        if (keyEvent->scancode == sf::Keyboard::Scancode::Up) {
                            selectedOption = (selectedOption - 1 + numMenuOptions) % numMenuOptions;
                        } else if (keyEvent->scancode == sf::Keyboard::Scancode::Down) {
                            selectedOption = (selectedOption + 1) % numMenuOptions;
                        } else if (keyEvent->scancode == sf::Keyboard::Scancode::Enter) {
                            // Handle menu selection
                            switch (selectedOption) {
                                case 0:
                                    currentState = GameState::Playing;
                                    break;
                                case 1:
                                    currentState = GameState::Controls;
                                    break;
                                case 2:
                                    currentState = GameState::Credits;
                                    break;
                                case 3:
                                    window.close();
                                    break;
                            }
                        }
                    }
                    break;
                }
                
                case GameState::Playing:
                    // Game input here
                    break;
                    
                case GameState::Paused:
                    // Paused input here
                    break;
                    
                case GameState::Controls:
                    // Controls input here
                    break;
                    
                case GameState::Credits:
                    // Credits input here
                    break;
            }
        }

        // Update fade-in alpha
        if (alpha < 255.f) alpha = std::min(255.f, alpha + alphaSpeed);

        // Apply alpha to elements
        auto applyAlpha = [&](sf::Color c) {
            c.a = static_cast<uint8_t>(alpha);
            return c;
        };

        topRect.setFillColor(applyAlpha(bgTop));
        bottomRect.setFillColor(applyAlpha(bgBottom));
        leftNeon.setFillColor(applyAlpha(neonAccent));
        rightNeon.setFillColor(applyAlpha(neonAccent));
        titlePlaceholder.setOutlineColor(applyAlpha(neonMain));
        promptText.setFillColor(applyAlpha(promptText.getFillColor()));

        // Render
        window.clear();
        window.draw(topRect);
        window.draw(bottomRect);

        // Decorative neon lines
        window.draw(leftNeon);
        window.draw(rightNeon);

        // Center decorative horizontal neon bar
        sf::RectangleShape neonBar(sf::Vector2f(WIDTH * 0.6f, 6.f));
        neonBar.setOrigin({neonBar.getSize().x / 2.f, neonBar.getSize().y / 2.f});
        neonBar.setPosition({WIDTH * 0.5f, HEIGHT * 0.58f});
        neonBar.setFillColor(applyAlpha(neonMain));
        window.draw(neonBar);

        // Neon glow effect: draw several layers of the title with increasing blur-like offsets
        sf::Text glow = titleText;
        for (int i = 6; i >= 1; --i) {
            float scale = 1.f + i * 0.0025f;
            glow.setScale({scale, scale});
            sf::Color glowColor = neonMain;
            glowColor.a = static_cast<uint8_t>(std::max(0.f, alpha - i * 20.f));
            glow.setFillColor(glowColor);
            window.draw(glow);
        }
        // Final crisp title
        titleText.setFillColor(applyAlpha(textFill));
        window.draw(titleText);

        // Subtitle and prompt
        subtitleText.setFillColor(applyAlpha(subtitleText.getFillColor()));
        window.draw(subtitleText);

        //promptText.setFillColor(applyAlpha(promptText.getFillColor()));
        //window.draw(promptText);

        // Menu options
        if (selectedOption==0) {
            playText.setFillColor(neonSelect);
            playText.setCharacterSize(75);
        } else {
            playText.setFillColor(textFill);
            playText.setCharacterSize(50);
        }
        centerOrigin(playText);
        playText.setFillColor(applyAlpha(playText.getFillColor()));
        window.draw(playText);

        if (selectedOption==1) {
            controlsText.setFillColor(neonSelect);
            controlsText.setCharacterSize(75);
        } else {
            controlsText.setFillColor(textFill);
            controlsText.setCharacterSize(50);
        }
        centerOrigin(controlsText);
        controlsText.setFillColor(applyAlpha(controlsText.getFillColor()));
        window.draw(controlsText);
        
        if (selectedOption==2) {
            creditsText.setFillColor(neonSelect);
            creditsText.setCharacterSize(75);
        } else {
            creditsText.setFillColor(textFill);
            creditsText.setCharacterSize(50);
        }
        centerOrigin(creditsText);
        creditsText.setFillColor(applyAlpha(creditsText.getFillColor()));
        window.draw(creditsText);

        if (selectedOption==3) {
            quitText.setFillColor(neonSelect);
            quitText.setCharacterSize(75);
        } else {
            quitText.setFillColor(textFill);
            quitText.setCharacterSize(50);
        }
        centerOrigin(quitText);
        quitText.setFillColor(applyAlpha(quitText.getFillColor()));
        window.draw(quitText);

        
        window.display();
    }
}