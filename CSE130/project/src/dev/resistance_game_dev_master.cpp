#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <map>
#include <fstream>
using namespace std;



/*
=============================================================================================================================================================================
                                            CLASS BASIC DEFINITIONS & GAME STRUCTURE
                                            For technical details of each object please use search (CTRL/CMD + F) for the relevant tag. 
                                            TODO - list of tasks scoped and assigned for completion.
                                            REFERENCETHIS - relevant book/online references to make our lives easier.
Class
1. Player - Player is the base class and parent for all characters in the game. Player will be extended into 4 subclasses that inherit base stats.
2. Room - Room class holds information on the Room Name and Room ID.
3. GameMap - Game map stitches the rooms together to make Euler paths possible. Each vertex will be initialized so it has a degree sequence >= 2.
4. Inventory - Extended Vector Class with methods that track the count of item and the name of the item picked up. (1 Key).
Each class has getter and setter methods for the private variables to allow interaction between object.
Game
All classes will be initialized in the Global scope of the program. 
Main() function now serves as the sandbox that calls everything and controls the exit condition.  
Construct a Do While loop calling each of the helper_functions. 
        1. Take console input from user.
        2. Goes into master_control helper function that calls parse_user_input class object.
        3. Each Decision is recorded in the player object class and that will supply all user facing information about self. 
        4. Main goal of game is to wage battle. If player is in battle, then call the battle helper function.
        5.If player is dead then, exit the game.
        .... 
TODO need to more clearly define win condition. 
Global non-class Variables (Used for gameplay)
game_running - flag for game running or not. Controlling expression for do while loop.
battle - flag for battle while loop.
has_key - user can exit the jail/ win the game
        
===============================================================================================================================================================================
*/

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
    public:
        int health = 75;  
        int strength = 15 ; 
        int defense = 25;
        int dexterity = 10 ;


};




class Room 
/*  Purpose: class factory for vertex representation as room spaces
    Returns: Instance of class object */
{

    private:   
       int ID;
       string Name;

    public:

    //getter for ID
       auto get_node_designation() {
        return ID;
       }

    //setter for ID
       void set_id(int id) {
            ID = id;
       }
    //getter for name
       auto get_node_name(){
        return Name;
    //setter for name
       }
       void set_node_name(string node_name) {
            Name = node_name;
       }

};



class GameMap
/*
Purpose: Class contains a logical network of rooms. Each class instance needs to hold multiple instances of the Room class, and also provide an interface to interact with the nodes once created.
  Returns: Instance of obj Map containing the connected edges drawn.
  
  Function DEBUG references
  1. Explanation of core idea and Pseduocode supplied from CSE 310 -- Discrete Mathematics, Kenneth A Ross & Charles Wright, Pg 233 ( Edge Traversal Problems/Euler Paths)
  2. Motivating code example -- https://learncplusplus.org/learn-to-develop-a-text-based-simple-adventure-game-in-c-on-windows/
  3. Malloc for classes in CPP -- https://www.geeksforgeeks.org/malloc-vs-new/
  4. Weird Memory bug to note w/ new & classes -- https://eng.libretexts.org/Courses/Delta_College/C_-_Data_Structures/03%3A_Arrays/3.01%3A_Dynamic_memory_allocation
  5. Explanation of Map (Basically a python dictionary) -- https://m.cplusplus.com/reference/map/map/
  6. Code examples on how to interact with containers-- A Tour of C++, Bjarne Stroustrup Pg 68(Using Classes w/ Pointers), Pg 144 (maps), Pg 150 (range based for loops on containers)
                                                            
  */ 
{  

    private:
        //define the set of Vertex reflexively. Should be initialized with a Vector. 
        Room* vertices; 
        //Mapping needed between the the edges.
        map<Room*, vector<Room*>> edges; 

    public:
        
        
        Room* create_room_node(int number, string name)
        /*Purpose: Create an instance of Room every time this function is called. 
          RETURN: pointer to isntance of class object set with arguments passed. */
         {
            // Create a room instance and assign a pointer to it for mutation.
            //dereference the member functions of the class through operator precedence.
            //Meant to be assigned to a Vector.
            
            Room *room = new Room; 
            (*room).set_id(number);   //https://docs.microsoft.com/en-us/cpp/cpp/pointers-to-members?view=msvc-170
            (*room).set_node_name(name); // https://docs.microsoft.com/en-us/cpp/cpp/pointer-to-member-operators-dot-star-and-star?view=msvc-170
                                          // https://docs.microsoft.com/en-us/cpp/cpp/cpp-built-in-operators-precedence-and-associativity?view=msvc-170
            
            return room;


        };

        vector<Room*> get_connected_rooms(Room& nodes)
        /* Purpose: From node n, display a list of all possible vertices that link to n 
           Return: vector of rooms that connect to current room. */
        {
            //
            auto connected_rooms = edges[&nodes];
            return vector<Room*>(connected_rooms.begin(),
                                connected_rooms.end()); //right now this will return all paths n+1, but want to limit it to 3 paths. n-1, n, and n+1. 
            

        }
    

        void create_edge(Room& source, Room& destination)
        /* Purpose: Create an adjacency list implicitly by defining edges as two nodes. 
        
        
         Note:
               1. Mathematically, now the number of edges for a connected graph is n!/(n-2)2! or n(n-1)/2 -- Discrete Mathematics, Kenneth Ross Pg 186
               2. Pass in references to the Room pointer. 
        
       */
        {
        
            auto& adjacents = edges[&source]; 
            auto start = adjacents.begin();
            auto stop = adjacents.end();
            //if edge does not exist between vertices then 
            if (find(start, stop, &destination) == adjacents.end()) {   //https://linuxhint.com/find-value-vector-cpp/
                adjacents.push_back(&destination);} 
             // do nothing if the edge already exists.

        }

};


