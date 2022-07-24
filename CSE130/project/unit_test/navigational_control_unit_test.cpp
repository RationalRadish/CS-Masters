#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <map>
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

        void set_string_location(string input_location){

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


Player player_one;
int total_rooms_visited;
bool player_in_combat;
GameMap cartograph; // this will be in global
Inventory player_backpack;
vector<Room*> arena;
vector <string> game_locations = {"Holding Cell", "Arena Room 1", "Arena Room 2", "Arena Room 3", "Arena Room 4", "Arena Room 5", 
                                "Arena Room 6", "Arena Room 7", "Arena Room 8", "Arena Room 9", "Jailor's Room"};


void load_game_map(){
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
}

//vertex 9 degree sequence is 2
{cartograph.create_edge(*arena.at(9), *arena.at(1));
cartograph.create_edge(*arena.at(9), *arena.at(2));
}

void move_user(int current_location, string console_decision){

vector<Room*> test_first_connect = cartograph.get_connected_rooms(*arena.at(current_location));
Room *left_room = test_first_connect[0];
Room *right_room = test_first_connect[1];

string left_room_name = (*left_room).get_node_name();
int left_room_designation = (*left_room).get_node_designation();


string right_room_name = (*right_room).get_node_name();
int right_room_designation = (*right_room).get_node_designation();

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


int class_sel;

void navigational_console_command();

int main() {
    
    for (int i = 0; i < game_locations.size(); i++){
        auto* const location = cartograph.create_room_node(i, game_locations.at(i));
        arena.push_back(location);
    }

class_sel = class_choice();
load_game_map();
player_one.set_int_location(0);
player_one.set_string_location("Holding Cell");
for(int i = 0 ; i < 20; i ++) navigational_console_command();


    return 0;
};


void navigational_console_command()
{
    string console_navigational_command;
    cout << "You are currently in " << player_one.get_string_location() << endl;
    cout << "Where would you like to go?" << endl;
    cout << "Left   Right" << endl;
    cin >> console_navigational_command;

    if(console_navigational_command == "left" || console_navigational_command == "Left" ||
        console_navigational_command == "right" || console_navigational_command == "Right")

    {
    move_user(player_one.get_int_location(), console_navigational_command);
    total_rooms_visited++;
    }

    else if(console_navigational_command == "quit" || console_navigational_command == "Quit")
    {exit(EXIT_SUCCESS);}


    else if(console_navigational_command == "location" || console_navigational_command == "Location")
    {player_one.get_string_location();}

    else if(console_navigational_command == "stats" || console_navigational_command == "Stats")
    {show_all_player_stats(player_one);}


    else if (console_navigational_command == "help" || console_navigational_command == "Help")
        {help_screen( player_in_combat,  class_sel, player_backpack);}
    

    else {help_screen( player_in_combat,  class_sel, player_backpack);}



};