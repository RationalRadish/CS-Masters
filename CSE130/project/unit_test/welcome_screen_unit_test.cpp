#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <map>
#include <fstream>
using namespace std;

typedef struct Inventory{
int potions = 4;
bool armor_equipped = false;
bool weapon_equipped = false;

} Inventory;


void help_screen(bool combat_flag, int class_selection, Inventory bag)
/*FUNCTION DEFINITION
Output text to console to show user valid commands. 
Based on expression combat, which is a global variable, set to indicate combat loop
*/
 {

    if (combat_flag)
    {   cout << "Valid combat commands are the following:" << endl;
        if(!bag.weapon_equipped) cout << "Punch    Drink Potion" << endl;
        if (class_selection == 1 && bag.weapon_equipped)
        cout << "Slash  Drink Potion" << endl;
        else if (class_selection == 2 && bag.weapon_equipped)
        cout << "Fireball   Drink Potion" << endl;
        else if (class_selection == 3 && bag.weapon_equipped)
        cout << "Stab       Drink Potion" << endl;}
    
    else {  cout << "Valid navigational commands are the following:" << endl;
            cout << "Left   Right" << endl;
            cout << "To quit the game, press quit." << endl;
            cout << "To check your inventory, press display equipment" << endl;
            cout << "To check your stats, press stats." << endl;
            cout << "To check your location, press location" << endl;}
            cout << "If you would like to see these options again, press help" << endl;


};

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

int main(){
    welcome_screen();



    return 0;
}