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
    int maxHealth, experience, level, MaxSpeed, maxDefense;
    int health, speed, defense;
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
            MaxSpeed = 0;
            maxDefense = 0;
            characterName = "undefined";

            health = maxHealth;
            speed = MaxSpeed;
            defense = maxDefense;
        }

        Character(const String& newName, int newHealth, int newSpeed, int newDefense, int newexperience, int newlevel){
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

        //constractor with abilitys, can get empty Ability class.
         Character(const String& newName, int newHealth, int newSpeed, int newDefense, int newexperience, int newlevel,
                    const Ability& newability1, const Ability& newability2, const Ability& newability3, const Ability& newability4){
            maxHealth = newHealth;
            experience = newexperience;
            level = newlevel;
            MaxSpeed = newSpeed;
            maxDefense = newDefense;
            characterName = newName;

            health = maxHealth;
            speed = MaxSpeed;
            defense = maxDefense;


            //cheack if the anilitys are valid
            if(newability1.IsEmpty()){
                ability1 = Ability(newability1);
            }
            if(newability2.IsEmpty()){
                ability2 = Ability(newability2);
            }
            if(newability3.IsEmpty()){
                ability3 = Ability(newability3);
            }
            if(newability4.IsEmpty()){
                ability4 = Ability(newability4);
            }
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
        int GetSpeed(){
            return speed;
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


        String testABC(){
            return ability1.GetAbilityName();
        }

        
};

#endif