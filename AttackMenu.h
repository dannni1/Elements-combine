#ifndef ATTACKMENU_H
#define ATTACKMENU_H

#include <SFML/Graphics.hpp> //need SFML package
#include <string>

#include "Menu2D.h"
#include "Character.h"

//Attack menu loop
void AttackMenu(sf::RenderWindow& window, Character& Character, sf::Sprite& characterSprite,
                 sf::Sprite& bgSprite){
    //box
    int m_boxSize_x = 400;
    int m_boxSize_y = 100;
    sf::RectangleShape m_Menu_Box(sf::Vector2f(m_boxSize_x, m_boxSize_y));
    m_Menu_Box.setFillColor(sf::Color::Black);
    m_Menu_Box.setPosition(50, window.getSize().y - m_boxSize_y - 150);//offset

    //get names
    std::string arr[4];
    for(int i = 1;i < 5; ++i){
       arr[i-1] = Character.GetAbilityName(i);
    }

    //menu 
    Menu2D m_attackMenu(arr);
    m_attackMenu.SetPosition(m_Menu_Box.getPosition().x ,m_Menu_Box.getPosition().y);

    characterSprite.setPosition(m_Menu_Box.getPosition().x + (m_boxSize_x/2) -50, m_Menu_Box.getPosition().y - 100);

    while (true)
    {

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
                    m_attackMenu.MoveUp();
                    break;
                case sf::Keyboard::Down:
                    m_attackMenu.MoveDown();
                    break;
                case sf::Keyboard::Left:
                    m_attackMenu.MoveLeft();
                    break;
                case sf::Keyboard::Right:
                    m_attackMenu.MoveRight();
                    break;
                default:
                    break;
                }
            }
        }
        window.clear();

        window.draw(bgSprite);
        window.draw(m_Menu_Box);
        m_attackMenu.Draw(window);
        window.draw(characterSprite);
        
        window.display();
    }                                
}

#endif