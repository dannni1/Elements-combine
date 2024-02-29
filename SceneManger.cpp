#include <SFML/Graphics.hpp> //need SFML package

#include "SceneManger.h"
#include "Scenes.h"
#include "Game.h"

#include "MainMenu.h"

Scene SceneManger::Change_To_MainMenu(sf::RenderWindow& window){
    MainMenu mainMenu;
    int item = mainMenu.MainMenu_Run(window);
    if(item == 0)
        return Scene::Battle;
    else if (item == 1) {}
        //load
    else
        return Scene::Quit;

    return Scene::Null;
}

Scene SceneManger::Change_To_Battle(sf::RenderWindow& window){
    Game_Run(window);
    return Scene::Null;
}

Scene SceneManger::ChangeScene(sf::RenderWindow& window, Scene& scene){

    switch (scene)
    {
    case Scene::MainMenu:
         return Change_To_MainMenu(window);
        break;
    case Scene::Battle:
        Change_To_Battle(window);
        return Scene::Quit;
        break;
    case Scene::Quit:
        window.close();
        return Scene::Quit;
        break;
    
    default:
        return Scene::Quit; //need to add on fail
        break;
    }
}

