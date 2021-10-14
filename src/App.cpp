#include "App.hpp"

App::App() : app_event(sf::Vector2f(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height)) {
    window = new sf::RenderWindow(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Pathfinding Visualizer", sf::Style::Close | sf::Style::Fullscreen);
    window->setFramerateLimit(120);
    app_event.dt = 0.0f;
    app_event.totalTime = 0.0f;
}

void App::updateEvents(){
    app_event.clickEvents(window);
    while (window->pollEvent(evnt)){
        switch(evnt.type){
            case sf::Event::Closed:
                window->close();
            break;
            case sf::Event::TextEntered:
                if (evnt.text.unicode == 27)
                    window->close();
            default:break;
        }
    }
}

void App::update(){
    app_event.dt = app_event.dtClock.restart().asSeconds();
    updateEvents();
}

void App::render(){
    window->clear(sf::Color::White);
    app_event.drawColoredTiles(window);
    app_event.texture_.drawStaticTextures(window);
    window->display();
}

void App::run(){
    while (window->isOpen()){
        update();
        render();
    }
}

App::~App(){
    delete window;
}
