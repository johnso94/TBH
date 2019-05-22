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
    string name;

public:
    PC(string filename)
    {
        temp_hp = stoi(get_value("Player_Stats.txt","temp_hp:"));
        name = get_value("Player_Stats.txt","name:");
        EXP = stoi(get_value("Player_Stats.txt","Exp:"));
        level = stoi(get_value("Player_Stats.txt","level:"));
        hp = 3 * stoi(get_value("Player_Stats.txt","con:")) + stoi(get_value("Player_Stats.txt","level:"));
        atk = stoi(get_value("Player_Stats.txt","atk:"));
        def = stoi(get_value("Player_Stats.txt","def:"));
        cha = stoi(get_value("Player_Stats.txt","cha:"));
        def = stoi(get_value("Player_Stats.txt","def:"));
        wep = stoi(get_value("Player_Stats.txt","wep:"));
    }
    void attack(Enemy &npc, string & is);
    void riposte(Enemy &npc, string & is);
    void heavy_attack(Enemy &npc, string & is);
    void light_attack(Enemy &npc, string & is);
    void fireball(Enemy &npc, string & is);
    void talk(Enemy &npc);
    void level_up();
    void gain_exp(int i)
    {
        EXP += i;
        set_value("Player_Stats.txt", "Exp:", to_string(EXP));
        if (EXP >= 100 * level)
        {
            EXP -= 100 * level;
            level_up();
        }
    }
    void run(Enemy &monster);
    void steal(Enemy &monster, Inventory &inv);
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
    void DIE(){
         string is = get_value("Game.txt","death:");
         cout << is;
    }
    void set_temp_hp();
    void set_hp(){
        set_value("Player_Stats.txt", "hp:", to_string(hp));
    }
    string named(){
        return name;
    }
};

#endif