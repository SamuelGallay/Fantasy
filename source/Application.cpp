#include "Application.hpp"

Application::Application() : window(sf::VideoMode(1024, 512), "Le Monde"), niveau("level.txt")
{
    window.setVerticalSyncEnabled(true);
    
    position = sf::Vector2i(8, 4);
    oldPosition = sf::Vector2i(8, 4);
    
    tempsDeplacement = 0.2f;
    zoom = 2.f;
    
    police.loadFromFile(resourcePath() + "FiraSans-Light.otf");
}

void Application::run(){
    sf::Vector2i direction(0,0);
    sf::Clock clockDeplacement;
    
    while (window.isOpen())
    {
        //On s'occupe des events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
        }
        
        //On s'occupe de la direction
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
            direction = sf::Vector2i(0,-1);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            direction = sf::Vector2i(-1,0);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            direction = sf::Vector2i(0,1);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            direction = sf::Vector2i(1,0);
        else
            direction = sf::Vector2i(0,0);
        
        //On change nos coordonnees si possible
        if(clockDeplacement.getElapsedTime().asSeconds()>tempsDeplacement && direction != sf::Vector2i(0,0) && niveau(position+direction))
        {
            oldPosition = position;
            position+=direction;
            clockDeplacement.restart();
            player.changeDirection(direction, tempsDeplacement);
        }
        
        //On deplace joueur
        if(clockDeplacement.getElapsedTime().asSeconds()<=tempsDeplacement)
        {
            float dt = clockDeplacement.getElapsedTime().asSeconds()/tempsDeplacement;
            player.setPosition( pt(position)*dt+pt(oldPosition)*(1-dt) );
        }
        else
            player.setPosition(pt(position));
        
        
        
        //On deplace la camera sur le joueur
        window.setView(sf::View(sf::Vector2f(player.getPosition().x,
                                             player.getPosition().y),
                                sf::Vector2f((int)((float)window.getSize().x/zoom),
                                             (int)((float)window.getSize().y/zoom))));
        
        
        player.update();
        //Effacer, dessiner, afficher
        window.clear();
        window.draw(niveau);
        window.draw(player);
        drawInventory();
        window.display();
    }
}


void Application::drawInventory(){
    sf::Text text("Gold : " + std::to_string(niveau.getInventory().gold), police);
    text.setFillColor(sf::Color::Yellow);
    window.setView(sf::View(sf::FloatRect( 0.f, 0.f, window.getSize().x, window.getSize().y) ) );
    window.draw(text);
}
