#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp> 

class Menu{
private:
    int selectedItemIndex;
    int numberOfItems;
    sf::Font font;
    sf::Text* menu;

public:
    Menu(float width, float height, nlohmann::json& menu_json, int numOfItems);
    ~Menu();

    void Draw(sf::RenderWindow &window);
    void SetPosition(const float& X,const float& Y);
    void MoveUp();
    void MoveDown();
    int GetPressedItem(){return selectedItemIndex;}

};


#endif