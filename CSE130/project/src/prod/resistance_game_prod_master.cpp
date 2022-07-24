#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <map>
#include <fstream>
using namespace std;

class Player
/* Purpose: Boilerplate class for all players in the game. 
   Return: Object instace of class Player.
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

        void set_string_location(string input_location){

            string_location = input_location;
        }

        void set_int_location(int input_location){

            int_location = input_location;
        }

        void display_location(){
            cout << "You are in " << string_location << endl;

        }


        //check death. 
        //TODO Will be called at the end of the do while loop that will be in void battle function 

        bool still_alive()
        {

            if  (health > 0) return true;
            else return false;
        }


};

//call the same thing a different name for convienence sake. (Player and Enemy)

class Enemy: public Player {


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
       int get_node_designation() {
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
         :Param:number - number designation of the room (0 -> N + 1)
         :Param:name - name of the room
          Return: pointer to instance of class object set with arguments passed. */
         {
            // Create a room instance and assign a pointer to it for mutation.
            // dereference the member functions of the class through operator precedence.
            // Meant to be assigned to a Vector.
            
            Room *room = new Room; 
            (*room).set_id(number);   //https://docs.microsoft.com/en-us/cpp/cpp/pointers-to-members?view=msvc-170
            (*room).set_node_name(name); // https://docs.microsoft.com/en-us/cpp/cpp/pointer-to-member-operators-dot-star-and-star?view=msvc-170
                                          // https://docs.microsoft.com/en-us/cpp/cpp/cpp-built-in-operators-precedence-and-associativity?view=msvc-170
            
            return room;


        };

        vector<Room*> get_connected_rooms(Room& nodes)
        /* Purpose: From node n, display a list of all possible vertices that link to n 
           :Param: &nodes - address of nodes. Expects a Room object. Best practice is to supply a Room Ptr.
            Return: vector of rooms that connect to current room. */
        {
            //
            auto connected_rooms = edges[&nodes];
            return vector<Room*>(connected_rooms.begin(),
                                connected_rooms.end()); 
            

        }
    

        void create_edge(Room& source, Room& destination)
        /* Purpose: Create an adjacency list implicitly by defining edges as two nodes. 
           Return: Function returns nothing. All stored in the graph object. This way the object has authority over the constructing
                    and destructing the ptr.
        
        
         Note:
                1. Mathematically we are creating a directed graph between the source and the sink nodes.
                   Since we are requiring the player to enter every node for the game,
                  we create Euler circuits by making all the degree sequences even. A png image is supplied of the work done beforehand.
                2. Programmaticially accomplished through use of the map data structure. Each node is a pointer. This functionally means
                  we can create a table of lookup values between {node 1, node 2,..,node n} to respective adjacency list of nodes.
        
        
       */
        {
        
            auto& adjacents = edges[&source]; 
            auto start = adjacents.begin();
            auto stop = adjacents.end();
            //if edge does not exist between vertices then directionally link them
            if (find(start, stop, &destination) == adjacents.end()) {   //https://linuxhint.com/find-value-vector-cpp/
                adjacents.push_back(&destination);} 
             // do nothing if the edge already exists.

        }

};


//GLOBALS
typedef struct Inventory{
int potions = 20;
bool armor_equipped = false;
bool weapon_equipped = false;

} Inventory;


int get_class_decision, enemy_kill_counter = 0, total_rooms_visited = 0;
bool player_in_combat = false, game_running = true;
GameMap cartograph; 
vector<Room*> arena;
Player player_one;
Inventory player_backpack;
vector <Enemy> enemy_forces_assembled(10);
vector <string> game_locations = {"Holding Cell", "Arena Room 1", "Arena Room 2", "Arena Room 3", "Arena Room 4", "Arena Room 5", 
                                "Arena Room 6", "Arena Room 7", "Arena Room 8", "Arena Room 9"};

// FUNCTION FORWARD DECLARATIONS
int class_choice();
void name_decision();
void welcome_screen();
void use_potion();
void confirm_armor_equip(int class_selection);
void confirm_weapon_equip(int class_selection);
void place_weapon_in_room(int user_class, int room_count);
void place_armor_in_room(int user_class, int room_count);
void ready_player_one(int class_choice);
void display_equipment(int class_selection);
void combat(vector <Enemy> &enemy_forces, int class_selection);
void help_screen(bool combat_flag, int class_selection, Inventory bag);
void move_user(int current_location, string console_decision);
template<class T> void show_all_player_stats(T agent);
void load_game_map();
void win_condition();
void navigational_console_command();


