#ifndef ATTACK_H
#define ATTACK_H

#include <SFML/Graphics.hpp> //need SFML package
#include <iostream>
#include <cmath>
#include <algorithm>

#include "monster.h"
#include "Character.h"


class Attack
{
private:
    void ClearMemory(std::vector<sf::Sprite*>& m_monsterSprite_vector, std::vector<sf::Sprite*>& m_characterSprite_vector){
        for(auto& sprite : m_characterSprite_vector)
            delete sprite;

        for(auto& sprite : m_monsterSprite_vector)
            delete sprite;
    }

    bool HitTarget_monster(Monster* m_monster, int m_power){
        m_monster->TakeDamge(m_power);
        if(m_monster->GetHealth() <= 0)
            return true; //dead

        return false;
    }

    bool HitTarget_character(Character* m_character, int m_power){
        m_character->TakeDamge(m_power);
        if(m_character->GetHealth() <= 0)
            return true;//dead

        return false;
    }

    bool EventHendler_monster(sf::Event& m_event,bool& m_enemy, int& m_index, std::vector<sf::Sprite*>& m_monsterSprite_vector){
            switch (m_event.key.code)
            {
            case sf::Keyboard::Left:
                if(m_index > 0)
                    m_index--;
                else
                    m_index = m_monsterSprite_vector.size() -1;
                break;
            case sf::Keyboard::Right:
                if(m_index+1 < m_monsterSprite_vector.size())
                    m_index++;
                else
                    m_index = 0;
                break;
            case sf::Keyboard::Tab:
                m_index = 0;
                m_enemy = false;
                break;
            case sf::Keyboard::Enter:
                return true;
                break;
        
            default:
                break;
            }

            return false;
    }

    bool EventHendler_chracter(sf::Event& m_event,bool& m_enemy, int& m_index, std::vector<sf::Sprite*>& m_characterSprite_vector){
            switch (m_event.key.code)
            {
            case sf::Keyboard::Left:
                if(m_index > 0)
                    m_index--;
                else
                    m_index = m_characterSprite_vector.size() -1;
                break;
            case sf::Keyboard::Right:
                if(m_index+1 < m_characterSprite_vector.size())
                    m_index++;
                else
                    m_index = 0;
                break;
            case sf::Keyboard::Tab:
                m_index = 0;
                m_enemy = true;
                break;
            case sf::Keyboard::Enter:
                return true;
                break;
            case sf::Keyboard::Escape:
                return false;
                break;
        
            default:
                break;
            }

            return false;
    }

public:

    //loop of picking a character
    bool PickTarget(sf::RenderWindow& m_window, sf::Sprite& m_bgSprite ,std::vector<Monster*>* m_monster_vector, std::vector<Character*>* m_character_vector,
                        int m_power){

        if(m_monster_vector->empty() || m_character_vector->empty()) {}
            //empty

        //monsters sprites
        std::vector<sf::Sprite*> m_monsterSprite_vector;
        for(int i = 0; i < m_monster_vector->size(); ++i){
            sf::Sprite* temp(m_monster_vector->at(i)->GetSprite_ptr());

            if(!(temp == nullptr))
                m_monsterSprite_vector.push_back(new sf::Sprite(*temp)); 
            else{
                std::cout << "character: " << m_monster_vector->at(i)->GetName() << " missing sprite\n";
            }
        }

        //character sprites
        std::vector<sf::Sprite*> m_characterSprite_vector;
        for(int i = 0; i < m_character_vector->size(); ++i){
            sf::Sprite* temp(m_character_vector->at(i)->GetSprite_ptr());

            if(!(temp == nullptr))
                m_characterSprite_vector.push_back(new sf::Sprite(*temp)); 
            else{
                std::cout << "character: " << m_character_vector->at(i)->GetName() << " missing sprite\n";
            }
        }

        int m_index = 0, m_x_position = 0, m_y_position = 0;
        bool m_enemy = true;
        float m_angle = 0.0f;
        sf::CircleShape m_triangle(40, 3);

        m_triangle.setFillColor(sf::Color::Black);
        m_triangle.rotate(180);
        m_triangle.setOrigin(m_triangle.getLocalBounds().width/2, m_triangle.getLocalBounds().height/2);

        while (true)
        {

            //Process events
            sf::Event m_event;
            while (m_window.pollEvent(m_event)) //must be a loop
            {
                if (m_event.type == sf::Event::Closed)
                    m_window.close();
                
                if(m_event.type == sf::Event::KeyReleased){
                    if(m_event.key.code == sf::Keyboard::Escape)
                        return false;
                        
                    if(m_enemy){
                        if(EventHendler_monster(m_event, m_enemy, m_index, m_monsterSprite_vector)){
                            if(HitTarget_monster(m_monster_vector->at(m_index), m_power)){
                                //dead
                                m_monster_vector->erase(m_monster_vector->begin() + m_index);
                            }
                            ClearMemory(m_monsterSprite_vector, m_characterSprite_vector);
                            return true;   //end

                    }}else {
                        if(EventHendler_chracter(m_event, m_enemy, m_index, m_characterSprite_vector)){
                            if(HitTarget_character(m_character_vector->at(m_index), m_power)){
                                //dead
                                m_character_vector->erase(m_character_vector->begin() + m_index);   
                            }
                            ClearMemory(m_monsterSprite_vector, m_characterSprite_vector);
                            return true;   //end                 
                    }}
                }
            }//events

            //clear and start drawing
            m_window.clear();

            //backgrownd
            m_window.draw(m_bgSprite);
            
            //characters
            m_x_position = 700, m_y_position = 100;
            for (auto& sprite : m_monsterSprite_vector)
            {
                (*sprite).setPosition(m_x_position, m_y_position);
                m_window.draw(*sprite);
                m_x_position += 100;
                m_y_position += 100;
            }

            //start position of the character imge
            m_x_position = 300, m_y_position = 350;
            for (auto& sprite : m_characterSprite_vector)
            {
                (*sprite).setPosition(m_x_position, m_y_position);
                m_window.draw(*sprite);
                m_x_position += 100;
                m_y_position += 100;
            }

            //arrwo on selecte character
            short m_offSet_X = 40, m_offSet_Y = -60;
            m_x_position = m_enemy ? m_monsterSprite_vector.at(m_index)->getPosition().x + m_offSet_X : m_characterSprite_vector.at(m_index)->getPosition().x + m_offSet_X;
            m_y_position = m_enemy ? m_monsterSprite_vector.at(m_index)->getPosition().y + m_offSet_Y : m_characterSprite_vector.at(m_index)->getPosition().y + m_offSet_Y;
            m_triangle.setPosition(m_x_position, m_y_position);

            //spin the arrwo
            m_angle += 0.2f;
            float m_triangle_spin = std::abs(std::sin(m_angle/180.0f * 3.14159f));
            m_triangle.setScale(sf::Vector2f(m_triangle_spin, 1.0f));


            m_window.draw(m_triangle);

            //show every thing on the screen
            m_window.display();
        }// while (true)
    } //end of PickTarget 
};
#endif