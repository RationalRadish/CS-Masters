#include <iostream>
#include <string>
#include <vector>
#include <random>
using namespace std;

typedef struct Inventory{
int potions = 8;
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



void use_potion();
void confirm_armor_equip(int class_selection);
void confirm_weapon_equip(int class_selection);
void place_weapon_in_room(int user_class, int room_count);
void place_armor_in_room(int user_class, int room_count);
void ready_player_one(int class_choice);
void display_equipment(int class_selection);
void combat(vector <Enemy> &enemy_forces, int class_selection);
void help_screen(bool combat_flag, int class_selection, Inventory bag);

Player player_one;
Inventory player_backpack;
vector <Enemy> enemy_forces_assembled(10);
int enemy_kill_counter;


int main(){

    for(int i = 0; i < enemy_forces_assembled.size(); i++) {enemy_forces_assembled[i].set_name("Enemy");};
    int get_class_decision = class_choice();
    ready_player_one(get_class_decision);
    show_all_player_stats(player_one);
    show_all_player_stats(enemy_forces_assembled[0]);
    confirm_armor_equip(get_class_decision);
    confirm_weapon_equip(get_class_decision);
    combat(enemy_forces_assembled, get_class_decision);




    return 0;
}

void combat(vector <Enemy> &enemy_forces, int class_selection)
/* 
FUNCTION EXPLANATION & PSEUDOCODE
Player and Enemy are both global variables. Called in the function.
Make a do while loop for all of this based on the player.is_alive() for both player and enemy.
Both player and enemy health will be called at the start of the loop.
The loop will Pokemon style.
"An enemy has appeared"
Fight   Run
If Fight then start combat. 
    The derived classes of player will have an attack method. Enemy is from player too. 
    Combat Options now will be valid in the parse input class (Flag set to True. Again global variable in the class)
    Attack          Drink Potion
    Depending upon the class, it will expose different attacks which are just different scaled hits
    If the player is dead then, then also game_over. (Game over will be a Global Flag)
Else Run
    Use random library to find if run is successful. 
    Switch statement inside of the else block, based on success we need to break out of everything.
    
     */
{   
    int get_player_location = player_one.get_int_location();
    int player_attack,player_defense;
    bool player_in_combat = true, user_survived_combat = true;
    Enemy *opponent = &enemy_forces.at(get_player_location);
    string battle_console_decision;

    if((*opponent).still_alive())
   { 
    cout << "\n\n";
    cout << "A foe has appeared!" << endl;}

    while((*opponent).still_alive() && player_one.still_alive()){
    cout << "What will you do?" << endl;
    
    if (class_selection == 1 && player_backpack.weapon_equipped)
    cout << "Slash  Potion" << endl;
    else if (class_selection == 2 && player_backpack.weapon_equipped)
    cout << "Fireball   Potion" << endl;
    else if (class_selection == 3 && player_backpack.weapon_equipped)
    cout << "Stab       Potion" << endl;
    else{
    cout << "Punch       Potion" << endl;}

    cin >> battle_console_decision;

    if(battle_console_decision == "Potion" || battle_console_decision == "potion")
    {use_potion(); }

    else if (battle_console_decision == "Fireball" || battle_console_decision == "fireball" 
            || battle_console_decision == "Slash" || battle_console_decision == "slash" 
            || battle_console_decision == "Stab" || battle_console_decision == "stab" 
            || battle_console_decision == "Punch" || battle_console_decision == "punch" )
    {
        
    random_device player_seed;
    mt19937 generate_player_parameters(player_seed());
    uniform_int_distribution<int> player_attack_distribution(12, 12 + player_one.get_dexterity());
    uniform_int_distribution<int> player_defense_distribution(5, floor(player_one.get_defense()/2));
    auto player_attack_stats_scaled = player_attack_distribution(generate_player_parameters);
    auto player_defense_stats_scaled = player_defense_distribution(generate_player_parameters);

    if (class_selection == 2 && player_backpack.weapon_equipped) {
        player_attack = player_one.get_spellpower() + player_attack_stats_scaled;
        player_defense = player_one.get_defense() + player_defense_stats_scaled;}
    else  
    {player_attack = player_one.get_strength() + player_attack_stats_scaled;
     player_defense = player_one.get_defense() + player_defense_stats_scaled;}

    

//build out seperate scales for enemy and player
//fix mage attack when not holding spellbook


    random_device enemy_seed;
    mt19937 generate_enemy_parameters(enemy_seed()); //https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
    uniform_int_distribution<int> enemy_attack_distribution(40, 40 + (*opponent).get_dexterity());
    uniform_int_distribution<int> enemy_defense_distribution(9, 9 + floor((*opponent).get_defense()/2));
    int enemy_attack_stats_scaled = enemy_attack_distribution(generate_enemy_parameters);
    int enemy_defense_stats_scaled = enemy_defense_distribution(generate_enemy_parameters);

    int enemy_attack = (*opponent).get_strength() + enemy_attack_stats_scaled;
    int enemy_defense = (*opponent).get_defense() + enemy_defense_stats_scaled;


    int player_turn_attack_enemy = player_attack - enemy_defense;
    int enemy_turn_attack_player = enemy_attack - player_defense;

    int player_current_health = player_one.get_health() - enemy_turn_attack_player;
    player_one.set_health(player_current_health);
    int enemy_current_health = (*opponent).get_health() - player_turn_attack_enemy;
    (*opponent).set_health(enemy_current_health);
    cout << "\n\n";
    if(player_turn_attack_enemy < 0)
    player_turn_attack_enemy = 0;
    cout << "You attack for " << player_turn_attack_enemy << " damage." << endl;
    if (!(*opponent).still_alive())
    {
      cout << "Enemy defeated!" << endl;
      enemy_kill_counter ++;
      break; }

    cout << "The enemy has " << enemy_current_health << " health remaining." << endl;
    cout << "\n";

    if(enemy_turn_attack_player < 0)
    enemy_turn_attack_player = 0;
    cout << "The enemy attacks you for " << enemy_turn_attack_player << " damage."  << endl;
    cout << "You have " << player_current_health << " health remaining." << endl; \
    cout << "\n\n";}

    else {help_screen(player_in_combat, class_selection, player_backpack);}}

    if (!player_one.still_alive())
    {cout << "Game Over." << endl;
     exit(EXIT_SUCCESS); }

};

void use_potion(){

    if(player_backpack.potions >= 1){
    cout << "\n\n";
    cout << "40 Health added." << endl;;
    //inventory object potions -= 1
    player_backpack.potions -= 1;
    int top_up = player_one.get_health() + 40;
    player_one.set_health(top_up);
    cout << "You now have " << player_one.get_health() << " HP." << endl;
    cout << "There are " << player_backpack.potions << " potions remaining." << endl;
    cout << "\n\n";}
    else{
        cout << "\n\n";
        cout << "Sorry. No more potions.";}

    
};

void confirm_armor_equip(int class_selection){
    if(class_selection == 1)
    {   cout << "\n\n";
        cout << "Shield Equipped!" << endl;
        player_backpack.armor_equipped = true;
        int new_defense = player_one.get_defense() + 20;
        player_one.set_defense(new_defense);
        cout << "Your defense has now raised to " << player_one.get_defense() << "." << endl;}
    //inventory object shield_equipped = true
    else if(class_selection == 2)
    {   cout << "\n\n";
        cout << "A forcefield envelopes you. You feel stronger." << endl;
        player_backpack.armor_equipped = true;
        int new_defense = player_one.get_defense() + 15;
        player_one.set_defense(new_defense);
        cout << "Your defense has now raised to " << player_one.get_defense() << "." << endl;}

    else if(class_selection == 3)
    {    cout << "\n\n";
         cout << "Leather cowl equipped." << endl;
         player_backpack.armor_equipped = true;
         int new_defense = player_one.get_defense() + 8;
         player_one.set_defense(new_defense);
         cout << "Your defense has now raised to " << player_one.get_defense() << "."  << endl;}
    
    
    
};


void confirm_weapon_equip(int class_selection){
    if(class_selection == 1)
    {   cout << "\n\n";
        cout << "Sword equipped! Slay them all." << endl;
    int new_attack = player_one.get_strength() + 10;
    player_one.set_strength(new_attack);
    cout << "Your attack has now raised to " << player_one.get_strength() << "." << endl;
    player_backpack.weapon_equipped = true;}

    else if (class_selection == 2)
    { cout << "\n\n";
      cout << "Spellbook acquired! Time to turn up the heat." << endl;
      int new_attack = player_one.get_spellpower() + 50;
      player_one.set_spellpower(new_attack);
      cout << "Your attack has now raised to " << player_one.get_spellpower() << "." << endl;
      player_backpack.weapon_equipped = true;}


    else if(class_selection == 3)
      {
      cout << "\n\n";
      cout << "Daggers Equipped! Strike swiftly and may the shadows be your guide." << endl;
      int new_attack = player_one.get_dexterity() + 45;
      player_one.set_dexterity(new_attack);
      cout << "You are now capable of dealing " << player_one.get_dexterity() << " damage." << endl;
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
            player_one.set_defense(10);
            break;
        case 2:
            cout << "\n\n";
            cout << "Mage Chosen!" << endl;
            player_one.set_health(40);
            player_one.set_strength(10);
            player_one.set_dexterity(10);
            player_one.set_defense(8);
            break;
        case 3:
            cout << "\n\n";
            cout << "Rogue Chosen!" << endl;
            player_one.set_health(60);
            player_one.set_strength(0);
            player_one.set_dexterity(45);
            player_one.set_defense(5);
            break;
         

                                }

};

void help_screen(bool combat_flag, int class_selection, Inventory bag)
/*FUNCTION DEFINITION
Output text to console to show user valid commands. 
Based on expression combat, which is a global variable, set to indicate combat loop
*/
 {

    if (combat_flag)
    {   cout << "Valid combat commands are the following:" << endl;
        if(!bag.weapon_equipped) cout << "Punch    Potion" << endl;
        if (class_selection == 1 && bag.weapon_equipped)
        cout << "Slash  Potion" << endl;
        else if (class_selection == 2 && bag.weapon_equipped)
        cout << "Fireball   Potion" << endl;
        else if (class_selection == 3 && bag.weapon_equipped)
        cout << "Stab       Potion" << endl;}
    
    else {  cout << "Valid navigational commands are the following:" << endl;
            cout << "Left   Right" << endl;
            cout << "To quit the game, press quit." << endl;
            cout << "To check your inventory, press display equipment" << endl;
            cout << "To check your stats, press stats." << endl;
            cout << "To check your location, press location" << endl;}
            cout << "If you would like to see these options again, press help" << endl;


};