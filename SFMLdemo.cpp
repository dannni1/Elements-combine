#include <SFML/Graphics.hpp> //need SFML package
#include <filesystem>
#include <iostream>
#include <vector>
#include <string>



class Load
{
private:
    bool LoadBackgrownd(const std::string& folderPath, sf::Texture& bgTexture){
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

    bool LoadLeader(const std::string& folderPath, sf::Texture& LeaderTexture){
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
    bool LoadMonster(const std::string& folderPath, std::vector<sf::Texture>& monstersTexture){
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
    bool LoadCharacter(const std::string& folderPath, std::vector<sf::Texture>& charactersTexture){
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
//end of privete


public:
    //load all the images from the images folder. give back a vector of the multi  load. 
    void LoadTexureFromFolder(const std::string& folderPath, std::vector<sf::Texture>& monstersTexture, std::vector<sf::Texture>& charactersTexture,
                            sf::Texture& bgTexture, sf::Texture& leaderTexture){

    std::string bgPath = folderPath + "Levels/";
    if(LoadBackgrownd(bgPath, bgTexture))
        std::cout << "the background loaded successfully.\n";
    else   
        std::cout << "the background faild to load.\n";

    std::string leaderPath = folderPath + "Leader/";
    if(LoadLeader(leaderPath, leaderTexture))
        std::cout << "the Leader character loaded successfully.\n";
    else   
        std::cout << "the Leader character faild to load.\n";
        
    std::string monsterPath = folderPath + "Monsters/";
    if(LoadMonster(monsterPath, monstersTexture))
        std::cout << "the monster loaded successfully.\n";
    else   
        std::cout << "the monster faild to load.\n";

    std::string characterPath = folderPath + "Characters/";
    if(LoadCharacter(characterPath, charactersTexture))
        std::cout << "the characters loaded successfully.\n";
    else   
        std::cout << "the characters faild to load.\n";
    }
};

std::vector<sf::Sprite> TextureVector_To_SpiteVector(const std::vector<sf::Texture>& textureVector){
    std::vector<sf::Sprite> spriteVector;

    for (int i = 0; i < textureVector.size(); ++i)
    {
        sf::Sprite sprite;
        sprite.setTexture(textureVector[i]);
        spriteVector.push_back(sprite);
    }

    return spriteVector;
}









int main()
{
    // Create the window
    sf::RenderWindow window(sf::VideoMode(1200, 700), "Demo");

    std::string folderPath ="images/";

    std::vector<sf::Texture> monsterTexture;
    std::vector<sf::Texture> characterTexture;
    sf::Texture bgTexture;
    sf::Texture leaderTexture;


    //using class to a void unwant method calls
    Load load;
    load.LoadTexureFromFolder(folderPath, monsterTexture, characterTexture, bgTexture, leaderTexture); 


    std::vector<sf::Sprite> monsterSprite(TextureVector_To_SpiteVector(monsterTexture));
    std::vector<sf::Sprite> characterSprite(TextureVector_To_SpiteVector(characterTexture));
    sf::Sprite bgSprite;
    bgSprite.setTexture(bgTexture);
    sf::Sprite leaderSprite;
    leaderSprite.setTexture(leaderTexture);
    
    // Main loop
    while (window.isOpen())
    {


        // Process events
        sf::Event event;
        while (window.pollEvent(event)) //must be a loop
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    

        //clear the window
        window.clear();

        //draw on the window 
        window.draw(bgSprite);
        window.draw(leaderSprite);

        for (const auto& sprite : monsterSprite)
        {
            window.draw(sprite);
        }

        for (const auto& sprite : characterSprite)
        {
            window.draw(sprite);
        }

        //display the window
        window.display();
    }

    return 0;
}//end of main