#ifndef TEXTURE_H
#define TEXTURE_H
#include <SFML/Graphics.hpp>
#include<vector>

class Texture_{
public:
    sf::Texture boardTexture;
    sf::Texture arrowTexture;
    sf::Texture targetTexture;
    sf::Texture visualizeTexture; 
    sf::Texture reloadTexture;
    sf::Texture clearTexture;
    sf::Texture choiceTexture;
    sf::Texture checkTexture;
    sf::Texture legendTexture;

    sf::Sprite visualizeSprite; 
    sf::Sprite reloadSprite;
    sf::Sprite clearSprite;
    sf::Sprite choiceSprite;
    sf::Sprite checkSprite;
    sf::Sprite legendSprite;
    sf::Sprite boardSprite;
    sf::Sprite arrowSprite;
    sf::Sprite targetSprite;

    sf::Font font;
    sf::Text clearText;

    Texture_(sf::Vector2f &s_coord, sf::Vector2f &e_coord, sf::Vector2f &windowSize);
    void drawStaticTextures(sf::RenderWindow *window);
};

#endif