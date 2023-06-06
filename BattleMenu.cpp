#include "Menu.h"

Menu::Menu(float width ,float height){
    if(!font.loadFromFile("./Assets/Fonts/Raleway-Regular.ttf")){
        //error
    }

    selectedItemIndex = 0;
    numberOfItems = 5; //5 is the number of options in the menu
    menu = new sf::Text[numberOfItems];


    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Red);
    menu[0].setString("Attack");
    
    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Combo");

    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setString("Swap");

    menu[3].setFont(font);
    menu[3].setFillColor(sf::Color::White);
    menu[3].setString("Item");

    menu[4].setFont(font);
    menu[4].setFillColor(sf::Color::White);
    menu[4].setString("Run");
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