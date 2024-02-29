#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp> //need SFML package
#include <string>

#include "Ability.h"


/* Character object, uses Ability object to work.
    simple object responsible to create new character.
*/
class Character {
    //TO DO: need to add special defense 
    private:
    int c_maxHealth, c_experience, c_level, c_maxDefense; //c for class
    int c_health, c_defense;
    bool c_playable; 
    std::string c_characterName;

    Ability c_ability1;
    Ability c_ability2;
    Ability c_ability3;
    Ability c_ability4;

    
    sf::Texture c_characterTexture;
    sf::Sprite* c_character_ptrSprite;

    //chack if uses left and return the ability power
    int UseAbilityHelper(Ability ability){
        if(ability.LowerUses())
            return ability.GetPower();

        return 0;
    }

    public:
        //Empty constractor
        Character(){
            c_maxHealth = -1;
            c_experience = -1;
            c_level = -1;
            c_maxDefense = -1;
            c_characterName = "";

            c_health = c_maxHealth;
            c_defense = c_maxDefense;
        }

        //constractor 
        Character(const std::string& newName, int newHealth, int newDefense, int newexperience, int newlevel)
        : c_maxHealth(newHealth), c_experience(newexperience), c_level(newlevel), c_maxDefense(newDefense), c_characterName(newName)
        {
            c_health = c_maxHealth;
            c_defense = c_maxDefense;
        }

        //constractor with abilitys, can get empty Ability class.
        Character(const std::string& newName, int newHealth, int newDefense, int newexperience, int newlevel,
                    const Ability& newability1, const Ability& newability2, const Ability& newability3, const Ability& newability4)
        : c_maxHealth(newHealth), c_experience(newexperience), c_level(newlevel), c_maxDefense(newDefense), c_characterName(newName),
        c_ability1(newability1), c_ability2(newability2), c_ability3(newability3), c_ability4(newability4)
        {

            c_health = c_maxHealth;
            c_defense = c_maxDefense;
        }

        //constractor with abilitys and pointers to texture & Sprite
        Character(const std::string& newName, int newHealth, int newDefense, int newexperience, int newlevel,
                    const Ability& newability1, const Ability& newability2, const Ability& newability3, const Ability& newability4,
                    sf::Texture& newcharacterTexture)
        : c_maxHealth(newHealth), c_experience(newexperience), c_level(newlevel), c_maxDefense(newDefense), c_characterName(newName),
        c_ability1(newability1), c_ability2(newability2), c_ability3(newability3), c_ability4(newability4),
        c_characterTexture(newcharacterTexture)
        {

            c_health = c_maxHealth;
            c_defense = c_maxDefense;
        }


        ~Character(){}


        //change the old ability to a new one
        bool AddAbility(int numAbility, const Ability& ability){
            if(numAbility > 4 || numAbility < 1)
                return false;
            if(numAbility == 1){
                c_ability1 = Ability(ability);
                return true;
            }
            if (numAbility == 2){
                c_ability2 = Ability(ability);
                return true;
            }
            if (numAbility == 3){
                c_ability3 = Ability(ability);
                return true;
            }
            if (numAbility == 4){
                c_ability4 = Ability(ability);
                return true;
            }


            return false;
        }
        
        int UseAbility(int numAbility){
            if(numAbility > 4 || numAbility < 1)
                return 0;

            if(numAbility == 1){
                return UseAbilityHelper(c_ability3);
            }
            if (numAbility == 2)
            {
                return UseAbilityHelper(c_ability2);
            }
            if (numAbility == 3)
            {
                return UseAbilityHelper(c_ability3);
            }
            if (numAbility == 4)
            {
                return UseAbilityHelper(c_ability4);
            }

            return -1;//on fail rerun -1
        }

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
        int GetExperience() const{
            return c_experience;
        }
        int GetLevel() const{
            return c_level;
        }
        std::string GetName() const{
            return c_characterName;
        }
        bool GetPlayable() const{
            return c_playable;
        }
        //give a pointer to character texture
        sf::Texture* GetTexture_ptr() {
            sf::Texture* ptr = &c_characterTexture;
            return ptr;
        }
        //give the character sprite pointer
        sf::Sprite* GetSprite_ptr() const{
            return c_character_ptrSprite;
        }
        //give the name of ability 1 to 4
        std::string GetAbilityName(const int abilityNumber) const{
            switch (abilityNumber)
            {
            case 1:
                return c_ability1.GetAbilityName();
                break;
            case 2:
                return c_ability2.GetAbilityName();
                break;
            case 3:
                return c_ability3.GetAbilityName();
                break;
            case 4:
                return c_ability4.GetAbilityName();
                break;
            
            default:
                return "";
                break;
            }
        }



        //simple set attribute
        void SetHealth(int newHealth) {
            c_health = newHealth;
        }
        void SetDefense(int newDefense) {
             c_defense = newDefense;
        }
        void SetExperience(int newExperience) {
            c_experience = newExperience;
        }
        void SetLevel(int newLevel) {
            c_level = newLevel;
        }
        void SetName(const std::string& newName) {
            c_characterName.assign(newName);
        }
        void SetPlayable(const bool newTurn){
            c_playable = newTurn;
        }
        /*void SetTexture(const sf::Texture newTexture) {
            c_characterTexture = std::move(sf::Texture(newTexture));;
        } ------------------- TOO EXPESIVE (bad for gpu)------------------------
        */
        void SetSprite_prt(sf::Sprite* newSprite_ptr) {
            c_character_ptrSprite = newSprite_ptr;
        }

        void Played(){
            c_playable = false;
        }
        void Playable(){
            c_playable = true;
        }
        
};

#endif