#include <SFML/Graphics.hpp> //need SFML package
#include <nlohmann/json.hpp> //need json package 
#include <fstream>

#include "Menu.h"
#include "MainMenu.h"


void MainMenu::MainMenu_Quit(sf::RenderWindow& window){
    window.close();
}

void MainMenu::MainMenu_Settings(sf::RenderWindow& window){
    //settings
}

void MainMenu::MainMenu_LoadSave(sf::RenderWindow& window){
    //Load Save
}

void MainMenu::MainMenu_NewGame(sf::RenderWindow& window){
    //new game
}

bool MainMenu::MainMenu_select(int itemNum, sf::RenderWindow& window){
    switch (itemNum)
    {
    case 0: //new game
        MainMenu_NewGame(window);
        return true;
        break;
    case 1: //load save
        MainMenu_LoadSave(window);
        return true;
        break;
    case 2: //settings
        MainMenu_Settings(window);
        return false;
        break;
    case 3: //quit
        MainMenu_Quit(window);
        return true;
        break;
    
    default:
        return false;
        break;
    }
}
//end of private


int MainMenu::MainMenu_Run(sf::RenderWindow& window){

    nlohmann::json MainMenu_json;
    std::ifstream readFile("Assets/Menu/MainMenu.json"); //json location

    if(readFile){
    readFile >> MainMenu_json;
    readFile.close();
    }

    Menu menu(window.getSize().x, window.getSize().y, MainMenu_json, MainMenu_json.size());

    while (window.isOpen())
    {
        //refresh window:
        window.clear();

        int offSet_X = -100;
        int offSet_Y = -100;
        menu.SetPosition(window.getSize().x/2 + offSet_X, window.getSize().y/2 + offSet_Y);
        menu.Draw(window);

        //Process events
        sf::Event event;
        while (window.pollEvent(event)) //must be a loop
        {
            if (event.type == sf::Event::Closed)
                window.close();
            
            if(event.type == sf::Event::KeyReleased){
                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                    menu.MoveUp();
                    break;
                case sf::Keyboard::Down:
                    menu.MoveDown();
                    break;
                case sf::Keyboard::Enter:
                    int itemSelected = menu.GetPressedItem();
                    if(MainMenu_select(itemSelected, window));
                        return itemSelected;
                    break;
                }
            }
        }
        
        window.display();
    }

    return 4; //quit
}
//end of public
