#ifndef GAME_COLORS_H
#define GAME_COLORS_H

#include <SFML/Graphics/Color.hpp>

namespace GameColors {
    const sf::Color bgTop(10, 6, 25);
    const sf::Color bgBottom(6, 20, 40);
    // Text fills
    const sf::Color textFill(230, 230, 255);       // Soft white text
    const sf::Color subtitleFill(200, 200, 220);   // Light gray text
    const sf::Color promptFill(220, 220, 255);     // Medium gray text
    // Neon colors
    const sf::Color neonMain(0, 255, 200);         // Neon blue/turquoise
    const sf::Color neonAccent(255, 0, 200);       // Neon pink/magenta
    const sf::Color neonSelect(255, 200, 0);       // Neon orange
    const sf::Color neonPad(100, 255, 0);         // Neon green
    // Blocks colors
    const sf::Color blockWhite(255, 255, 255);     // Bright white
    const sf::Color blockRed(255, 0, 0);           // Bright red
    const sf::Color blockGreen(0, 255, 0);         // Bright green
    const sf::Color blockBlue(0, 0, 255);          // Bright blue
    const sf::Color blockYellow(255, 255, 0);      // Bright yellow

    const sf::Color blockWhiteDim(200, 200, 200);  // Medium white
    const sf::Color blockRedDim(200, 0, 0);        // Medium red
    const sf::Color blockGreenDim(0, 200, 0);      // Medium green
    const sf::Color blockBlueDim(0, 0, 200);       // Medium blue
    const sf::Color blockYellowDim(200, 200, 0);   // Medium yellow



}

#endif