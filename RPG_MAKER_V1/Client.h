#ifndef _NAVIGATOR_
#define _NAVIGATOR_

#include"Util.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include"Location.h"
#include"sd_fun.h"

using namespace std;

class Client : public Util
{
    Location player_location;
    map<string,string> event_data;
    string current_event;
    string game_state;
public:
    Client()
    {
        current_event = get_str_value("Game.txt","Event:");
        event_data = get_data("Events.txt",current_event);
        print_event_to_yaml();
    }
    void set_player_location();
    void set_monster_player_is_fighting();

    // Executing the Game
    void print_event_to_yaml();
    void set_player_battle();
    void navigation();
    void combat();
    void run();
    ~Client(){}
};

#endif