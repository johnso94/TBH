#ifndef _NAVIGATOR_
#define _NAVIGATOR_

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>

#include"Location.h"
#include"Util.h"
#include"Monster.h"
#include"sd_fun.h"

using namespace std;

class Client : public Util
{
    Location current_location;
    Monster current_monster;

    map<string,string> event_data;
    string current_event;
    string game_state;
public:
    Client()
    {
        current_event = get_str_value("Game.txt","Event:");
        print_event_to_yaml();
    }

    void set_monster_player_is_fighting();

    // Executing the Game
    void run();
    void select();
    void print_event_to_yaml();
    void navigation();
    void combat();
    ~Client(){}
};

#endif