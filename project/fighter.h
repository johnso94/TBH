#ifndef _FIGHTER_
#define _FIGHTER_

#include <iostream>
using namespace std;
#include <vector>
#include <string>
#include "Inventory.h"
#include <cstdlib>
#include <fstream>
struct PlaceHolder;
extern void set_value(string filename, string key, string value);
extern void cut_spaces_off_ends(string &str);
extern string get_value(string filename, string _key);
class fighter
{
protected:
    int hp;
    int atk;
    int def;
    int temp_hp;
public:

    int get_hp()
    {
        return hp;
    }
    virtual void take_damage(int i, string is)
    {
        temp_hp -= i;
    }
    void reset(){
        temp_hp = hp;
        set_value("Game.txt","temp_hp:", to_string(hp));
    }
};


#endif