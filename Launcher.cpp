//global includes
#include <SFML/Graphics.hpp> //need SFML package
#include <nlohmann/json.hpp> //need json package 
#include <fstream>
#include <filesystem>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
 
 
#include "SceneManger.h"
#include "Scenes.h"


int main(){

    //need to be loaded from a file
    //window size
    int windowSize_X = 1200;
    int windowSize_Y = 700;

    sf::RenderWindow renderWindow(sf::VideoMode(windowSize_X, windowSize_Y), "Game_name"); 

    SceneManger sceneManger;
    Scene scene = Scene::MainMenu;


    while (renderWindow.isOpen())
    {
        scene = sceneManger.ChangeScene(renderWindow, scene);
    }
    


        //run main menu  int

        //switch for input

        //on new game: --create new file, run the game.----

    //on close window: release all memory

return 1;

}//main
