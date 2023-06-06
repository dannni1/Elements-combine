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
    bool LoadBackgrowndTexture(const std::string& folderPath, sf::Texture& bgTexture){
        for(const auto& entry : std::filesystem::directory_iterator(folderPath)){
            if(entry.is_regular_file()){
                if(bgTexture.loadFromFile(entry.path().string())){
                    return true;
                } else{
                    std::cout << "fail to load: " << entry.path() << std::endl;
                }
            } else{
                std::cout << "fail to load: " << entry.path() << std::endl;
            }
        }
        return false;
    }

    bool LoadLeaderTexture(const std::string& folderPath, sf::Texture& LeaderTexture){
        for(const auto& entry : std::filesystem::directory_iterator(folderPath)){
            if(entry.is_regular_file()){
                if(LeaderTexture.loadFromFile(entry.path().string())){
                    return true;
                } else{
                    std::cout << "fail to load: " << entry.path() << std::endl;
                }
            } else{
                std::cout << "fail to load: " << entry.path() << std::endl;
            }
        }
        return false;
    }

    //load all the monster images (for now)
    bool LoadMonsterTexture(const std::string& folderPath, std::vector<sf::Texture>& monstersTexture){
        bool fullLoad = true;

        for(const auto& entry : std::filesystem::directory_iterator(folderPath)){
            if(entry.is_regular_file()){
                sf::Texture texture;

                if(texture.loadFromFile(entry.path().string())){
                    monstersTexture.push_back(texture);
                } else{
                    std::cout << "fail to load: " << entry.path() << std::endl;
                    fullLoad = false;
                }
                
            } else{
                std::cout << "fail to load: " << entry.path() << std::endl;
                fullLoad = false;
            }
        }
        return fullLoad;
    }

    //load all the characters images (for now)
    bool LoadCharacterTexture(const std::string& folderPath, std::vector<sf::Texture>& charactersTexture){
        bool fullLoad = true;

        for(const auto& entry : std::filesystem::directory_iterator(folderPath)){
            if(entry.is_regular_file()){
                sf::Texture texture;

                if(texture.loadFromFile(entry.path().string())){
                    charactersTexture.push_back(texture);
                } else{
                    std::cout << "fail to load: " << entry.path() << std::endl;
                    fullLoad = false;
                }

            } else{
                std::cout << "fail to load: " << entry.path() << std::endl;
                fullLoad = false;
            }
        }
        return fullLoad;
    }


    

    //find the file and load it to json
    nlohmann::json LoadFileJson(const std::string& fileName){
    std::ifstream readFile(fileName);
    if(readFile){
        nlohmann::json data;
        readFile >> data;
        readFile.close();

        return data;
    }   

    std::cout << "fail to load: " << fileName << std::endl;
    return nlohmann::json(); //on fail retun empty  
    }

    //create character and load it form file
    Character LoadCharacter(const std::string& folderPathChracter){
    //call file load
    nlohmann::json jsonFile = LoadFileJson(folderPathChracter);

    if(!jsonFile.empty()){
        Character loadedCharacter = Character(jsonFile["name"], jsonFile["health"], jsonFile["defense"],
                                    jsonFile["experience"], jsonFile["level"]);
    std::cout << "the character: " << jsonFile["name"] << " loaded successfuly.\n";
    return loadedCharacter;
    }

    return Character(); //on fail retun empty  
    }

    //overload create lvl 1 character and load it form file with abilitys
    Character LoadCharacter(const std::string& folderPathChracter, const std::string& folderPathAbility){
    //call file load
    nlohmann::json jsonFileCharacter = LoadFileJson(folderPathChracter);
    nlohmann::json jsonFileAbility = LoadFileJson(folderPathAbility);
    
    if(jsonFileCharacter.empty() || jsonFileAbility.empty())
        return Character();//on fail retun empty  

    Ability ability1(jsonFileAbility["1"]["uses"], jsonFileAbility["1"]["power"], jsonFileAbility["1"]["name"]);
    Ability ability2(jsonFileAbility["2"]["uses"], jsonFileAbility["2"]["power"], jsonFileAbility["2"]["name"]);

    Ability ability3;
    Ability ability4;

    Character loadedCharacter = Character(jsonFileCharacter["name"], jsonFileCharacter["health"], jsonFileCharacter["defense"],
                                jsonFileCharacter["experience"], jsonFileCharacter["level"], ability1, ability2, ability3, ability4);
    std::cout << "the character: " << jsonFileCharacter["name"] << " loaded successfuly.\n";
    return loadedCharacter;
}
//end of privete


public:
    //load all the images from the images folder. give back a vector of the multi  load. 
    void LoadTexureFromFolder(const std::string& folderPath, std::vector<sf::Texture>& monstersTexture, std::vector<sf::Texture>& charactersTexture,
                            sf::Texture& bgTexture, sf::Texture& leaderTexture){

    std::string bgPath = folderPath + "Levels/";
    if(LoadBackgrowndTexture(bgPath, bgTexture))
        std::cout << "the background texture loaded successfully.\n";
    else   
        std::cout << "the background texture faild to load.\n";

    std::string leaderPath = folderPath + "Leader/";
    if(LoadLeaderTexture(leaderPath, leaderTexture))
        std::cout << "the Leader character texture loaded successfully.\n";
    else   
        std::cout << "the Leader character texture faild to load.\n";
        
    std::string monsterPath = folderPath + "Monsters/";
    if(LoadMonsterTexture(monsterPath, monstersTexture))
        std::cout << "the monster texture loaded successfully.\n";
    else   
        std::cout << "the monster texture faild to load.\n";

    std::string characterPath = folderPath + "Characters/";
    if(LoadCharacterTexture(characterPath, charactersTexture))
        std::cout << "the characters  texture loaded successfully.\n";
    else   
        std::cout << "the characters texture faild to load.\n";
    }

    //give character no abilitys
    Character LoadChracterFromFolder(const std::string& folderPathChracter){
        Character character = LoadCharacter(folderPathChracter);
        return character;
    }

    //overload character with abilitys
    Character LoadChracterFromFolder(const std::string& folderPathChracter, const std::string& folderPathAbility){
        Character character = LoadCharacter(folderPathChracter, folderPathAbility);
        return character;
    }
};
#endif