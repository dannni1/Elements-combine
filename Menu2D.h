#ifndef MENU2D_H
#define MENU2D_H

#include <SFML/Graphics.hpp>
#include <string>

class Menu2D
{
private:
    int selectedItemIndex_X;
    int selectedItemIndex_Y;
    const int numberOfItems2D = 2;
    sf::Font font;
    sf::Text** menu2D;


public:
    Menu2D(const std::string* abiliyNameArry);
    ~Menu2D();

    void Draw(sf::RenderWindow &window);
    void SetPosition(const float& X,const float& Y);
    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();
    //int GetPressedItem(){return selectedItemIndex;}

};




#endif