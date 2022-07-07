#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
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
        int strength = 25 ; 
        int defense = 20;
        int dexterity = 15 ;
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
        void display_health () {
            cout << "You have "<< health << "HP" << flush;

        }
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


        //defense
        int get_defense(){
            return defense;

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
            cout << "You are in" << string_location << flush;

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

        bool stil_alive(int hp)
        {
            if  (hp > 0) true;
            else false;
        }


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


class ParseUserInput
/*
CLASS DEFINITION
 Take console input from user and search for game keywords. 
 Based on console input, do x action.
 see if one method can do a try/catch for user input.
 can also be a struct with a separate function and case staement if a class is too complicated.
 */
{};



struct inventory{
int potions = 10;
bool shield_equipped = false;
bool sword_equipped = false;

};



/*

=============================================================================================================================================================================


                                                                    HELPER   FUNCTIONS


FUNCTIONS GENERAL USAGE IN GAME


Functions will be used in game to modify class objects because they are in global scope.
        i.e. void function_runtime_version_get_player_name(){
            string user_input;
            cout << "What's your name, brave warrior" << flush
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

//Player Helper Functions

void class_choice()
{
    cout << "Please select your class:" << flush;




};

auto combat()
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




{};


// INVENTORY FUNCTIONS

void use_potion(){
    cout << "10 Health added";
    //inventory object potions -= 1
    //player.get_health()
    //player.set_health() + 10
    
};

void confirm_armor_equip(){
    cout << "Shield Equipped!";
    //inventory object shield_equipped = true
    //player.get_defense()
    //player.set_defense() + 10
    
};


void confirm_sword_equip(){
    cout << "Sword equipped! Slay them all.";
    //inventory object sword_equipped = true
    //player.get_attack()
    //player.set_attack() + 10
    
};


// HOUSEKEEPING FUNCTIONS

void help_screen(bool combat)
/*FUNCTION DEFINITION
Output text to console to show user valid commands. 
Based on expression combat, which is a global variable, set to indicate combat loop

*/
 {


    if (!combat)

    {cout << flush;
        cout << "Valid combat commands are the following:" << flush;

    }
    
    else {cout << flush;
        cout << "Valid navigational commands are the following:" << flush;
        cout << "Left, Right, Straight" << flush;
        cout << "To quit the game, press quit." << flush;};


};

void welcome_screen()
/*
FUNCTION DEFINITION
create file with text to display welcome message to user
open file with stream and display the help_screen()
ASCII art for Title ??? Saved as png file and also called with file_stream
REFERENCETHIS C++ for the Absolute Beginner, pg 277 */

{};


// TODO move classes into separate .h files once build phase complete.



/*
=================================================================================================================================================================================================

                                                MAIN GAME

=================================================================================================================================================================================================



*/

#include <iostream>
using namespace std;



//GLOBALS
bool game_running = true;
bool player_in_combat = false;
bool user_has_key = false;



//FUNCTION FORWARD DECLARATIONS




//GAMEPLAY

int main(void){








return 0; }




