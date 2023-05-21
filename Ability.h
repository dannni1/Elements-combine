#include <string>

#ifndef ABILITY_H
#define ABILITY_H

using String = std::string;

class Ability{
    private:
    //TO DO: need to add elements to the ability
    String abilityName;
    int numOfUses, power;
    //bool canUseAbility; not necessarily

    public:
        Ability(){
            numOfUses = 0;
            power = 0;
            abilityName = "null";
        }

        Ability(int newNumOfUses, int newPower, const String& newName){
            numOfUses = newNumOfUses;
            power = newPower;
            abilityName = newName;
        }

        Ability(const  Ability& otherAbility) : numOfUses(otherAbility.numOfUses), power(otherAbility.power)
                                                ,abilityName(otherAbility.abilityName) {}


        int GetPower(){
            return power;
        }
        int GetUseNumber(){
            return numOfUses;
        }
        String GetAbilityName(){
            return abilityName;
        }
        bool LowerUses (){
            if(numOfUses > 0){
                numOfUses--;
                return true;
            }
            else
                return false;
        }
        bool LowerUses (int num){
            if(numOfUses - num >= 0){
                numOfUses -= num;
                return true;
            }
            else
                return false;
        }
};

#endif