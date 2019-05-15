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
    void take_damage(int i)
    {
        temp_hp -= i;
    }
};

#endif