#ifndef Application_hpp
#define Application_hpp

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include "Player.hpp"

#include "Level.hpp"


class Application{
    
public:
    Application();
    void run();
    
private:
    sf::Vector2f pt(sf::Vector2i position){return sf::Vector2f(position.x*32+16.f,position.y*32+16.f);}
    
    sf::RenderWindow window;
    Level niveau;
    float tempsDeplacement;
    float zoom;
    sf::Vector2i position;
    sf::Vector2i oldPosition;
    sf::Font police;
    
    Player player;
    
    
    void drawInventory();
};

#endif /* Application_hpp */
