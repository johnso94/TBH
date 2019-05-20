#include"Monster.h"


void Monster::set_monster_values(map<string,string> event_data)
{
    try
    {
        strength = stoi(event_data["Str"]);
        defence = stoi(event_data["Def"]);
        max_hit_points = stoi(event_data["Hp"]);
        current_hp = get_int_value("Game.txt","Current Hp:");
    }
    catch(const std::exception& e)
    {
        cerr << e.what() << '\n';
    }

    name = event_data["Name"];
    string background = event_data["Background"];
    string foreground = event_data["Foreground"];

    set_value("Game.txt","Events:",name);
    set_value("Game.txt","Foreground:",foreground);
    set_value("Game.txt","Background:",background);
    description = event_data["Description"];
}

string Monster::to_str()
{

    /*  Creates the Following string

        ### Name ###

        Location Description

        [1] Attack
        [2] Run

    */

    string display = "";
    display.append("\n### " + name + " ###\n");
    display.append("\n" + description + "\n");
    display.append("\nStrength: "+ to_string(strength));
    display.append("\nDefence: "+ to_string(defence));
    display.append("\nHp: "+ to_string(current_hp)+ "\n");
    display.append("\n[1] Attack");
    display.append("\n[2] Run");
    return display;
}