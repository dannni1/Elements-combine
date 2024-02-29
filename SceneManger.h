#ifndef SCENE_MANGER_H
#define SCENE_MANGER_H

#include <SFML/Graphics.hpp> //need SFML package
#include "Scenes.h"

class SceneManger
{
    private:
        Scene Change_To_MainMenu(sf::RenderWindow& window);
        Scene Change_To_Battle(sf::RenderWindow& window);


    public:
        SceneManger(){
            #include "Scenes.h"
        }

        Scene ChangeScene(sf::RenderWindow& window, Scene& scene);
        
};


#endif