int main(){
    //hydrate the enemy forces
    for(int i = 0; i < enemy_forces_assembled.size(); i++) {enemy_forces_assembled[i].set_name("Enemy");};
    //create the map
    for (int i = 0; i < game_locations.size(); i++){
        auto* const location = cartograph.create_room_node(i, game_locations.at(i));
        arena.push_back(location);}
    //show welcome
    welcome_screen();
    //get user name
    name_decision();
    // get the class
    get_class_decision = class_choice();
    //based on user and user choice. Alter user stats.
    ready_player_one(get_class_decision);
    show_all_player_stats(player_one);
    load_game_map();
    //give default values to the starting location of the player
    player_one.set_int_location(0);
    player_one.set_string_location("Holding Cell");
    //start an infinite loop. Respective functions have the exit() call nested inside.
    while(game_running)
    {
        //if player is at the start, just have them move to another room.
     if(player_one.get_int_location() == 0 && total_rooms_visited == 0)navigational_console_command();

     else{
        //otherwise initiate the proper loop. Player can pick up a defense and offensive power up based on number of rooms visited.
        place_armor_in_room(get_class_decision, total_rooms_visited);
        place_weapon_in_room(get_class_decision, total_rooms_visited);
        //war
        combat(enemy_forces_assembled, get_class_decision);
        //win when everyone is dead
        win_condition();
        // if an enemy is still alive in another room, go find them
        navigational_console_command();
     }}

    return 0;
}

//NAVIGATIONAL FUNCTIONS 



void load_game_map()
/* There is a illustrated game map that is supplied as part of project that more clearly shows the edges between the nodes.
    Every node has an even degree sequence except node 3. There are some loops meant to trick the player. 
    Node 3 has more indegrees than outdegrees making it tricky for the player to navigate to all the rooms.
    Node 9 pushes you back to 1 and 2. It makes it easier to navigate to the other side of the map once your reach the end.

    
*/
{
    //make a Euler path possib 

// vertex 0 degree sequence is 2
cartograph.create_edge(*arena.at(0), *arena.at(1));
cartograph.create_edge(*arena.at(0), *arena.at(2));


//vertex 1 degree sequence is 4
cartograph.create_edge(*arena.at(1), *arena.at(4));
cartograph.create_edge(*arena.at(1), *arena.at(5));

//vertex 2 degree sequence is 4
cartograph.create_edge(*arena.at(2), *arena.at(2));
cartograph.create_edge(*arena.at(2), *arena.at(4));


//vertex 3 degree sequence is 5
cartograph.create_edge(*arena.at(3), *arena.at(1));
cartograph.create_edge(*arena.at(3), *arena.at(7));

//vertex 4 degree sequence is 4
cartograph.create_edge(*arena.at(4), *arena.at(3));
cartograph.create_edge(*arena.at(4), *arena.at(7));


//vertex 5 degree sequence is 4
cartograph.create_edge(*arena.at(5), *arena.at(5));
cartograph.create_edge(*arena.at(5), *arena.at(6));

//vertex 6 degree sequence is 4
cartograph.create_edge(*arena.at(6), *arena.at(3));
cartograph.create_edge(*arena.at(6), *arena.at(8));

//vertex 7 degree sequence is 4
cartograph.create_edge(*arena.at(7), *arena.at(6));
cartograph.create_edge(*arena.at(7), *arena.at(9));

//vertex 8 degree sequence is 4
cartograph.create_edge(*arena.at(8), *arena.at(3));
cartograph.create_edge(*arena.at(8), *arena.at(9));


//vertex 9 degree sequence is 2
cartograph.create_edge(*arena.at(9), *arena.at(1));
cartograph.create_edge(*arena.at(9), *arena.at(2));
}

