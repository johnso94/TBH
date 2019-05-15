#ifndef _PC_H_
#define _PC_H_

#include "fighter.h"

class Enemy;

class PC:public fighter
{
    int cha;
    int intel;
    int wep;
    int EXP;
    int level;

public:
    PC(ifstream &is)
    {
        is >> hp;
        is >> atk;
        is >> def;
        is >> cha;
        is >> temp_hp;
        is >> intel;
        is >> wep;
        is >> EXP;
        is >> level;
    }
    void attack(Enemy &npc, string & is);
    void talk(Enemy &npc);
    void level_up();
    void gain_exp(int i)
    {
        EXP += i;
        if (EXP >= 100 * level)
        {
            EXP -= 100 * level;
            level++;
            level_up();
        }
    }
    void run(Enemy &npc);
    int get_health()
    {
        return temp_hp;
    }
    int return_level(){
        return level;
    }
    int get_hp(){
        return temp_hp;
    }
    int AC(){
        return def;
    }
};

#endif