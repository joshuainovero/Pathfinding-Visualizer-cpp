#ifndef APP_H
#define APP_H
#include <SFML/Graphics.hpp>
#include "Events.hpp"

class App {
private:
    sf::RenderWindow *window;
    sf::Event evnt;
    sf::Mouse mousePos;
    Events_ app_event;
    
    void updateEvents();
    void update();
    void render();

public:
    App();
    ~App();
    void run();
};
#endif // APP_H