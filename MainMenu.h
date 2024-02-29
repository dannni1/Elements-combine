#ifndef MAINMENU_H
#define MAINMENU_H

#include <SFML/Graphics.hpp> //need SFML package

#include "Menu.h"

class MainMenu{
private:
    void MainMenu_Quit(sf::RenderWindow& window);
    void MainMenu_Settings(sf::RenderWindow& window);
    void MainMenu_LoadSave(sf::RenderWindow& window);
    void MainMenu_NewGame(sf::RenderWindow& window);
    bool MainMenu_select(int itemNum, sf::RenderWindow& window);

public:
    MainMenu() {}
    ~MainMenu() {}

    int MainMenu_Run(sf::RenderWindow& window);
};


#endif