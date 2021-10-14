#include "Textures.hpp"
#include <iostream>

Texture_::Texture_(sf::Vector2f &s_coord, sf::Vector2f &e_coord, sf::Vector2f &windowSize){
    boardTexture.loadFromFile("Assets/tiles.png");
    boardTexture.setSmooth(true);
    boardSprite.setTexture(boardTexture);
    boardSprite.setScale(sf::Vector2f(sf::VideoMode::getDesktopMode().height/1080.0f, sf::VideoMode::getDesktopMode().height/1080.0f));

    arrowTexture.loadFromFile("Assets/start.png");
    arrowTexture.setSmooth(true);
    arrowSprite.setTexture(arrowTexture);
    arrowSprite.setScale(sf::Vector2f((0.32f/768.0f) * sf::VideoMode::getDesktopMode().height,(0.32f/768.0f) * sf::VideoMode::getDesktopMode().height));
    arrowSprite.setPosition(sf::Vector2f((s_coord.x) + ((3.5f/768.0f) * sf::VideoMode::getDesktopMode().height), (s_coord.y) + ((3.5f/768.0f) * sf::VideoMode::getDesktopMode().height)));

    targetTexture.loadFromFile("Assets/target.png");
    targetTexture.setSmooth(true);
    targetSprite.setTexture(targetTexture);
    targetSprite.setScale(sf::Vector2f((0.075f/768.0f) * sf::VideoMode::getDesktopMode().height,(0.075f/768.0f) * sf::VideoMode::getDesktopMode().height));
    targetSprite.setPosition(sf::Vector2f((e_coord.x) + ((3.0f/768.0f) * sf::VideoMode::getDesktopMode().height), (e_coord.y) + ((2.9f/768.0f) * sf::VideoMode::getDesktopMode().height)));

    visualizeTexture.loadFromFile("Assets/visualize.png");
    visualizeTexture.setSmooth(true);
    visualizeSprite.setTexture(visualizeTexture);
    visualizeSprite.setScale(sf::Vector2f((0.35f/768.0f) * sf::VideoMode::getDesktopMode().height, (0.35f/768.0f) * sf::VideoMode::getDesktopMode().height));
    visualizeSprite.setOrigin(sf::Vector2f((visualizeSprite.getPosition().x + visualizeSprite.getTexture()->getSize().x)/2.0f, (visualizeSprite.getPosition().y + visualizeSprite.getTexture()->getSize().y)/2.0f));
    visualizeSprite.setPosition(sf::Vector2f((windowSize.x/2.0f) + ((10.0f/768.0f) * sf::VideoMode::getDesktopMode().height), visualizeSprite.getPosition().y + ((58.0f/768.0f) * sf::VideoMode::getDesktopMode().height)));
    
    reloadTexture.loadFromFile("Assets/reload.png");
    reloadTexture.setSmooth(true);
    reloadSprite.setTexture(reloadTexture);
    reloadSprite.setScale(sf::Vector2f((0.17f/768.0f) * sf::VideoMode::getDesktopMode().height, (0.17f/768.0f) * sf::VideoMode::getDesktopMode().height));
    reloadSprite.setPosition(sf::Vector2f((820.0f/768.0f) * sf::VideoMode::getDesktopMode().height, reloadSprite.getPosition().y + ((31.0f/768.0f) * sf::VideoMode::getDesktopMode().height)));
    
    font.loadFromFile("Font/OpenSans-Light.ttf");
    clearText.setFont(font);
    clearText.setFillColor(sf::Color::Black);
    clearText.setString("Clear Board");
    clearText.setCharacterSize(23);
    clearText.setScale(sf::Vector2f(sf::VideoMode::getDesktopMode().height/768.0f, sf::VideoMode::getDesktopMode().height/768.0f));
    clearText.setPosition(sf::Vector2f((435.0f/768.0f) * sf::VideoMode::getDesktopMode().height, (45.0f/768.0f) * sf::VideoMode::getDesktopMode().height));

    choiceTexture.loadFromFile("Assets/algos.png");
    choiceTexture.setSmooth(true);
    choiceSprite.setTexture(choiceTexture);
    choiceSprite.setScale(sf::Vector2f((0.72f/768.0f) * sf::VideoMode::getDesktopMode().height, (0.72f/768.0f) * sf::VideoMode::getDesktopMode().height));
    choiceSprite.setPosition(sf::Vector2f((75.0f/768.0f) * sf::VideoMode::getDesktopMode().height, (90.0f/768.0f) * sf::VideoMode::getDesktopMode().height));

    checkTexture.loadFromFile("Assets/check.png");
    checkTexture.setSmooth(true);
    checkSprite.setTexture(checkTexture);
    checkSprite.setScale(sf::Vector2f((0.54f/768.0f) * sf::VideoMode::getDesktopMode().height, (0.54f/768.0f) * sf::VideoMode::getDesktopMode().height));

    legendTexture.loadFromFile("Assets/legend.png");
    legendTexture.setSmooth(true);
    legendSprite.setTexture(legendTexture);
    legendSprite.setScale(sf::Vector2f((0.7f/768.0f) * sf::VideoMode::getDesktopMode().height,(0.7f/768.0f) * sf::VideoMode::getDesktopMode().height));
    legendSprite.setPosition(sf::Vector2f((980.0f/768.0f) * sf::VideoMode::getDesktopMode().height,(90.0f/768.0f) * sf::VideoMode::getDesktopMode().height));

}

void Texture_::drawStaticTextures(sf::RenderWindow *window){
    window->draw(boardSprite);
    window->draw(legendSprite);
    window->draw(visualizeSprite);
    window->draw(choiceSprite);
    window->draw(checkSprite);
    window->draw(targetSprite);
    window->draw(arrowSprite);
    
}