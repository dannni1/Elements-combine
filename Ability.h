#include <string>

#ifndef ABILITY_H
#define ABILITY_H

using String = std::string;

/* Ability object.
    simple object that hold the characters or monsters abilitys
*/
class Ability{
    private:
    //TO DO: need to add elements to the ability
    String abilityName;
    int numOfUses, power;
    //bool canUseAbility; not necessarily

    public:
        //empty constructor
        Ability(){
            numOfUses = 0;
            power = 0;
        }

        Ability(int newNumOfUses, int newPower, const String& newName){
            numOfUses = newNumOfUses;
            power = newPower;
            abilityName = newName;
        }

        //copy constructor 
        Ability(const  Ability& otherAbility) : numOfUses(otherAbility.numOfUses), power(otherAbility.power)
                                                ,abilityName(otherAbility.abilityName) {}


        //check and lowers if you have any uses left
        bool LowerUses (){
            if(numOfUses > 0){
                numOfUses--;
                return true;
            }
            return false;
        }
         //overload check and lowers by a number 
        bool LowerUses (int num){
            if(numOfUses - num >= 0){
                numOfUses -= num;
                return true;
            }
            else
                return false;
        }

        //simple attribute returns 
        int GetPower(){
            return power;
        }
        int GetUseNumber(){
            return numOfUses;
        }
        String GetAbilityName(){
            return abilityName;
        }
        bool IsEmpty() const{
            if(abilityName.empty() && numOfUses != 0)
                return true;
            return false;
        }

};

#endif