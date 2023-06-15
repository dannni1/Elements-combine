#ifndef LOAD_H
#define LOAD_H

#include <SFML/Graphics.hpp> //need SFML package
#include <nlohmann/json.hpp> //need to have json package 
#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>

#include "Character.h"
#include "Ability.h"

class Load
{
private:
    //find the file and load it to json
    bool LoadFileJson(const std::string& m_fileName, nlohmann::json& m_json){
        std::ifstream readFile(m_fileName);
        if(readFile){
            readFile >> m_json;
            readFile.close();

            return true;
        }   

        std::cout << "fail to load: " << m_fileName << std::endl;
        return false; //on fail  
    }

    //load a texture from file
    bool LoadTextureFromfile(const std::string& m_filePath, sf::Texture& m_texture){
        if(m_texture.loadFromFile(m_filePath)){
            return true;
        }
        
        std::cout << "fail to load Texture: " << m_filePath << std::endl;
        return false;//on fail  
    }

    //create character and load it form file
    Character LoadChracterFromfile(const std::string& m_filePathChracter){
        //call file load
        nlohmann::json m_jsonFile;
        if(!LoadFileJson(m_filePathChracter, m_jsonFile)){
            std::cout << "Fail to load character: " << m_filePathChracter << std::endl;
            return Character();//on fail retun empty 
        }

        if(!m_jsonFile.empty()){
            Character loadedCharacter = Character(m_jsonFile["name"], m_jsonFile["health"], m_jsonFile["defense"],
                                        m_jsonFile["experience"], m_jsonFile["level"]);
        std::cout << "the character: " << m_jsonFile["name"] << " loaded successfuly.\n";
        return loadedCharacter;
        }

        std::cout << "Fail to load character: " << m_filePathChracter << std::endl;
        return Character(); //on fail retun empty  
    }


    //overload load character with abilitys
    Character LoadChracterFromfile(const std::string& m_filePathChracter, const std::string& m_filePathAbility){
        //call file load
        nlohmann::json m_jsonFileCharacter;
        if(!LoadFileJson(m_filePathChracter, m_jsonFileCharacter)){
            std::cout << "Fail to load character: " << m_filePathChracter << std::endl;
            return Character();//on fail retun empty 
        }

        nlohmann::json m_jsonFileAbility;
        if(!LoadFileJson(m_filePathAbility, m_jsonFileAbility)){
            std::cout << "Fail to load character Abilitys: " << m_filePathAbility << std::endl;
            return Character();//on fail retun empty 
        }

        Ability ability1 = m_jsonFileAbility.contains("1") ? Ability(m_jsonFileAbility["1"]["uses"], m_jsonFileAbility["1"]["power"], m_jsonFileAbility["1"]["name"]) :
            Ability();

        Ability ability2 = m_jsonFileAbility.contains("2") ? Ability(m_jsonFileAbility["2"]["uses"], m_jsonFileAbility["2"]["power"], m_jsonFileAbility["2"]["name"]) :
            Ability();
        
        Ability ability3 = m_jsonFileAbility.contains("3") ? Ability(m_jsonFileAbility["3"]["uses"], m_jsonFileAbility["3"]["power"], m_jsonFileAbility["3"]["name"]) :
            Ability();

        Ability ability4 = m_jsonFileAbility.contains("4") ? Ability(m_jsonFileAbility["4"]["uses"], m_jsonFileAbility["4"]["power"], m_jsonFileAbility["4"]["name"]) :
            Ability();

        Character loadedCharacter = Character(m_jsonFileCharacter["name"], m_jsonFileCharacter["health"], m_jsonFileCharacter["defense"],
                                    m_jsonFileCharacter["experience"], m_jsonFileCharacter["level"], ability1, ability2, ability3, ability4);
        std::cout << "the character: " << m_jsonFileCharacter["name"] << " loaded successfuly.\n";
        return loadedCharacter;
    }


    //overload load character with abilitys and textures
    Character LoadChracterFromfile(const std::string& m_filePathChracter, const std::string& m_filePathAbility,
                                const std::string& m_filePathTexture){

        nlohmann::json m_jsonFileCharacter;
        if(!LoadFileJson(m_filePathChracter, m_jsonFileCharacter)){
            std::cout << "Fail to load character: " << m_filePathChracter << std::endl;
            return Character();//on fail retun empty 
        }

        nlohmann::json m_jsonFileAbility;
        if(!LoadFileJson(m_filePathAbility, m_jsonFileAbility)){
            std::cout << "Fail to load character Abilitys: " << m_filePathAbility << std::endl;
            return Character();//on fail retun empty 
        }

        Ability ability1 = m_jsonFileAbility.contains("1") ? Ability(m_jsonFileAbility["1"]["uses"], m_jsonFileAbility["1"]["power"], m_jsonFileAbility["1"]["name"]) :
            Ability();

        Ability ability2 = m_jsonFileAbility.contains("2") ? Ability(m_jsonFileAbility["2"]["uses"], m_jsonFileAbility["2"]["power"], m_jsonFileAbility["2"]["name"]) :
            Ability();
        
        Ability ability3 = m_jsonFileAbility.contains("3") ? Ability(m_jsonFileAbility["3"]["uses"], m_jsonFileAbility["3"]["power"], m_jsonFileAbility["3"]["name"]) :
            Ability();

        Ability ability4 = m_jsonFileAbility.contains("4") ? Ability(m_jsonFileAbility["4"]["uses"], m_jsonFileAbility["4"]["power"], m_jsonFileAbility["4"]["name"]) :
            Ability();

        sf::Texture m_texture;
        if(!LoadTextureFromfile(m_filePathTexture, m_texture)){
            std::cout << "Fail to load character Texture: " << m_filePathTexture << std::endl;
            return Character();//on fail retun empty 
        }

        Character loadedCharacter = Character(m_jsonFileCharacter["name"], m_jsonFileCharacter["health"], m_jsonFileCharacter["defense"],
                                    m_jsonFileCharacter["experience"], m_jsonFileCharacter["level"], ability1, ability2, ability3, ability4, m_texture);

        std::cout << "the character: " << m_jsonFileCharacter["name"] << " loaded successfuly.\n";
        return loadedCharacter;
    }
//end of privete


public:
    sf::Texture LoadTexture(const std::string& m_filePathTexter, sf::Texture& m_texture){
        if(LoadTextureFromfile(m_filePathTexter, m_texture))
            return m_texture;

        return m_texture;//fail
    }

    //give character no abilitys
    Character LoadChracter(const std::string& m_filePathChracter){
        Character character = LoadChracterFromfile(m_filePathChracter);
        return character;
    }

    //overload character with abilitys
    Character LoadChracter(const std::string& m_filePathChracter, const std::string& m_filePathAbility){
        Character character = LoadChracterFromfile(m_filePathChracter, m_filePathAbility);
        return character;
    } 

    //overload character with abilitys and texture 
    Character LoadChracter(const std::string& m_filePathChracter, const std::string& m_filePathAbility,
                                        const std::string& m_filePathTexter){
        Character character = LoadChracterFromfile(m_filePathChracter, m_filePathAbility, m_filePathTexter);
        return character;
    }

};
#endif