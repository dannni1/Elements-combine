#include <string>
#include "Ability.h"

#ifndef CHARACTER_H
#define CHARACTER_H

using String = std::string;

class Character {
    //TO DO: need to add special defense 
    private:
    int maxHealth, experience, level, MaxSpeed, maxDefense;
    int health, speed, defense;
    String characterName;

    Ability ability1;
    Ability ability2;
    Ability ability3;
    Ability ability4;

    public:
        Character(int newHealth ,int newexperience ,int newlevel ,int newSpeed ,int newDefense,const String& newName){
            maxHealth = newHealth;
            experience = newexperience;
            level = newlevel;
            MaxSpeed = newSpeed;
            maxDefense = newDefense;
            characterName = newName;

            health = maxHealth;
            speed = MaxSpeed;
            defense = maxDefense;
        }

        bool AddAbility(int numAbility, const Ability& ability){
            if(numAbility > 4 || numAbility < 1)
                return false;

            if(numAbility == 1){
                 ability1 = Ability(ability);
                return true;
            }
            if (numAbility == 2){
                ability2 = Ability(ability);
                return true;
            }
            if (numAbility == 3){
                ability3 = Ability(ability);
                return true;
            }
            if (numAbility == 4){
                ability4 = Ability(ability);
                return true;
            }


            return false;
        }

        int UseAbility(int numAbility){
            if(numAbility > 4 || numAbility < 1)
                return 0;

            if(numAbility == 1){
                return UseAbilityHelper(ability1);
            }
            if (numAbility == 2)
            {
                return UseAbilityHelper(ability2);
            }
            if (numAbility == 3)
            {
                return UseAbilityHelper(ability3);
            }
            if (numAbility == 4)
            {
                return UseAbilityHelper(ability4);
            }

            return -1;
        }

        int UseAbilityHelper(Ability ability){
            if(ability.LowerUses())
                return ability.GetPower();
            else
                return 0;
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


        String testABC(){
            return ability1.GetAbilityName();
        }

        
};

#endif