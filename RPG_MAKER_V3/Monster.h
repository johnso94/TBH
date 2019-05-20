#ifndef _MONSTER_
#define _MONSTER_

#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<fstream>
#include"Util.h"

using namespace std;


class Monster : public Util
{
    string description;
    string name;

    int strength;
    int defence;
    int max_hit_points;
    int current_hp;

public:

    void set_monster_values(map<string,string> event_data);
    string to_str();


};

#endif
