#include "Menu2D.h"

//arry must be size of 4 
Menu2D::Menu2D(const std::string* abiliyNameArry){ 
    if(!font.loadFromFile("./Assets/Fonts/Raleway-Regular.ttf")){
        //error 
    }

    selectedItemIndex_X = 0;
    selectedItemIndex_Y = 0;
    menu2D = new sf::Text*[numberOfItems2D];

    for(int i = 0; i < numberOfItems2D; ++i){
        menu2D[i] = new sf::Text[numberOfItems2D];
    }

    int loopNum = 0;
    for(int i = 0; i < numberOfItems2D; ++i){
        for (int j = 0; j < numberOfItems2D; ++j)
        {
            menu2D[j][i].setFont(font);
            menu2D[j][i].setFillColor(sf::Color::White);
            menu2D[j][i].setString(abiliyNameArry[loopNum++]);
        }}

    menu2D[selectedItemIndex_X][selectedItemIndex_Y].setFillColor(sf::Color::Red);
}


Menu2D::~Menu2D(){
    for (int i = 0; i < numberOfItems2D; ++i)
    {
        delete [] menu2D[i];
    }
    
}

void Menu2D::Draw(sf::RenderWindow& window){
    for(int i = 0; i < numberOfItems2D; ++i){
        for (int j = 0; j < numberOfItems2D; ++j)
        {
            window.draw(menu2D[i][j]);
        }
        
    }
}

void Menu2D::SetPosition(const float& X,const float& Y){
    float offSetX = 200;
    float offSetY = 50;
    for(int i = 0; i < numberOfItems2D; ++i){
        for (int j = 0; j < numberOfItems2D; ++j)
        {
            menu2D[i][j].setPosition(X + (i*offSetX) + 10, Y + (j*offSetY));//10 start offset look better 
        }
        
    }
}

void Menu2D::MoveUp(){
    if(selectedItemIndex_Y-1 >= 0){
        menu2D[selectedItemIndex_X][selectedItemIndex_Y].setFillColor(sf::Color::White);
        selectedItemIndex_Y--;
        menu2D[selectedItemIndex_X][selectedItemIndex_Y].setFillColor(sf::Color::Red);
    }else{
        menu2D[selectedItemIndex_X][selectedItemIndex_Y].setFillColor(sf::Color::White);
        selectedItemIndex_Y = numberOfItems2D-1;
        menu2D[selectedItemIndex_X][selectedItemIndex_Y].setFillColor(sf::Color::Red);
    }
}

void Menu2D::MoveDown(){
    if(selectedItemIndex_Y+1 < numberOfItems2D){
        menu2D[selectedItemIndex_X][selectedItemIndex_Y].setFillColor(sf::Color::White);
        selectedItemIndex_Y++;
        menu2D[selectedItemIndex_X][selectedItemIndex_Y].setFillColor(sf::Color::Red);
    }else{
        menu2D[selectedItemIndex_X][selectedItemIndex_Y].setFillColor(sf::Color::White);
        selectedItemIndex_Y = 0;
        menu2D[selectedItemIndex_X][selectedItemIndex_Y].setFillColor(sf::Color::Red);
    }
}

void Menu2D::MoveLeft(){
    if(selectedItemIndex_X-1 >= 0){
        menu2D[selectedItemIndex_X][selectedItemIndex_Y].setFillColor(sf::Color::White);
        selectedItemIndex_X--;
        menu2D[selectedItemIndex_X][selectedItemIndex_Y].setFillColor(sf::Color::Red);
    }else{
        menu2D[selectedItemIndex_X][selectedItemIndex_Y].setFillColor(sf::Color::White);
        selectedItemIndex_X = numberOfItems2D-1;
        menu2D[selectedItemIndex_X][selectedItemIndex_Y].setFillColor(sf::Color::Red);
    }
}

void Menu2D::MoveRight(){
    if(selectedItemIndex_X+1 < numberOfItems2D){
        menu2D[selectedItemIndex_X][selectedItemIndex_Y].setFillColor(sf::Color::White);
        selectedItemIndex_X++;
        menu2D[selectedItemIndex_X][selectedItemIndex_Y].setFillColor(sf::Color::Red);
    }else{
        menu2D[selectedItemIndex_X][selectedItemIndex_Y].setFillColor(sf::Color::White);
        selectedItemIndex_X = 0;
        menu2D[selectedItemIndex_X][selectedItemIndex_Y].setFillColor(sf::Color::Red);
    }
}


