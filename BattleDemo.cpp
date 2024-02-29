#include <iostream>
#include <string>

#include "Ability.h"
#include "Character.h"
#include "Monster.h"


using namespace std;

int main(){

    int hp = 10;
    int speed1 = 5; //speed is not implement 
    int speed2 = 4;
    int speed3 = 6;
    int numOfUses = 3;
    int anilitypower1 = 4;
    int anilitypower2 = 2;
    bool temp;

    Character A = Character(hp ,0 ,0 ,speed1 ,0 ,"A"); //chacter A
    Character B = Character(hp ,0 ,0 ,speed2 ,0 ,"B"); //chacter B
    Character C = Character(hp ,0 ,0 ,speed3 ,0 ,"C"); //chacter C

    Monster X = Monster(hp + 20 ,0 ,0 ,1 ,0 ,"X");//monster X

    Ability Ab1 = Ability(numOfUses, anilitypower1 , "fireball"); //some abilitys
    Ability Ab2 = Ability(numOfUses, anilitypower2 , "iceball");

    temp = A.AddAbility(1, Ab1);//add the abilitys
    temp = A.AddAbility(2, Ab2);
    temp = B.AddAbility(1, Ab1);
    temp = B.AddAbility(2, Ab2);
    temp = C.AddAbility(1, Ab1);
    temp = C.AddAbility(2, Ab2);
    temp = X.AddAbility(1, Ab1);
    temp = X.AddAbility(2, Ab2);

    cout << "YOU ARE BEING ATTATK\n";
    cout << "use your characters to defend your self\n";

    int input;
    while (true)
    {
        if(X.GetHealth() <= 0)
            break;

        cout << "This A turn pick a ability (1 or 2)\n";
        cin >> input;

        if(input == 1){
            int power = A.UseAbility(input);
            if(power != 0){
                cout << "A USE FIREBALL\n";
                X.TakeDamge(power);
            }
            else{
                cout << "A RUN OUT OF USES TURN LOST\n";
            }
        }
        else if(input == 2) {
            int power = A.UseAbility(input);
            if(power != 0){
                cout << "A USE ICEBALL\n";
                X.TakeDamge(power);
            }
            else{
                cout << "A RUN OUT OF USES TURN LOST\n";
            }
        }
        else{
            cout << "good job troll\n";
            break;
        }

        
        cout << "This B turn pick a ability (1 or 2)\n";
        cin >> input;

        if(input == 1){
            int power = A.UseAbility(input);
            if(power != 0){
                cout << "B USE FIREBALL\n";
                X.TakeDamge(power);
            }
            else{
                cout << "B RUN OUT OF USES TURN LOST\n";
            }
        }
        else if(input == 2) {
            int power = A.UseAbility(input);
            if(power != 0){
                cout << "B USE ICEBALL\n";
                X.TakeDamge(power);
            }
            else{
                cout << "B RUN OUT OF USES TURN LOST\n";
            }
        }
        else{
            cout << "good job troll\n";
            break;
        }

        cout << "This C turn pick a ability (1 or 2)\n";
        cin >> input;

        if(input == 1){
            int power = A.UseAbility(input);
            if(power != 0){
                cout << "C USE FIREBALL\n";
                X.TakeDamge(power);
            }
            else{
                cout << "C RUN OUT OF USES TURN LOST\n";
            }
        }
        else if(input == 2) {
            int power = A.UseAbility(input);
            if(power != 0){
                cout << "C USE ICEBALL\n";
                X.TakeDamge(power);
            }
            else{
                cout << "C RUN OUT OF USES TURN LOST\n";
            }
        }
        else{
            cout << "fail\n";
            break;
        }
    }
    
    cout << "GOOD JOB YOU WIN\n";
    cin >> input; //pause

    return 0;
}
