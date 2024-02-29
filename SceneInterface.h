#ifndef SCENE_INTERFACE_H
#define SCENE_INTERFACE_H

#include <SFML/Graphics.hpp> //need SFML package


class SceneInterface
{
public:
    virtual void handleEvent(sf::Event event) = 0;
    //virtual void update(float deltatime) = 0; maybe in the future?
    virtual void draw(sf::RenderWindow& window) = 0;
};


#endif