void move_user(int current_location, string console_decision){
/* Purpose: Bus object for the player and the map. 
Param:current_location: - current_location comes from the player.get_int_location() method
Param: console_decision - comes from the terminal command input. The function is meant to be called inside another function that will have this param.
Returns: Nothing. User is moved from beginning room to ending room based on choice.

*/
//get a vector of pointers of the rooms the current room is connected to
vector<Room*> test_first_connect = cartograph.get_connected_rooms(*arena.at(current_location));
//unpack the room locations into pointers for easier access
Room *left_room = test_first_connect[0];
Room *right_room = test_first_connect[1];

//get the both rooms ready to be passed into the user depending upon the receiving input. Dereference each room b/c they're still pointers here.
string left_room_name = (*left_room).get_node_name();
int left_room_designation = (*left_room).get_node_designation();


string right_room_name = (*right_room).get_node_name();
int right_room_designation = (*right_room).get_node_designation();

//create if/else statement to assign either left room or right room as new user room.

if(console_decision == "left" || console_decision == "Left"){
    player_one.set_int_location(left_room_designation);
    player_one.set_string_location(left_room_name);
    cout << "You are now in " << left_room_name << endl;
    cout << "\n\n";
}

else if(console_decision == "right" || console_decision == "Right"){
    player_one.set_int_location(right_room_designation);
    player_one.set_string_location(right_room_name);
    cout << "You are now in " << right_room_name << endl;
    cout << "\n\n";
}


};


void navigational_console_command()
/* Purpose: Provide a uniform way for the program to accept input from the user and map those inputs to various functions

*/
{
    string console_navigational_command;
    cout << "You are currently in " << player_one.get_string_location() << endl;
    cout << "Where would you like to go?" << endl;
    cout << "Left   Right" << endl;
    cin >> console_navigational_command;

    // if user selects a navigational command, call move_user, and add to the room count of rooms visited.
    if(console_navigational_command == "left" || console_navigational_command == "Left" ||
        console_navigational_command == "right" || console_navigational_command == "Right")

    {
    ++total_rooms_visited;
    move_user(player_one.get_int_location(), console_navigational_command);
    
    }
    // if user doesn't want to play anymore. call exit()
    else if(console_navigational_command == "quit" || console_navigational_command == "Quit")
    {exit(EXIT_SUCCESS);}

    //recite location to user on request
    else if(console_navigational_command == "location" || console_navigational_command == "Location")
    {player_one.get_string_location();}

    //recite stats to user on request
    else if(console_navigational_command == "stats" || console_navigational_command == "Stats")
    {show_all_player_stats(player_one);}

    // display inventory upon request
    else if(console_navigational_command == "equipment" || console_navigational_command == "Equipment"){
        display_equipment(get_class_decision);
    }

    // if user explicitly asks for help, give them the help dialogue
    else if (console_navigational_command == "help" || console_navigational_command == "Help")
        {help_screen( player_in_combat,  get_class_decision, player_backpack);}

    // catch everything else with the help dialogue
    else {help_screen( player_in_combat,  get_class_decision, player_backpack);}



};

//HOUSEKEEPING FUNCTIONS

void help_screen(bool combat_flag, int class_selection, Inventory bag)
/*
Purpose: Output text to console to show user valid commands. 
Param:combat_flag: Global flag meant to indicate whether user is in combat or not. In practice, the respective functions that call
this function override the global flag but keeping it for continuity purposes.
Param:class_selection: Based on the user input for class selection. 
Param:Inventory Bag: Based on global struct object Inventory. Checks if users has weapons and shields equip. 
*/
 {

    if (combat_flag)
    {   cout << "\n";
        cout << "Valid combat commands are the following:" << endl;
        if(!bag.weapon_equipped) cout << "Punch    Potion" << endl;
        if (class_selection == 1 && bag.weapon_equipped)
        cout << "Slash  Potion" << endl;
        else if (class_selection == 2 && bag.weapon_equipped)
        cout << "Fireball   Potion" << endl;
        else if (class_selection == 3 && bag.weapon_equipped)
        cout << "Stab       Potion" << endl;}
    
    else {  
            cout << "\n";
            cout << "Valid navigational commands are the following:" << endl;
            cout << "Left   Right" << endl;
            cout << "To quit the game, press quit." << endl;
            cout << "To check your inventory, press equipment" << endl;
            cout << "To check your stats, press stats." << endl;
            cout << "To check your location, press location" << endl;}
            cout << "If you would like to see these options again, press help" << endl;
            cout << "\n\n";


};