typedef struct Inventory{
int potions = 4;
bool armor_equipped = false;
bool weapon_equipped = false;

} Inventory;



/*
=============================================================================================================================================================================
                                                                    HELPER   FUNCTIONS
FUNCTIONS GENERAL USAGE IN GAME
Functions will be used in game to modify class objects because they are in global scope.
        i.e. void function_runtime_version_get_player_name(){
            string user_input;
            cout << "What's your name, brave warrior" << endl
            cin >> user_input;
            Player1.set_name = user_input;
        } **VALID provided Player Player1(); initialized outside of main in direct body of code.  
===============================================================================================================================================================================
*/

//ROOM & Map Helper Functions

void load_map()
/*
FUNCTION DEFINITION
    Construct game map with a for loop calling the GameMap Class. 
*/

{}; 


void navigate_player()
{
    string console_navigational_command;

    cout << "You are currently in " << player_one.get_string_location() << endl;
    cout << "Where would you like to go?" << endl;
    cout << "Left   Right" << endl;
    cin >> console_navigational_command;

    if(console_navigational_command == "left" || console_navigational_command == "Left")
    {



    total_rooms_visited++;
    }
    else if(console_navigational_command == "right" || console_navigational_command == "Right")

    {

    total_rooms_visited++;
    }

    else if(console_navigational_command == "quit" || console_navigational_command == "Quit")
    {exit(EXIT_SUCCESS);}


    else if(console_navigational_command == "location" || console_navigational_command == "Location")
    {player_one.get_string_location();}

    else if(console_navigational_command == "stats" || console_navigational_command == "Stats")
    {show_all_player_stats(player_one);}


    else if (console_navigational_command == "help" || console_navigational_command == "Help")
        {help_screen(player_one, player_in_combat, player_backpack);}
    

    else {help_screen(player_one, player_in_combat, player_backpack);}



};





//Player Helper Functions

template<class T> void show_all_player_stats(T agent){
    
    cout << agent.get_health() << " HP" << endl;
    cout << agent.get_strength() << " strength." << endl;
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
    cin >> user_class_choice;

    return user_class_choice;
};


void ready_player_one(int class_choice) {
    switch(class_choice){
        case 1:
            cout << "Warrior chosen!" << endl;
            player_one.set_health(150);
            player_one.set_strength(20);
            break;
        case 2:
            cout << "Mage Chosen!" << endl;
            player_one.set_health(40);
            player_one.set_strength(10);
            player_one.set_dexterity(10);
            break;
        case 3:
            cout << "Rogue Chosen!" << endl;
            player_one.set_health(80);
            player_one.set_strength(5);
            player_one.set_dexterity(20);
            break;
         

                                }

};

