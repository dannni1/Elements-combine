#include <SFML/Graphics.hpp> //need SFML package
#include <nlohmann/json.hpp> //need json package 
#include <fstream>
#include <filesystem>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>


//empty constructors
#include "Menu.h"
#include "Menu2D.h"

//objects
#include "Ability.h"
#include "Character.h"
#include "Monster.h"

//static
#include "StaticMembers.h"
static std::vector<Monster*>* STATIC_MonsterVector = new std::vector<Monster*>;

//classes and methods
#include "Load.h"
#include "PickAbility.h"
#include "PickCharacter.h"
#include "Attack.h"


int CheckState(std::vector<Character*>* m_character_vector, std::vector<Monster*>* m_monster_vector){
    if(m_monster_vector->empty())
        return 1;   //win

    //if leader is dead loss return 2


    bool characters_playable = false;
    for(int i = 0; i < m_character_vector->size(); ++i){
        if(m_character_vector->at(i)->GetPlayable()){
            characters_playable = true;
            break;
        }
    }

    if(!characters_playable)
        return 9;   //all characters run out of moves

    return 0;   //game in progress
} 

//move from vector 1 to vector 2
void MoveCharacterVector(int startPosition, std::vector<Character*>* sourceVector, std::vector<Character*>* targetVector){
    targetVector->insert(targetVector->end(), std::make_move_iterator(sourceVector->begin()
                         + startPosition), std::make_move_iterator(sourceVector->end()));
    
    sourceVector->erase(sourceVector->begin() + startPosition, sourceVector->end());
}


//give back selected ability power if number of use left. attack a monster.
int UseCharacterAbility(Character& m_character, const int m_numAbility) {
    int power = m_character.UseAbility(m_numAbility);
    if(power != -1) { 
        return power;
        }

    std::cout << "run out of uses\n";
    return -1; //fail  
}