void welcome_screen()
/*
Purpose: Stream files in that are used to welcome the user and introduce the game.
Notes:
    No Params but expects a file with game_name.txt and game_welcome.txt in the same file directory as the program.

REFERENCETHIS C++ for the Absolute Beginner, pg 277 */

{
bool false_combat_flag = false;
int false_class_selection = 4;
Inventory false_inventory_object;
ifstream title_screen;
ifstream welcome_text;
title_screen.open("game_name.txt");
string title_sequenece;
if (title_screen.is_open()){
while(getline(title_screen, title_sequenece))
{cout << title_sequenece << endl;}
title_screen.close();

}
cout << "\n\n";

welcome_text.open("game_welcome.txt");
string lines;
if (welcome_text.is_open()){
    while(getline(welcome_text, lines))
    {cout << lines << endl;}
    welcome_text.close();

}
cout << "\n\n";
help_screen(false_combat_flag, false_class_selection, false_inventory_object);
false_combat_flag = true;
cout << "\n\n";
help_screen(false_combat_flag, false_class_selection, false_inventory_object);

};

// PLAYER FUNCTIONS

int class_choice()
/*
Purpose: Ask the user to select a class and then record the decision for gameplay mechanics.
*/
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

void name_decision()
/* Purpose: Ask the user for their name and record the decision */ 
{
    string name;
    cout << "What do you call yourself, noble challenger?" << endl;
    cin >> name;
    player_one.set_name(name);
    cout << "Hello, " << player_one.get_name();
    cout << "\n\n";
};

template<class T> void show_all_player_stats(T agent)
/* Purpose: Provide a generic function to accept the stats of the player and the enemy
   on demand. */

{
    cout << "\n\n";
    cout << agent.get_name();
    cout << " has the following stats:" << endl;
    cout << agent.get_health() << " HP" << endl;
    cout << agent.get_strength() << " strength." << endl;
    cout << agent.get_spellpower() << " spellpower." << endl;
    cout << agent.get_defense() << " defense." << endl;
    cout << agent.get_dexterity() << " dexterity." << endl;
    cout << "\n\n";


};

void ready_player_one(int class_choice) 
/* Purpose: Make 3 "classes" from the base class. Meant to escape scope issues.

Notes:
    Warrior - Tank character. Warrior is easy mode. Very hard to die and deals a lot of damage.
    Mage - Medium level difficulty. Basically a glass cannon. Especially once the character has all the upgrades.
    Rogue - most fun/frustrating. Completely based on RNG. The rogue has the ability to insta kill any other character
    but in turn can be obliterated in 1 - 2 hits.
*/
 {
    switch(class_choice){
        case 1:
            cout << "\n\n";
            cout << "Warrior chosen!" << endl;
            player_one.set_health(150);
            player_one.set_strength(22);
            player_one.set_defense(10);
            break;
        case 2:
            cout << "\n\n";
            cout << "Mage Chosen!" << endl;
            player_one.set_health(80);
            player_one.set_strength(17);
            player_one.set_dexterity(10);
            player_one.set_defense(10);
            break;
        case 3:
            cout << "\n\n";
            cout << "Rogue Chosen!" << endl;
            player_one.set_health(60);
            player_one.set_strength(0);
            player_one.set_dexterity(45);
            player_one.set_defense(10);
            break;
         

                                }

};

//COMBAT FUNCTION

