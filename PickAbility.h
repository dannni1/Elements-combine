#ifndef PICK_ABILITY_H
#define PICK_ABILITY_H

#include <SFML/Graphics.hpp> //need SFML package
#include <string>

#include "Menu2D.h"
#include "Character.h"

//Attack menu loop (add monster)
int PickAbility(sf::RenderWindow& m_window, Character* m_character, 
                 sf::Sprite& m_bgSprite){
    //box
    int m_boxSize_x = 400;
    int m_boxSize_y = 100;
    sf::RectangleShape m_Menu_Box(sf::Vector2f(m_boxSize_x, m_boxSize_y));
    m_Menu_Box.setFillColor(sf::Color::Black);
    m_Menu_Box.setPosition(50, m_window.getSize().y - m_boxSize_y - 150);//offset

    //get names
    std::string arr[4];
    for(int i = 1;i < 5; ++i)
       arr[i-1] = m_character->GetAbilityName(i);

    //menu 
    Menu2D m_attackMenu(arr);
    m_attackMenu.SetPosition(m_Menu_Box.getPosition().x ,m_Menu_Box.getPosition().y);

    sf::Sprite* m_characterSptite = m_character->GetSprite_ptr();

    m_characterSptite->setPosition(m_Menu_Box.getPosition().x + (m_boxSize_x/2) -50, m_Menu_Box.getPosition().y - 100);

    while (true)
    {

        //Process events
        sf::Event event;
        while (m_window.pollEvent(event)) //must be a loop
        {
            if (event.type == sf::Event::Closed)
                m_window.close();
            
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
                case sf::Keyboard::Enter:
                    return m_attackMenu.GetSelectedItem(); //return
                    break;
                case sf::Keyboard::Escape:
                    return -1; //go back
                    break;
                default:
                    break;
                }
            }
        }
        m_window.clear();

        m_window.draw(m_bgSprite);
        m_window.draw(m_Menu_Box);
        m_attackMenu.Draw(m_window);
        m_window.draw(*m_characterSptite);
        
        m_window.display();
    }                                
}

#endif