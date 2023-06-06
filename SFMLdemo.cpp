#include <SFML/Graphics.hpp> //need SFML package
#include <nlohmann/json.hpp> //need json package 
#include <fstream>
#include <filesystem>
#include <iostream>
#include <vector>
#include <string>

//empty constructors
#include "Menu.h"
#include "Menu2D.h"

//objects
#include "Ability.h"
#include "Character.h"
#include "Monster.h"

//classes and methods
#include "Load.h"
#include "AttackMenu.h"



std::vector<sf::Sprite> TextureVector_To_SpiteVector(const std::vector<sf::Texture>& textureVector){
    std::vector<sf::Sprite> spriteVector;

    for (int i = 0; i < textureVector.size(); ++i)
    {
        sf::Sprite sprite;
        sprite.setTexture(textureVector[i]);
        spriteVector.push_back(sprite);
    }

    return spriteVector;
}


//move from vector 1 to vector 2
void MoveSpriteVector(int startPosition, std::vector<sf::Sprite>& sourceVector, std::vector<sf::Sprite>& targetVector){
    targetVector.insert(targetVector.end(), std::make_move_iterator(sourceVector.begin()
                         + startPosition), std::make_move_iterator(sourceVector.end()));
    
    sourceVector.erase(sourceVector.begin() + startPosition, sourceVector.end());
}



void KeyPressEvent(int numOfItem ,sf::RenderWindow& window, Character& Character, sf::Sprite& characterSprite,
                 sf::Sprite& bgSprite){

    switch (numOfItem)
    {
    case 0:
        AttackMenu(window, Character, characterSprite, bgSprite);
        break;
    case 1:
        break;
    case 2: 
        break;
    case 3:
        break;
    case 4:
        break;
    
    default:
        break;
    }
}



int main()
{

    // Create the window
    sf::RenderWindow window(sf::VideoMode(1200, 700), "Demo");

    std::string folderPathTexture ="images/";
    std::string folderPathCharacters="Characters/StarterCharacters/";
    std::string folderPathAbilitys="Characters/Abilities/";

    std::vector<sf::Texture> monsterTexture;
    std::vector<sf::Texture> characterTexture;
    sf::Texture bgTexture;
    sf::Texture leaderTexture;

    //menu
    int boxSize_x = 150;
    int boxSize_y = 250;
    sf::RectangleShape battleMenu_box(sf::Vector2f(boxSize_x, boxSize_y));
    battleMenu_box.setFillColor(sf::Color::Black);
    Menu battleMenu(battleMenu_box.getSize().x, battleMenu_box.getSize().y);


    //using class to a void unwant method calls
    Load load;
    load.LoadTexureFromFolder(folderPathTexture, monsterTexture, characterTexture, bgTexture, leaderTexture);
    Character A(load.LoadChracterFromFolder(folderPathCharacters + "Abraham.json", folderPathAbilitys + "AbrahamAbilities.json"));
    Character B(load.LoadChracterFromFolder(folderPathCharacters + "Alatar.json", folderPathAbilitys + "AlatarAbilities.json"));
    Character C(load.LoadChracterFromFolder(folderPathCharacters + "Billie.json", folderPathAbilitys + "BillieAbilities.json"));

    Character D(load.LoadChracterFromFolder(folderPathCharacters + "Bran.json", folderPathAbilitys + "BranAbilities.json"));
    Character E(load.LoadChracterFromFolder(folderPathCharacters + "Cassandra.json", folderPathAbilitys + "CassandraAbilities.json"));
    Character F(load.LoadChracterFromFolder(folderPathCharacters + "Elvin.json", folderPathAbilitys + "ElvinAbilities.json"));



    //build all the sprites
    std::vector<sf::Sprite> monsterSprite(TextureVector_To_SpiteVector(monsterTexture));
    std::vector<sf::Sprite> characterSprite_front(TextureVector_To_SpiteVector(characterTexture)); //load all the characters
    std::vector<sf::Sprite> characterSprite_back;
    sf::Sprite bgSprite;
    bgSprite.setTexture(bgTexture);
    sf::Sprite leaderSprite;
    leaderSprite.setTexture(leaderTexture);



    //split characters to front and back
    MoveSpriteVector(3, characterSprite_front, characterSprite_back);
    
    // Main loop
    while (window.isOpen())
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
                    battleMenu.MoveUp();
                    break;
                case sf::Keyboard::Down:
                    battleMenu.MoveDown();
                    break;
                case sf::Keyboard::Enter:
                    KeyPressEvent(battleMenu.GetPressedItem(), window, A, characterSprite_front[1], bgSprite);
                    break;
                default:
                    break;
                }
            }
        }
    

        //clear the window
        window.clear();

        //draw on the window: 
        //backgrownd 
        window.draw(bgSprite);

        //leader
        leaderSprite.setPosition(350, 600);
        window.draw(leaderSprite);

        //start position of the monseter imge
        short x_position = 700, y_position = 100;
        for (auto& sprite : monsterSprite)
        {
            sprite.setPosition(x_position, y_position);
            window.draw(sprite);
            x_position += 50;
            y_position += 50;
        }

        //start position of the character imge
        x_position = 300, y_position = 350;
        for ( auto& sprite : characterSprite_front)
        {
            sprite.setPosition(x_position, y_position);
            window.draw(sprite);
            x_position += 100;
            y_position += 100;
        }

        //menu
        battleMenu_box.setPosition(window.getSize().x - boxSize_x - 50, window.getSize().y - boxSize_y - 50);//50 offset
        battleMenu.SetPosition(battleMenu_box.getPosition().x, battleMenu_box.getPosition().y);

        window.draw(battleMenu_box);
        battleMenu.Draw(window);

        //display the window
        window.display();
    }

    return 0;
}//end of main