//add monster
int KeyPressEvent(const int m_numOfItem, sf::RenderWindow& m_window, std::vector<Character*>* m_character_vector,
                    std::vector<Monster*>* m_monster_vector, sf::Sprite& m_bgSprite){

    switch (m_numOfItem)
    {
    case 0:
    {
        Character* m_temp = PickCharacter(m_window, m_bgSprite, m_character_vector);
        if(m_temp == nullptr)
            return 0;

        int ability = PickAbility(m_window, m_temp, m_bgSprite);
        if(ability == -1)
            return 0;
        
        int m_power = UseCharacterAbility(*m_temp, ability);
        Attack m_attack;
        if(m_attack.PickTarget(m_window, m_bgSprite, m_monster_vector, m_character_vector, m_power)){
            m_temp->Played();
            return CheckState(m_character_vector, m_monster_vector);
        }
        
        return 0;
    }
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

    return 0;
}

Character LoadbyName_Character(const std::string& m_name, const std::string& m_filePath){
    Load m_load;
    std::string filePathAbilitys = m_filePath + "Abilities/";
    std::string filePathTexture = m_filePath + "Textures/";
    return(m_load.LoadChracter(m_filePath + m_name + ".json", filePathAbilitys + m_name + "Abilities.json", filePathTexture + m_name + "Textures.png"));
}

void NewTurn(std::vector<Character*>* m_chracterfront_vector){
    for(int i = 0; i < m_chracterfront_vector->size(); ++i){
        m_chracterfront_vector->at(i)->Playable();
    }
}

void UpdateHpVector(std::vector<std::string>& m_chracter_hpString, std::vector<Character*>* chracterfront_vector){
    for(int i = 0; i < m_chracter_hpString.size(); ++i){
        m_chracter_hpString.at(i) = std::to_string(chracterfront_vector->at(i)->GetHealth());
    }
}


int Game_Run(sf::RenderWindow& window){


    std::string folderPathCharacters = "Assets/Characters/";
    std::string folderPathAbilitys = folderPathCharacters + "Abilities/";
    std::string folderPathTexture  = folderPathCharacters + "Textures/";

    std::vector<sf::Sprite> chracterSprites_vector;
    std::vector<Character*>* chracterfront_vector = new std::vector<Character*>;
    std::vector<Character*>* chracterback_vector = new std::vector<Character*>;
    std::vector<Monster*>* monster_vector = new std::vector<Monster*>;
    std::vector<std::string> chracter_hpString;

    //using class to a void unwant method calls
    Load load;


    //chracters:
    //load Characters to dynamic memory
    Character* A = new Character(LoadbyName_Character("Abraham", folderPathCharacters));
    sf::Sprite A_sptite(*(A->GetTexture_ptr()));
    A->SetSprite_prt(&A_sptite);
    chracterfront_vector->push_back(A);
    chracter_hpString.push_back(std::to_string(A->GetHealth()));
    
    Character* B = new Character(LoadbyName_Character("Alatar", folderPathCharacters));
    sf::Sprite B_sptite(*(B->GetTexture_ptr()));
    B->SetSprite_prt(&B_sptite);
    chracterfront_vector->push_back(B);
    chracter_hpString.push_back(std::to_string(B->GetHealth()));

    Character* C = new Character(LoadbyName_Character("Billie", folderPathCharacters));
    sf::Sprite C_sptite(*(C->GetTexture_ptr()));
    C->SetSprite_prt(&C_sptite);
    chracterfront_vector->push_back(C);
    chracter_hpString.push_back(std::to_string(C->GetHealth()));

    Character* D = new Character(LoadbyName_Character("Bran", folderPathCharacters));
    sf::Sprite D_sptite(*(D->GetTexture_ptr()));
    D->SetSprite_prt(&D_sptite);
    chracterfront_vector->push_back(D);

    Character* E = new Character(LoadbyName_Character("Cassandra", folderPathCharacters));
    sf::Sprite E_sptite(*(E->GetTexture_ptr()));
    E->SetSprite_prt(&E_sptite);
    chracterfront_vector->push_back(E);

    Character* F = new Character(LoadbyName_Character("Elvin", folderPathCharacters));
    sf::Sprite F_sptite(*(F->GetTexture_ptr()));
    F->SetSprite_prt(&F_sptite);
    chracterfront_vector->push_back(F);

    MoveCharacterVector(3, chracterfront_vector, chracterback_vector);//split front and back


    //backgrownd:
    sf::Texture bgTexture;
    load.LoadTexture("Assets/Images/Levels/background.png", bgTexture);
    //sf::Texture leaderTexture;


    //monsters:
    sf::Texture X_texture;
    X_texture.loadFromFile("Assets/Images/Monsters/stonemonster.png");
    sf::Sprite X_Sptire(X_texture);
    Monster X("x", 10000, 5, X_texture);
    X.SetSprite_prt(&X_Sptire);
    monster_vector->push_back(&X);

    //build all the sprites
    sf::Sprite bgSprite;
    bgSprite.setTexture(bgTexture);
    //sf::Sprite leaderSprite;
    //leaderSprite.setTexture(leaderTexture);


    //menu
    int boxSize_x = 150;
    int boxSize_y = 250;
    sf::RectangleShape battleMenu_box(sf::Vector2f(boxSize_x, boxSize_y));
    battleMenu_box.setFillColor(sf::Color::Black);

    nlohmann::json battleMenu_json;
    std::ifstream battleMenu_readFile("Assets/Menu/BattleMenu.json"); //json location
    battleMenu_readFile >> battleMenu_json;
    battleMenu_readFile.close();
    Menu battleMenu(battleMenu_box.getSize().x, battleMenu_box.getSize().y, battleMenu_json, battleMenu_json.size());

    int boxSize_x2 = 150;
    int boxSize_y2 = 80;
    sf::RectangleShape character_hpBox(sf::Vector2f(boxSize_x2, boxSize_y2));
    character_hpBox.setFillColor(sf::Color::Black);

    sf::Font font;
    if(!font.loadFromFile("./Assets/Fonts/Raleway-Regular.ttf")){
        //error
    }

    sf::Text character_hpText;
    character_hpText.setFont(font);

    
    //setup for first turn
    NewTurn(chracterfront_vector);

    // Main loop
    while (window.isOpen())
    {

        //Character test = *PickCharacter(window, bgSprite);

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
                {
                    int state = KeyPressEvent(battleMenu.GetPressedItem(), window, chracterfront_vector, monster_vector, bgSprite);//A is character 

                    if(state != 0)
                        switch (state)
                        {
                        case 1:
                            return 1; //win
                            break;
                        case 2:
                            return 2; //loss
                            break;
                        case 9:
                            //TO DO: monster move
                            NewTurn(chracterfront_vector);
                            break;


                        default:
                            break;
                        }
                }
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
        //leaderSprite.setPosition(350, 600);
        //window.draw(leaderSprite);

        //start position of the monseter imge
        short x_position = 700, y_position = 100;
        for (auto& monster_ptr : *monster_vector)
        {
            monster_ptr->GetSprite_ptr()->setPosition(x_position, y_position);
            window.draw(*(monster_ptr->GetSprite_ptr()));
            x_position += 50;
            y_position += 50;
        }


        //start position of the character imge
        x_position = 300, y_position = 350;
        for (auto& Character_ptr : *chracterfront_vector)
        {
            Character_ptr->GetSprite_ptr()->setPosition(x_position, y_position);
            window.draw(*(Character_ptr->GetSprite_ptr()));
            x_position += 100;
            y_position += 100;
        }


        //menu
        battleMenu_box.setPosition(window.getSize().x - boxSize_x - 50, window.getSize().y - boxSize_y - 50);//50 offset
        battleMenu.SetPosition(battleMenu_box.getPosition().x, battleMenu_box.getPosition().y);

        window.draw(battleMenu_box);
        battleMenu.Draw(window);

        std::string str1 = "Health: " + std::to_string(A->GetHealth());
        character_hpText.setString(str1);
        character_hpText.setPosition(100,100);

        window.draw(character_hpBox);
        window.draw(character_hpText);

        //display the window
        window.display();
    }

    return 0;
}//end of main