#include <iostream>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp> //need to have json package 
#include <variant>
#include <vector>

#include "Ability.h"
#include "Character.h"
#include "Monster.h"


using namespace std;
using json = nlohmann::json;


//find the file and load it to json
json LoadFile(const string& fileName){
    ifstream readFile(fileName);
    if(readFile){
        json data;
        readFile >> data;
        readFile.close();

        cout << "File Load successfully." << std::endl;
        return data;
    }   

    cout << "Exception fail to open file." << std::endl;
    return json(); //on fail retun empty  
}

//create character and load it form file
Character LoadCharacter(const string& characterName){
    //call file load
    json jsonFile = LoadFile(characterName);

    if(!jsonFile.empty()){
        Character loadedCharacter = Character(jsonFile["name"], jsonFile["health"], jsonFile["speed"], jsonFile["defense"],
                                    jsonFile["level"], jsonFile["experince"]);
    return loadedCharacter;
    }
    cout << "Exception did don't found file named: " << characterName << endl;
    return Character(); //on fail retun empty  
    
}

//Add Abilitys to Character Class
void AddAbilitysToCharacter(const Ability& ability1, const Ability& ability2, Character* character){
    character->AddAbility(1, ability1);
    character->AddAbility(2, ability2);
}

//return Ability Class from json
Ability JsonToAbility(const json& jsonAbility){
    return Ability(jsonAbility["uses"], jsonAbility["power"], jsonAbility["name"]);
}

int PickAbility(){
    cout << "Pick Ability (1 or 2)\n";
    int playerInput;
    cin >> playerInput;

    while (playerInput != 1 && playerInput != 2)
    {
        cout << "invalid input try again\n";
        cin >> playerInput;
    }
    
    return playerInput;
}

//sort vector moster and character takes pointers only
void SortVector(vector<variant<Character*, Monster*>>& m_vector){
    int size = m_vector.size();

    for (int i = 0; i < size; ++i) {

        int smallest = visit([](auto&& arg){//chack for what type is the object and returns the speed
            return arg->GetSpeed();
        }, m_vector[i]);

        for(int j = i + 1; j < size; ++j){

            int temp = visit([](auto&& arg){
            return arg->GetSpeed();
        }, m_vector[j]);

        if(temp > smallest){
            swap(m_vector[i], m_vector[j]);
            smallest = temp;
        }}  
    }
}



int main(){

    //TO DO: load characters with abilitys
    //load 3 characters
    Character A = LoadCharacter("A.json");
    Character B = LoadCharacter("B.json");
    Character C = LoadCharacter("C.json");

    //TEMP CODE, will move to a file later on 
    //some unique abilitys
    json ability1 = {
        {"name", "fireball"},
        {"power", 40},
        {"uses", 4},
    };

     json ability2 = {
        {"name", "firelance"},
        {"power", 60},
        {"uses", 1},
    };

    json ability3 = {
        {"name", "iceball"},
        {"power",  25},
        {"uses",  8},
    };

    json ability4 = {
        {"name", "freeze"},
        {"power",  10},
        {"uses",  1},
    };

    json ability5 = {
        {"name", "zap"},
        {"power",  15},
        {"uses",  15},
    };

    json ability6 = {
        {"name", "lightning"},
        {"power",  80},
        {"uses",  1},
    };

    //add the abilitys to characters
    AddAbilitysToCharacter(JsonToAbility(ability1), JsonToAbility(ability2), &A);
    AddAbilitysToCharacter(JsonToAbility(ability3), JsonToAbility(ability4), &B);
    AddAbilitysToCharacter(JsonToAbility(ability5), JsonToAbility(ability6), &C);

    //monster
    Monster X = Monster(250,0,0,2,10,"DOG");

    /* tests
    cout << A.GetName() << endl;
    cout << B.GetName() << endl;
    cout << C.GetName() << endl;

    cout << A.testABC() << endl;
    cout << B.testABC() << endl;
    cout << C.testABC() << endl;
    */


    cout << "YOU ARE BEING ATTATK\n";
    cout << "use your characters to defend your self\n";


    //a way to store and sort objects 
    vector<variant<Character*, Monster*>> turnOrder; //pointer vector (no memory is stored)
    turnOrder.push_back(&A);
    turnOrder.push_back(&B);
    turnOrder.push_back(&C);
    turnOrder.push_back(&X);

    SortVector(turnOrder);//hell

    int turn = 0;
     while (true)
    {

        if(X.GetHealth() <= 0)
            break;

        String name = visit([](auto&& arg){
            return arg->GetName();
        }, turnOrder[turn]);


        if(holds_alternative<Monster*>(turnOrder[turn])){//cheack if its a Monster or character
            cout << "Monster: " << name << " is atking you!!\n";
        }else{
            cout << "This: " << name << " turn\n";

            int power = get<Character*>(turnOrder[turn])->UseAbility(PickAbility());//in short, use character ability 
            //cout << power << "test" << endl;

            if(power != 0){
                X.TakeDamge(power);
                cout << "you hit the Monster! with: " <<  power << " power\n";
            } else{
                cout << "you OUT of uses, turn lost.\n";
            }  
        }

        ++turn;
        if(turn >= turnOrder.size())
            turn = 0;
    }
    
    cout << "GOOD JOB YOU WIN\n";
    return 0;
}


