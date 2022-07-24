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

        void set_defense(int input_defense){
        defense = input_defense;

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


void use_potion();
void confirm_armor_equip(int class_selection);
void confirm_weapon_equip(int class_selection);
void place_weapon_in_room(int user_class, int room_count);
void place_armor_in_room(int user_class, int room_count);
void ready_player_one(int class_choice);
void display_equipment(int class_selection);

Player player_one;
Inventory player_backpack;

int main(){
    int get_class_decision = class_choice();
    ready_player_one(get_class_decision);
    use_potion();
    confirm_armor_equip(get_class_decision);
    confirm_weapon_equip(get_class_decision);
    display_equipment(get_class_decision);


    return 0;
}
// INVENTORY HELPER FUNCTIONS

void use_potion(){

    if(player_backpack.potions >= 1){
    cout << "\n\n";
    cout << "10 Health added." << endl;;
    //inventory object potions -= 1
    player_backpack.potions -= 1;
    int top_up = player_one.get_health() + 10;
    player_one.set_health(top_up);
    cout << "You now have " << player_one.get_health() << " HP." << endl;
    cout << "There are " << player_backpack.potions << " potions remaining." << endl;}
    else{
        cout << "\n\n";
        cout << "Sorry. No more potions.";}

    
};

void confirm_armor_equip(int class_selection){
    if(class_selection == 1)
    {   cout << "\n\n";
        cout << "Shield Equipped!" << endl;
        player_backpack.armor_equipped = true;
        int new_defense = player_one.get_defense() + 30;
        player_one.set_defense(new_defense);
        cout << "Your defense has now raised to " << player_one.get_defense() << endl;}
    //inventory object shield_equipped = true
    else if(class_selection == 2)
    {   cout << "\n\n";
        cout << "A forcefield envelopes you. You feel stronger." << endl;
        player_backpack.armor_equipped = true;
        int new_defense = player_one.get_defense() + 25;
        player_one.set_defense(new_defense);
        cout << "Your defense has now raised to " << player_one.get_defense() << endl;}

    else if(class_selection == 3)
    {    cout << "\n\n";
         cout << "Leather cowl equipped." << endl;
         player_backpack.armor_equipped = true;
         int new_defense = player_one.get_defense() + 20;
         player_one.set_defense(new_defense);
         cout << "Your defense has now raised to " << player_one.get_defense() << endl;}
    
    
    
};


void confirm_weapon_equip(int class_selection){
    if(class_selection == 1)
    {   cout << "\n\n";
        cout << "Sword equipped! Slay them all." << endl;
    int new_attack = player_one.get_strength() + 10;
    player_one.set_strength(new_attack);
    cout << "Your attack has now raised to " << player_one.get_strength() << endl;
    player_backpack.weapon_equipped = true;}

    else if (class_selection == 2)
    { cout << "\n\n";
      cout << "Spellbook acquired! Time to turn up the heat." << endl;
      int new_attack = player_one.get_spellpower() + 50;
      player_one.set_spellpower(new_attack);
      cout << "Your attack has now raised to " << player_one.get_spellpower() << endl;
      player_backpack.weapon_equipped = true;}


    else if(class_selection == 3)
      {
      cout << "\n\n";
      cout << "Daggers Equipped! Strike swiftly and may the shadows be your guide." << endl;
      int new_attack = player_one.get_strength() + 10;
      player_one.set_strength(new_attack);
      cout << "Your attack has now raised to " << player_one.get_strength() << endl;
      player_backpack.weapon_equipped = true;}
    

};

void place_weapon_in_room(int user_class, int room_count){
    if (room_count == 4){
    string user_decision;
    cout << "\n\n";
    cout << "You notice there is a powerful object on the ground. Pick it up?" << endl;
    cout << "Yes    No" << endl;
    cin >> user_decision;
    if(user_decision == "Yes" || user_decision =="yes")
    {confirm_weapon_equip(user_class);}}
    else if (!(user_class == 1 || user_class == 2 || user_class == 3))
    {cout << "You can't pick it up!" << endl;} 

};

void place_armor_in_room(int user_class, int room_count){
    if(room_count == 2){
    string user_decision;
    cout << "\n\n";
    cout << "You notice there is a durable object on the ground. Pick it up?" << endl;
    cout << "Yes    No" << endl;
    cin >> user_decision;
    if(user_decision == "Yes" || user_decision == "yes")
    {confirm_armor_equip(user_class);}}
    else if (!(user_class == 1 || user_class == 2 || user_class == 3))
    {cout << "You can't pick it up!" << endl;} 
};

void display_equipment(int class_selection){
    cout << "\n\n";
    cout << "Inventory:" << endl;
    if(player_backpack.potions >= 1)
    cout << player_backpack.potions << " potions." << endl;

    if(class_selection == 1 && player_backpack.weapon_equipped && player_backpack.armor_equipped)
    {cout << "Sword." << endl;
     cout << "Shield." << endl;}
    else if (class_selection == 2 && player_backpack.weapon_equipped && player_backpack.armor_equipped)
    {cout << "Spellbook." << endl;
     cout << "Arcane Armor." << endl;}
    else if (class_selection == 3 && player_backpack.weapon_equipped && player_backpack.armor_equipped)
    {cout << "Daggers." << endl;
     cout << "Leather Cowl." << endl;}

    else if(class_selection == 1 && player_backpack.weapon_equipped)
    {cout << "Sword." << endl;}
    else if(class_selection == 2 && player_backpack.weapon_equipped)
    {cout << "Spelbook." << endl;}
    else if(class_selection == 3 && player_backpack.weapon_equipped)
    {cout << "Daggers." << endl;}


    else if(class_selection == 1 && player_backpack.armor_equipped)
    {cout << "Shield." << endl;}
    else if(class_selection == 2 && player_backpack.armor_equipped)
    {cout << "Arcane Armor." << endl;}
    else if(class_selection == 3 && player_backpack.armor_equipped)
    {cout << "Leather Cowl." << endl;}
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