void name_decision(){
    string name;
    cout << "What do you call yourself, noble challenger?" << endl;
    cin >> name;
    player_one.set_name(name);
};

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
    int player_attack;
    bool player_in_combat = true, user_survived_combat = true;
    Enemy *opponent = &enemy_forces.at(get_player_location);
    string battle_console_decision;

    if((*opponent).still_alive())
   { cout << "A foe has appeared!" << endl;}

    while((*opponent).still_alive() && player_one.still_alive()){
    cout << "What will you do?" << endl;
    
    if (class_selection == 1 && player_backpack.weapon_equipped)
    cout << "Slash  Drink Potion" << endl;
    else if (class_selection == 2 && player_backpack.weapon_equipped)
    cout << "Fireball   Drink Potion" << endl;
    else if (class_selection == 3 && player_backpack.weapon_equipped)
    cout << "Stab       Drink Potion" << endl;

    cin >> battle_console_decision;

    if(battle_console_decision == "Drink Potion" || battle_console_decision == "drink potion")
    {use_potion(); }

    else if (battle_console_decision == "Fireball" || battle_console_decision == "fireball" 
            | battle_console_decision == "Slash" || battle_console_decision == "slash" 
            | battle_console_decision == "Stab" || battle_console_decision == "stab" )
    {default_random_engine scale_player_stats;
    uniform_int_distribution<int> player_distribution(1, player_one.get_dexterity());
    auto player_stats_scaled = player_distribution(scale_player_stats);
    if(class_selection == 1 || class_selection == 3) {player_attack = player_one.get_strength() + player_stats_scaled;}
    else if (class_selection == 2) {player_attack = player_one.get_spellpower() + player_stats_scaled;}
    int player_defense = player_one.get_defense() + player_stats_scaled;


    default_random_engine scale_enemy_stats;
    uniform_int_distribution<int> enemy_distribution(1, (*opponent).get_dexterity());
    auto enemy_stats_scaled = enemy_distribution(scale_enemy_stats);
    int enemy_attack = (*opponent).get_strength() + enemy_stats_scaled;
    int enemy_defense = (*opponent).get_defense() + enemy_stats_scaled;


    int player_turn_attack_enemy = player_attack - enemy_defense;
    int enemy_turn_attack_player = enemy_attack - player_defense;

    int player_current_health = player_one.get_health() - enemy_turn_attack_player;
    player_one.set_health(player_current_health);
    int enemy_current_health = (*opponent).get_health() - player_turn_attack_enemy;
    (*opponent).set_health(enemy_current_health);
    cout << "You attack for " << player_turn_attack_enemy << endl;
    cout << "The enemy has " << enemy_current_health << " health remaining." << endl;
    cout << "The enemy attacks you for " << enemy_turn_attack_player << endl;
    cout << "You have " << player_current_health << " health remaining." << endl; }

    else {help_screen(player_one, player_in_combat, player_backpack);}}

    if (!player_one.still_alive())
    {cout << "Game Over." << endl;
     exit(EXIT_SUCCESS); }

};


// INVENTORY HELPER FUNCTIONS

void use_potion(){
    cout << "10 Health added";
    //inventory object potions -= 1
    player_backpack.potions -= 1;
    int top_up = player_one.get_health + 10;
    player_one.set_health(top_up);
    cout << "You now have " << player_one.display_health() << endl;
    
};

void confirm_armor_equip(int class_selection){
    if(class_selection == 1)
    {cout << "Shield Equipped!" << endl;}
    //inventory object shield_equipped = true
    else if(class_selection == 2)
    {cout << "A forcefield envelopes you. You feel stronger." << endl;}
    else if(class_selection == 3)
    {cout << "Leather cowl equipped." << endl;}
    player_backpack.armor_equipped = true;
    int new_defense = player_one.get_defense() + 10;
    player_one.set_defense(new_defense);
    
};


void confirm_weapon_equip(int class_selection){
    if(class_selection == 1)
    {cout << "Sword equipped! Slay them all." << endl;
    int new_attack = player_one.get_strength() + 10;
    player_one.set_strength(new_attack);}

    else if (class_selection == 2)
    { cout << "Spellbook acquired! Time to turn up the heat." << endl;
      int new_attack = player_one.get_spellpower() + 50;
      player_one.set_spellpower(new_attack);}

    else if(class_selection == 3)
      {cout << "Daggers Equipped! Strike swiftly and may the shadows be your guide." << endl;
      player_backpack.weapon_equipped = true;}

};

void place_weapon_in_room(int user_class, int room_count){
    if (room_count == 4){
    string user_decision;
    cout << "You notice there is a powerful object on the ground. Pick it up?" << endl;
    cout << "Yes    No" << endl;
    cin >> user_decision;
    if(user_decision == "Yes" || user_decision =="yes")
    {confirm_weapon_equip(user_class);}}

};

