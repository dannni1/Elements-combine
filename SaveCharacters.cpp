#include <iostream>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>//need to have json package 

using namespace std;
using json = nlohmann::json;


//test for vaild inputs
void CheckIfValid(int miniValidNum,int& attribute){
    cin >> attribute; 
    while (!(attribute >= miniValidNum))
    {
        cout << "Plese enter valid number\n";
        cin >> attribute;
    }
}

//create josn file save file as chacracter name
void writeJsonToFile(const json& jsonFile, const string& nameFile){
    ofstream fileToSave(nameFile);
    if(fileToSave){
        fileToSave << jsonFile.dump(0);
        fileToSave.close();
        cout << "JSON file have been saved";
    }
    else
        cout << "exception fail to open file.";

}

int main(){

    //get all the character stats
    string characterName;
    cout << "Creating new character\n";
    cout << "Enter a name\n";
    cin >> characterName;
    while (characterName.empty())
    {
        cout << "Plese enter valid name\n";
        cin >> characterName;
    }
    
    int characterrHealth = 0;
    cout << "Enter character health\n";
    CheckIfValid(1, characterrHealth);

    int characterrSpeed = 0;
    cout << "Enter character speed\n";
    CheckIfValid(0, characterrSpeed);

    int characterrDefense = 0;
    cout << "Enter character Defense\n";
    CheckIfValid(0, characterrDefense);

    int characterrLevel= 0;
    cout << "Enter character Level\n";
    CheckIfValid(1, characterrDefense);

    int characterrExperience = 0; //need to chack if exp is valid
    cout << "Enter character Experience\n";
    CheckIfValid(0, characterrExperience);


    //Serialize to json 
    json characterJson = {
        {"name", characterName},
        {"health", characterrHealth},
        {"speed", characterrSpeed},
        {"defense", characterrDefense},
        {"level", characterrLevel},
        {"experince", characterrExperience},
    };

    string fileName = characterName + ".json";
    //cout << fileName << endl; for testing 
    writeJsonToFile(characterJson, fileName);



    return 0;
}


