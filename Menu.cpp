#include <nlohmann/json.hpp> //need json package 
#include <string>

#include "Menu.h"

Menu::Menu(float window_width ,float window_height, nlohmann::json& menu_json, int numOfItems){
    if(!font.loadFromFile("./Assets/Fonts/Raleway-Regular.ttf")){
        //error
    }

    numberOfItems = numOfItems; //min 1
    menu = new sf::Text[numberOfItems];

    for(int i = 0; i < numOfItems; i++){
        menu[i].setFont(font);
        menu[i].setFillColor(sf::Color::White);
        std::string temp = menu_json[std::to_string((i+1))];
        menu[i].setString(temp);
    }

    selectedItemIndex = 0;
    menu[selectedItemIndex].setFillColor(sf::Color::Red);
}


Menu::~Menu(){
    delete [] menu;
}

void Menu::Draw(sf::RenderWindow& window){
    for(int i = 0; i < numberOfItems; ++i){
        window.draw(menu[i]);
    }
}

void Menu::SetPosition(const float& X,const float& Y){
    for(int i = 0; i < numberOfItems; ++i){
        menu[i].setPosition(X + (10), Y + (i*50));
    }
}

void Menu::MoveUp(){
    if(selectedItemIndex-1 >= 0){
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }else{
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex = numberOfItems-1;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void Menu::MoveDown(){
    if(selectedItemIndex+1 < numberOfItems){
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }else{
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex = 0;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}