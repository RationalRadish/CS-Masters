#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef struct Inventory{
int potions = 4;
bool armor_equipped = false;
bool weapon_equipped = false;

} Inventory;


class Player
/* Purpose: Boilerplate class for all players in the game. 
   Returns: Object instace of class Player.
NOTES FOR FUTURE    class keeps track of player location. The room and map objects are only called for navigation. 
                    class keeps track of player dead/alive status. It will be called in the Battle Function, but the scope of battle is to only give command for battle.
                    Int Location keeps track of player in terms of the map for Vector traversal. String location is what is shown to the user.
TODO extend Player into 3 subclasses security officer, command officer, and enemy.
       These subclasses will inherit base traits and attributes of player (Are you alive, what your name, what's your location)
       Also will add in traits for battle based on subclass. Specifics are below -- 
       command officer will have more strength and less dexterity. 
       security officer will have less strength but more dexterity.
       Each subclass also has potion method that allows them to restore health.
REFERENCETHIS C++ For Absolute Beginners Pg 201 
*/ 
{

    private:
       /* base stats*/
        int health = 100;  
        int strength = 10;
        int spellpower = 0;
        int defense = 10;
        int dexterity = 5;
        int int_location = 0;
        string string_location = "";
        string name = "";
        string player_decision = "";

    public:
    
       
        //self
        string get_name(){
            return name;
        }

        void set_name(string input_name){
            name = input_name;

        }
        
        //health
        
        int get_health(){
            return health;

        }
        void set_health(int input_health){
            health = input_health;

        }


        //attack
        int get_strength(){
            return strength;

        }

        void set_strength(int input_strength){
            strength = input_strength;
        }

        int get_spellpower(){
            return spellpower;
        }

        void set_spellpower(int input_spellpower){
            spellpower = input_spellpower;
        }


        //defense
        int get_defense(){
            return defense;

        }

        int set_defense(int input_defense){
           return input_defense = defense;

        }

        //dexterity

        int get_dexterity(){
            return dexterity;
        }

        void set_dexterity(int input_dexterity){
            dexterity = input_dexterity;
        }

        //location
        string get_string_location(){

            return string_location;

        }

        int get_int_location(){

            return int_location;

        }

        void set_string_location(int input_location){

            string_location = input_location;
        }

        void set_int_location(int input_location){

            int_location = input_location;
        }

        void display_location(){
            cout << "You are in " << string_location << endl;

        }

        //store last console input decision.

        void set_player_decision(string choice){

            player_decision = choice;
        }

        string get_player_decision(){

            return player_decision;

        }


        //check death. 
        //TODO Will be called at the end of the do while loop that will be in void battle function 

        bool still_alive()
        {

            if  (health > 0) return true;
            else return false;
        }


};

class Enemy: public Player {


};


//Player Helper Functions

template<class T> void show_all_player_stats(T agent){
    cout << "\n\n";
    cout << agent.get_name();
    cout << " has the following stats:" << endl;
    cout << agent.get_health() << " HP" << endl;
    cout << agent.get_strength() << " strength." << endl;
    cout << agent.get_spellpower() << " spellpower." << endl;
    cout << agent.get_defense() << " defense." << endl;
    cout << agent.get_dexterity() << " dexterity." << endl;


};



int class_choice()
{
    int user_class_choice;
    cout << "Please select your class:" << endl;
    cout << "Press 1 for the Warrior." << endl;
    cout << "Press 2 for the Mage." << endl;
    cout << "Press 3 for the Rogue." << endl;
    cout << "To play without upgrades, press any other key." << endl;
    cin >> user_class_choice;

    return user_class_choice;
};



void name_decision();
void ready_player_one(int class_choice);

Player player_one;
vector <Enemy> enemy_forces_assembled(10);


int main(){

    for(int i = 0; i < enemy_forces_assembled.size(); i++) {enemy_forces_assembled[i].set_name("Enemy");};
    name_decision();
    int get_class_decision = class_choice();
    ready_player_one(get_class_decision);
    show_all_player_stats(player_one);
    show_all_player_stats(enemy_forces_assembled[0]);




    return 0;
}

void name_decision(){
    string name;
    cout << "What do you call yourself, noble challenger?" << endl;
    cin >> name;
    player_one.set_name(name);
    cout << "Hello, " << player_one.get_name();
    cout << "\n\n";
};


void ready_player_one(int class_choice) {
    switch(class_choice){
        case 1:
            cout << "\n\n";
            cout << "Warrior chosen!" << endl;
            player_one.set_health(150);
            player_one.set_strength(20);
            break;
        case 2:
            cout << "\n\n";
            cout << "Mage Chosen!" << endl;
            player_one.set_health(40);
            player_one.set_strength(10);
            player_one.set_dexterity(10);
            break;
        case 3:
            cout << "\n\n";
            cout << "Rogue Chosen!" << endl;
            player_one.set_health(80);
            player_one.set_strength(5);
            player_one.set_dexterity(20);
            break;
         

                                }

};