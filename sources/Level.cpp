#include "Level.hpp"
#include "ResourcePath.hpp"
#include "Perlin.hpp"

#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

Level::Level(std::string file)
{
    std::ifstream stream(resourcePath() + file);
    
    int x=512, y=512;
    //stream >> x >> y;
    
    
    dim = sf::Vector2i(x,y);
    
    level = std::vector<std::vector<int> >(x, std::vector<int>(y, 0));
    
    for(int j=0; j<y; j++){
        for(int i=0; i<x; i++){
            //stream >> level[i][j];
            //level[i][j] = (Get2DPerlinNoiseValue(i,j, 10)+1)*100;
            float perlin = Get2DPerlinNoiseValue(i,j, 10);
            if ( perlin > 0.25)
                level[i][j] = 11*23+6; //Montagnes
            else if (perlin > 0.05)
                level[i][j] = 23; //Foret
            else if ( perlin > -0.3)
                level[i][j] = 0;// Herbe
            else
                level[i][j] = 90; // Eau
        }
    }
    
    map.load("textures.png", sf::Vector2u(32, 32), level, x, y);
    
    srand(time(NULL));
    while (goldList.size()<20)
    {
        sf::Vector2i g(rand()%x, rand()%y);
        if(operator()(g))
            goldList.push_back(g);
    }
    
    goldTexture.loadFromFile(resourcePath() + "gold.png");
    
    goldListToMap();
    
    stuff.gold = 0;
    
    coinBuffer.loadFromFile(resourcePath() + "coin.wav");
    coinSound.setBuffer(coinBuffer);
    
    victory.openFromFile(resourcePath() + "ffvi.ogg");
    
    prelude.openFromFile(resourcePath() + "prelude.ogg");
    prelude.setLoop(true);
    prelude.setVolume(60);
    prelude.play();
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    
    target.draw(map, states);
    target.draw(goldMap, &goldTexture);
}

bool Level::operator()(sf::Vector2i pos)
{
    bool vide;
    if(pos.x < dim.x && pos.y < dim.y && pos.x >= 0 && pos.y >= 0){
        if(level[pos.x][pos.y] == 90 || level[pos.x][pos.y] == 11*23+6)
            vide = false;
        else
            vide = true;
        
        std::vector<sf::Vector2i>::iterator it;
        it = find(goldList.begin(), goldList.end(), pos);
        if(it != goldList.end())
        {
            coinSound.play();
            goldList.erase(it);
            goldListToMap();
            stuff.gold++;
            if(goldList.size() == 0){
                prelude.stop();
                victory.play();
            }
        }
    }
    else
        vide = true;
    
    return vide;
}

Inventory Level::getInventory(){
    return stuff;
}

void Level::goldListToMap(){
    goldMap.setPrimitiveType(sf::Quads);
    goldMap.resize(goldList.size()*4);
    for(int i=0; i<goldList.size(); i++)
    {
        int x = goldList[i].x;
        int y = goldList[i].y;
        goldMap[4*i].position = sf::Vector2f(x*32, y*32);
        goldMap[4*i+1].position = sf::Vector2f((x+1)*32, y*32);
        goldMap[4*i+2].position = sf::Vector2f((x+1)*32, (y+1)*32);
        goldMap[4*i+3].position = sf::Vector2f(x*32, (y+1)*32);
        
        goldMap[4*i].texCoords = sf::Vector2f(0.f, 0.f);
        goldMap[4*i+1].texCoords = sf::Vector2f(32.f, 0.f);
        goldMap[4*i+2].texCoords = sf::Vector2f(32.f, 32.f);
        goldMap[4*i+3].texCoords = sf::Vector2f(0.f, 32.f);
    }
}
