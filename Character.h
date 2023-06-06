#include <string>
#include "Ability.h" //use objcet Ability

#ifndef CHARACTER_H
#define CHARACTER_H

using String = std::string;

/* Character object, uses Ability object to work.
    simple object responsible to create new character.
*/
class Character {
    //TO DO: need to add special defense 
    private:
    int maxHealth, experience, level, maxDefense;
    int health, defense;
    String characterName;

    Ability ability1;
    Ability ability2;
    Ability ability3;
    Ability ability4;

    public:
        //Empty constractor
        Character(){
            maxHealth = 0;
            experience = 0;
            level = 0;
            maxDefense = 0;
            characterName = "undefined";

            health = maxHealth;
            defense = maxDefense;
        }

        Character(const String& newName, int newHealth, int newDefense, int newexperience, int newlevel)
        : maxHealth(newHealth), experience(newexperience), level(newlevel), maxDefense(newDefense), characterName(newName)
        {
            health = maxHealth;
            defense = maxDefense;
        }

        //constractor with abilitys, can get empty Ability class.
         Character(const String& newName, int newHealth, int newDefense, int newexperience, int newlevel,
                    const Ability& newability1, const Ability& newability2, const Ability& newability3, const Ability& newability4)
        : maxHealth(newHealth), experience(newexperience), level(newlevel), maxDefense(newDefense), characterName(newName),
        ability1(newability1), ability2(newability2), ability3(newability3), ability4(newability4)
        {

            health = maxHealth;
            defense = maxDefense;
        }


        //change the old ability to a new one
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

            return -1;//on fail rerun -1
        }

        //chack if uses left and return the ability power
        int UseAbilityHelper(Ability ability){
            if(ability.LowerUses())
                return ability.GetPower();

            return 0;
        }

        //simple attribute returns
        int GetHealth(){
            return health;
        }
        int GetDefense(){
            return defense;
        }
        int GetExperience(){
            return experience;
        }
        int GetLevel(){
            return level;
        }
        String GetName(){
            return characterName;
        }

        String GetAbilityName(int abilityNumber){
            switch (abilityNumber)
            {
            case 1:
                return ability1.GetAbilityName();
                break;
            case 2:
                return ability2.GetAbilityName();
                break;
            case 3:
                return ability3.GetAbilityName();
                break;
            case 4:
                return ability4.GetAbilityName();
                break;
            
            default:
                return "";
                break;
            }
        }

        
};

#endif