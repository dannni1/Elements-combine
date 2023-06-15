#ifndef MENU2D_H
#define MENU2D_H

#include <SFML/Graphics.hpp> //need SFML package
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
    int GetSelectedItem(){return (selectedItemIndex_X + selectedItemIndex_Y + 1);} //starts from 0

};




#endif