#ifndef Level_hpp
#define Level_hpp

#include "TileMap.hpp"
#include <vector>
#include <SFML/Audio.hpp>


struct Inventory{
    int gold;
};

class Level : public sf::Drawable, public sf::Transformable{
public:
    Level(std::string file);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    bool operator()(sf::Vector2i pos);
    
    Inventory getInventory();
    
private:
    TileMap map;
    std::vector<std::vector<int> > level;
    sf::Vector2i dim;
    
    sf::VertexArray goldMap;
    std::vector<sf::Vector2i> goldList;
    sf::Texture goldTexture;
    sf::SoundBuffer coinBuffer;
    sf::Sound coinSound;
    Inventory stuff;
    sf::Music victory;
    sf::Music prelude;
    void goldListToMap();
};

#endif /* Level_hpp */