void combat(vector <Enemy> &enemy_forces, int class_selection)
/* 
Purpose: Specifies battle mechanics between player and enemy forces.
Param: &enemy_forces -- CPP allows for pass by reference with vectors/arrays provided the & symbol is specified in function calls.
Param: class_selection -- User decided input on the types of powerups to expect during playthrough.

Notes:
    Both player and enemy health will be called at the start of the loop.
    The loop will Pokemon style.
    "An enemy has appeared"
    Combat Options now will be valid in the parse input class (Flag set to True. Again global variable in the class)
    Attack          Drink Potion
    Depending upon the class, it will expose different attacks which are just different scaled hits based on attributes
    If the player is dead then, then say game over and exit game. (Game running will be a Global Flag)
    
     */
{   
    //get the player location and match the int location with the position of the enemy in the vector.
    int get_player_location = player_one.get_int_location();
    int player_attack,player_defense;
    bool player_in_combat = true;
    //Issue a pointer to the name (enemy_forces) because all changes downstream need to be reflected in source.
    Enemy *opponent = &enemy_forces.at(get_player_location);
    string battle_console_decision;

    if((*opponent).still_alive())
   { 
    cout << "\n\n";
    cout << "A foe has appeared!" << endl;}

    //Make a while loop for all of this based on the player.is_alive() for both player and enemy.

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

    //Enter loop if the user enters the respective "attack" command. 
    //If weapon is equipped, treat the fireball, slash, stab keywords as valid 
    //if weapon is not equipped, only punch is valid
    else if (((battle_console_decision == "Fireball" || battle_console_decision == "fireball" 
            || battle_console_decision == "Slash" || battle_console_decision == "slash" 
            || battle_console_decision == "Stab" || battle_console_decision == "stab") && player_backpack.weapon_equipped) ||

            ((battle_console_decision == "Punch" || battle_console_decision == "punch" ) && !player_backpack.weapon_equipped))
    {
    // generate random distribution for both attack and defense. Scaled to player stats with the same seed each turn of combat. 
    random_device player_seed;
    mt19937 generate_player_parameters(player_seed());
    //base atack off player dexterity. Provide a floor of 12.
    uniform_int_distribution<int> player_attack_distribution(12, 12 + player_one.get_dexterity());
    //base defense off existing defense
    uniform_int_distribution<int> player_defense_distribution(5, floor(player_one.get_defense()/2));
    auto player_attack_stats_scaled = player_attack_distribution(generate_player_parameters);
    auto player_defense_stats_scaled = player_defense_distribution(generate_player_parameters);

    // based on class selection call different user attributes to wage war.
    if (class_selection == 2 && player_backpack.weapon_equipped) {
        player_attack = player_one.get_spellpower() + player_attack_stats_scaled;
        player_defense = player_one.get_defense() + player_defense_stats_scaled;}
    else  
    {player_attack = player_one.get_strength() + player_attack_stats_scaled;
     player_defense = player_one.get_defense() + player_defense_stats_scaled;}


   // same as for enemy, as for player.
    random_device enemy_seed;
    mt19937 generate_enemy_parameters(enemy_seed()); //https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
    uniform_int_distribution<int> enemy_attack_distribution(40, 40 + (*opponent).get_dexterity());
    uniform_int_distribution<int> enemy_defense_distribution(9, 9 + floor((*opponent).get_defense()/2));
    int enemy_attack_stats_scaled = enemy_attack_distribution(generate_enemy_parameters);
    int enemy_defense_stats_scaled = enemy_defense_distribution(generate_enemy_parameters);

    int enemy_attack = (*opponent).get_strength() + enemy_attack_stats_scaled;
    int enemy_defense = (*opponent).get_defense() + enemy_defense_stats_scaled;

    // generate the damage done this turn
    int player_turn_attack_enemy = player_attack - enemy_defense;
    int enemy_turn_attack_player = enemy_attack - player_defense;

    //Player attacks first
    int enemy_current_health = (*opponent).get_health() - player_turn_attack_enemy;
    (*opponent).set_health(enemy_current_health);
    cout << "\n\n";
    if(player_turn_attack_enemy < 0)
    player_turn_attack_enemy = 0;
    cout << "You attack for " << player_turn_attack_enemy << " damage." << endl;
    
    // if the opponent is dead then break out of the loop before enemy can attack.
    if (!(*opponent).still_alive())
    {
      cout << "Enemy defeated!" << endl;

      enemy_kill_counter ++;
      break; }
    
    // if enemy is still alive, then attack the player
    int player_current_health = player_one.get_health() - enemy_turn_attack_player;
    player_one.set_health(player_current_health);

    // output results of this turn to the console.
    cout << "The enemy has " << enemy_current_health << " health remaining." << endl;
    cout << "\n";

    if(enemy_turn_attack_player < 0)
    enemy_turn_attack_player = 0;
    cout << "The enemy attacks you for " << enemy_turn_attack_player << " damage."  << endl;
    cout << "You have " << player_current_health << " health remaining." << endl; \
    cout << "\n\n";}

    else {help_screen(player_in_combat, class_selection, player_backpack);}}

    // if the player has died, then initiate exit()
    if (!player_one.still_alive())
    {cout << "Game Over." << endl;
     exit(EXIT_SUCCESS); }

};


