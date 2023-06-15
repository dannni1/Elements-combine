#ifndef PICK_CHARACTER_H
#define PICK_CHARACTER_H

#include <SFML/Graphics.hpp> //need SFML package

#include"Character.h"


//loop of picking a character
Character* PickCharacter(sf::RenderWindow& m_window, sf::Sprite& m_bgSprite ,std::vector<Character*>* m_character_vector){
    if(m_character_vector->empty())
        return nullptr;

    std::vector<sf::Sprite*> m_characterSprite_vector;
    std::vector<int> playable_characterIndex;
    for(int i = 0; i < m_character_vector->size(); ++i){
        sf::Sprite* temp(m_character_vector->at(i)->GetSprite_ptr());
        if(m_character_vector->at(i)->GetPlayable())
            playable_characterIndex.push_back(i);

        if(!(temp == nullptr))
            m_characterSprite_vector.push_back(new sf::Sprite(*temp)); 
        else{
            std::cout << "character: " << m_character_vector->at(i)->GetName() << " missing sprite\n";
            return nullptr;//error
        }
    }

    if(playable_characterIndex.empty()){
        std::cout << "error all character out of turns\n";
        return nullptr; //error
    }


    int m_vectorIndex = 0;
    sf::CircleShape m_triangle(40, 3);

    m_triangle.setFillColor(sf::Color::Black);
    m_triangle.rotate(180);


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
                case sf::Keyboard::Left:
                    if(m_vectorIndex <= 0){
                        m_vectorIndex = playable_characterIndex.size() -1;
                    } else
                        m_vectorIndex--;
                    break;
                case sf::Keyboard::Right:
                    if((m_vectorIndex + 1) >= playable_characterIndex.size()){
                        m_vectorIndex = 0;
                    } else
                        m_vectorIndex++;
                    break;
                case sf::Keyboard::Enter:
                    for (sf::Sprite* sprite : m_characterSprite_vector) {delete sprite;}
                    return m_character_vector->at(playable_characterIndex.at(m_vectorIndex));
                    break;
                default:
                    break;
                }
            }
        }

        //clear and start drawing
        m_window.clear();

        //backgrownd
        m_window.draw(m_bgSprite);
        
        //characters
        short x_position = 300, y_position = 350;
        for ( auto& sprite : m_characterSprite_vector)
        {
            (*sprite).setPosition(x_position, y_position);
            m_window.draw(*sprite);
            x_position += 100;
            y_position += 100;
        }

        //arrwo on selecte character
        int m_tempNum = playable_characterIndex.at(m_vectorIndex);
        m_triangle.setPosition(m_characterSprite_vector.at(m_tempNum)->getPosition().x + 70 ,
            m_characterSprite_vector.at(m_tempNum)->getPosition().y - 60);
        m_window.draw(m_triangle);

        //show every thing on the screen
        m_window.display();
    }
}

#endif