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
vector<string> nearby_locations;
vector<Location> World;
map<string,Location> str_to_Location;
public:
    Client()
    {
        print_to_yaml(get_display_text());
    }
    void run();
    vector<string> get_nearby_locations(string location_name, vector<Location> World);
    vector<Location> Get_All_Locations();
    string get_display_text();
    ~Client(){}


    // Executing the Game
};

#endif