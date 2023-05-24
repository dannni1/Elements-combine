#include <string>
#include "Ability.h"

#ifndef MONSTER_H
#define MONSTER_H

using String = std::string;


class Monster {
    //TO DO: need to add special defense 
    private:
    int maxHealth, experience, level, MaxSpeed, maxDefense;
    int health, speed, defense;
    String monsterName;

    Ability ability1;
    Ability ability2;
    Ability ability3;
    Ability ability4;

    public:
        Monster(int newHealth ,int newexperience ,int newlevel ,int newSpeed ,int newDefense,const String& newName){
            maxHealth = newHealth;
            experience = newexperience;
            level = newlevel;
            MaxSpeed = newSpeed;
            maxDefense = newDefense;
            monsterName = newName;

            health = maxHealth;
            speed = MaxSpeed;
            defense = maxDefense;
        }

        //changer the old ability to a new one
        bool AddAbility(int numAbility, const Ability& ability){
            if(numAbility > 4 || numAbility < 1)
                return false;
            if(numAbility == 1){
                Ability ability1 = Ability(ability);
                return true;
            }
            if (numAbility == 2)
            {
                Ability ability2 = Ability(ability);
                return true;
            }
            if (numAbility == 3)
            {
                Ability ability3 = Ability(ability);
                return true;
            }
            if (numAbility == 4)
            {
                Ability ability4 = Ability(ability);
                return true;
            }
            

            return false;
        }

        int GetHealth(){
            return health;
        }
        int GetSpeed(){
            return speed;
        }
        int GetDefense(){
            return defense;
        }
        String GetName(){
            return monsterName;
        }
        void TakeDamge(int damge){
            health -= damge;
        }
        
};

#endif