//INVENTORY FUNCTIONS
void use_potion()
/*
Purpose: Defines interaction between the player, inventory, navigational objects.
When a player inputs potion or Potion into the console, a potion is consumed from inventory,
and the effect is added to the player.


POTION COUNT: 20
POTION EFFECTIVENESS: 40



*/
{
    //check inventory for available potions
    if(player_backpack.potions >= 1){
    cout << "\n\n";
    cout << "40 Health added." << endl;;
    //inventory object potions -= 1
    player_backpack.potions -= 1;
    // add the effect to the player
    int top_up = player_one.get_health() + 40;
    player_one.set_health(top_up);
    //console output
    cout << "You now have " << player_one.get_health() << " HP." << endl;
    cout << "There are " << player_backpack.potions << " potions remaining." << endl;
    cout << "\n\n";}
    // if player does not have any potions remaining. Then say sorry :( 
    else{
        cout << "\n\n";
        cout << "Sorry. No more potions.";}

    
};

void confirm_armor_equip(int class_selection)
/*
Purpose: Define defensive upgrade interaction between player and inventory. This directly affects combat as well.

Notes:
    WARRIOR UPGRADE - +20
    MAGE UPGRADE - +15
    ROGUE UPGRADE - +8

*/
{
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


void confirm_weapon_equip(int class_selection)
/*
Purpose: Provide interaction between the player and inventory objects based on class selection.

Notes:
     Warrior - +10 attack power
     Mage - +50 spell power
     Rogue - +60 dexterity


*/
{
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
      int new_attack = player_one.get_dexterity() + 60;
      player_one.set_dexterity(new_attack);
      cout << "You are now capable of dealing " << player_one.get_dexterity() << " damage." << endl;
      player_backpack.weapon_equipped = true;}
    

};

void place_weapon_in_room(int user_class, int room_count)
/* Purpose : Extend interaction of user and offensive inventory objects to Room.
   :Param: room_count - comes from the navigational control functions. Supplied here to trigger event.

*/{
    if (room_count == 4){
    string user_decision;
    cout << "\n\n";
    cout << "You notice there is a powerful object on the ground. Pick it up?" << endl;
    cout << "Yes    No" << endl;
    cin >> user_decision;
    if(user_decision == "Yes" || user_decision =="yes")
    {confirm_weapon_equip(user_class);}}
    //if user the user has opted out of upgrades
    else if (!(user_class == 1 || user_class == 2 || user_class == 3))
    {cout << "You can't pick it up!" << endl;} 

};

void place_armor_in_room(int user_class, int room_count)
/* Purpose : Extend interaction of user and defensive inventory objects to Room.
   :Param: room_count - comes from the navigational control functions. Supplied here to trigger event.

*/{
    if(room_count == 2){
    string user_decision;
    cout << "\n\n";
    cout << "You notice there is a durable object on the ground. Pick it up?" << endl;
    cout << "Yes    No" << endl;
    cin >> user_decision;
    if(user_decision == "Yes" || user_decision == "yes")
    {confirm_armor_equip(user_class);}}
    //if user the user has opted out of upgrades
    else if (!(user_class == 1 || user_class == 2 || user_class == 3))
    {cout << "You can't pick it up!" << endl;} 
};

void display_equipment(int class_selection)
/* Purpose: Enumerate the inventory object on command.
   :Param: class_selection - user input on class selection
*/{
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
    cout << "\n\n";
};

//WIN

void win_condition()
/*Purpose: Define a successful exit condition from the loop.
    Notes:    
        Player has to kill all enemies

*/
{
    if (enemy_kill_counter == 9){

     cout << "You pick up a key from the last fallen opponent." << endl;
     cout << "You manage to free your family with the key and begin to make your escape." << endl;
     cout << "------------------------------------------------------------------------" << endl;
     cout << "-                                                                        -" << endl;
     cout << "-                                                                        -" << endl;
     cout << "-                         YOU WIN                                        -" << endl;
     cout << "-                                                                        -" << endl;
     cout << "-                                                                        -" << endl;
     cout << "------------------------------------------------------------------------"   << endl;
     exit(EXIT_SUCCESS);

     
       }


};