void place_armor_in_room(int user_class, int room_count){
    if(room_count == 2){
    string user_decision;
    cout << "You notice there is a durable object on the ground. Pick it up?" << endl;
    cout << "Yes    No" << endl;
    cin >> user_decision;
    if(user_decision == "Yes" || user_decision == "yes")
    {confirm_armor_equip(user_class);}}
};

void display_equipment(int class_selection){

    if(player_backpack.potions >= 1)
    cout << bag.potions << " potions." << endl;

    if(class_selection == 1 && player_backpack.weapon_equipped && player_backpack.armor_equipped)
    {cout << "Sword." << endl;
    cout << "Shield." << endl;}
    else if (class_selection == 2 && player_backpack.weapon_equipped && player_backpack.armor_equipped)
    {cout << "Spellbook." << endl;
    cout << "Arcane Armor." << endl;}
    else if (class_selection == 2 && player_backpack.weapon_equipped && player_backpack.armor_equipped)
    {cout << "Daggers." << endl;
     cout << "Leather Cowl." << endl;}

    else if(class_selection == 1 && player_backpack.weapon_equipped)
    cout << "Sword." << endl;
    else if(class_selection == 2 && player_backpack.weapon_equipped)
    cout << "Spelbook." << endl;
    else if(class_selection == 3 && player_backpack.weapon_equipped)
    cout << "Daggers." << endl;


    else if(class_selection == 1 && player_backpack.armor_equipped)
    cout << "Shield." << endl;
    else if(class_selection == 2 && player_backpack.armor_equipped)
    cout << "Arcane Armor." << endl;
    else if(class_selection == 3 && player_backpack.armor_equipped)
    cout << "Leather Cowl." << endl;
}


// HOUSEKEEPING FUNCTIONS

void help_screen(bool combat_flag, int class_selection)
/*FUNCTION DEFINITION
Output text to console to show user valid commands. 
Based on expression combat, which is a global variable, set to indicate combat loop
*/
 {

    if (combat_flag)
    {   cout << "Valid combat commands are the following:" << endl;
        if(!player_backpack.weapon_equipped) cout << "Punch    Drink Potion" << endl;
        if (class_selection == 1 && player_backpack.weapon_equipped)
        cout << "Slash  Drink Potion" << endl;
        else if (class_selection == 2 && player_backpack.weapon_equipped)
        cout << "Fireball   Drink Potion" << endl;
        else if (class_selection == 3 && player_backpack.weapon_equipped)
        cout << "Stab       Drink Potion" << endl;}
    
    else {  cout << "Valid navigational commands are the following:" << endl;
            cout << "Left   Right" << endl;
            cout << "To quit the game, press quit." << endl;
            cout << "To check your inventory, press display equipment" << endl;
            cout << "To check your stats, press stats." << endl;
            cout << "To check your location, press location" << endl;
            cout << "If you would like to see these options again, press help" << end}


};
int enemy_kill_counter;
void win_condition(){
    if (enemy_kill_counter == 9){

     cout << "You pick up a key from the last fallen opponent." << endl;
     cout << "You manage to free your family with the key and begin to make your escape." << endl;
     cout << "------------------------------------------------------------------------" << endl;
     cout << "-                                                                        -" << endl;
     cout << "-                                                                        -" << endl;
     cout << "-                         YOU WIN                                        -" << endl;
     cout << "-                                                                        -" << endl;
     cout << "-                                                                        -" << endl;
     cout << "------------------------------------------------------------------------" << endl;

     
       }


}

void welcome_screen()
/*
FUNCTION DEFINITION
create file with text to display welcome message to user
open file with stream and display the help_screen()
ASCII art for Title ??? Saved as png file and also called with file_stream
REFERENCETHIS C++ for the Absolute Beginner, pg 277 */

{
bool false_combat_flag = false;
int false_class_selection = 4;
ifstream title_screen;
ifstream welcome_text;
title_screen.open("game_name.txt");
string title_sequenece;
if (title_screen.is_open()){
while(getline(title_screen, title_sequenece))
{cout << title_sequenece << endl;}
title_screen.close();

}
cout << "\n\n\n\n\n\n\n";

welcome_text.open("game_welcome.txt");
string lines;
if (welcome_text.is_open()){
    while(getline(welcome_text, lines)){
        cout << lines << endl;
    }
    welcome_text.close();

}
cout << "\n\n\n\n\n\n\n";
help_screen(false_combat_flag, false_class_selection);
false_combat_flag = true;
help_screen(false_combat_flag, false_class_selection);

};

