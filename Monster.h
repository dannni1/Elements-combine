#ifndef MONSTER_H
#define MONSTER_H

#include <SFML/Graphics.hpp> //need SFML package
#include <string>

#include "Ability.h"


class Monster {
    //TO DO: need to add special defense 
    private:
    int c_maxHealth, c_level, c_maxDefense; //c for class
    int c_health, c_defense;
    std::string c_monsterName;

    
    sf::Texture c_monsterTexture;
    sf::Sprite* c_monster_ptrSprite;

    //chack if uses left and return the ability power
    int UseAbilityHelper(Ability ability){
        if(ability.LowerUses())
            return ability.GetPower();

        return 0;
    }

    public:
        //Empty constractor
        Monster(){
            c_maxHealth = -1;
            c_level = -1;
            c_maxDefense = -1;
            c_monsterName = "";

            c_health = c_maxHealth;
            c_defense = c_maxDefense;
        }

        //constractor 
        Monster(const std::string& newName, int newHealth, int newDefense)
        : c_maxHealth(newHealth), c_maxDefense(newDefense), c_monsterName(newName)
        {
            c_health = c_maxHealth;
            c_defense = c_maxDefense;
        }

        //constractor with texture
        Monster(const std::string& newName, int newHealth, int newDefense, sf::Texture newTexure)
        : c_maxHealth(newHealth), c_maxDefense(newDefense), c_monsterName(newName), c_monsterTexture(newTexure)
        {
            c_health = c_maxHealth;
            c_defense = c_maxDefense;
        }

        ~Monster(){}



        //take damge and return the damge obj take 
        int TakeDamge(const int m_damge){
            int m_temp = m_damge - c_defense;
            if(m_temp > 0)
                c_health -= m_temp;
            
            return m_temp;
        }

        
        //simple attribute returns
        int GetHealth() const{
            return c_health;
        }
        int GetDefense() const{
            return c_defense;
        }
        int GetLevel() const{
            return c_level;
        }
        std::string GetName() const{
            return c_monsterName;
        }
        //give a pointer to character texture
        sf::Texture* GetTexture_ptr() {
            sf::Texture* ptr = &c_monsterTexture;
            return ptr;
        }
        //give the character sprite pointer
        sf::Sprite* GetSprite_ptr() const{
            return c_monster_ptrSprite;
        }

        //simple set attribute
        void SetHealth(int newHealth) {
            c_health = newHealth;
        }
        void SetDefense(int newDefense) {
             c_defense = newDefense;
        }
        void SetLevel(int newLevel) {
            c_level = newLevel;
        }
        void SetName(const std::string& newName) {
            c_monsterName.assign(newName);
        }
        /*void SetTexture(const sf::Texture newTexture) {
            c_characterTexture = std::move(sf::Texture(newTexture));;
        } ------------------- TOO EXPESIVE (bad for gpu)------------------------
        */
        void SetSprite_prt(sf::Sprite* newSprite_ptr) {
            c_monster_ptrSprite = newSprite_ptr;
        }

        
};

#endif