#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <map>

using namespace std;

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


    


int main() {
    GameMap cartograph; // this will be in global

    vector<Room*> arena;
    vector <string> game_locations = {"Holding Cell", "Arena Room 1", "Arena Room 2", "Arena Room 3", "Arena Room 4", "Arena Room 5", 
                                "Arena Room 6", "Arena Room 7", "Arena Room 8", "Arena Room 9", "Jailor's Room"};
    for (int i = 0; i < game_locations.size(); i++){
        auto* const location = cartograph.create_room_node(i, game_locations.at(i));
        arena.push_back(location);
    }

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


//vertex 3 degree sequence is 4
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
cartograph.create_edge(*arena.at(8), *arena.at(0));
cartograph.create_edge(*arena.at(8), *arena.at(9));

vector<Room*> test_first_connect = cartograph.get_connected_rooms(*arena.at(0));
Room *left_room = test_first_connect[0];
Room *right_room = test_first_connect[1];

string left_room_name = (*left_room).get_node_name();
int left_room_designation = (*left_room).get_node_designation();


string right_room_name = (*right_room).get_node_name();
int right_room_designation = (*right_room).get_node_designation();

cout << "The left most room to the current room is " << left_room_name << endl ;
cout << "The left most room to the current room has a desgination of " << left_room_designation << endl ;
cout << "The right most room to the current room is " << right_room_name << endl ;
cout << "The right most room to the current room has a desgination of " << right_room_designation << endl ;


    return 0;
}