#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <string>
#include "fighter.h"
#include "Inventory.h"

using namespace std;
class PC;

class Enemy:public fighter
{
    bool convinced = 0;
    int CR = 0;
    int gold;
    int EXP;
    string t;
    string title;

public:
    Enemy(string name, int cr, int gp, int Exp, int thp, int str, int tdef)
    {
        hp = thp;
        str = str;
        temp_hp = thp;
        EXP = Exp;
        gold = gp;
        CR = cr;
        title = name;
        def = tdef;
    }

    void give_wealth(Inventory &i);
    void give_exp(PC &p);
    void die();
    void convince();
    bool is_convinced();
    int return_CR();
    int get_hp();
    int AC();
    void reset(){
        temp_hp = hp;
    }
    int total_hp();
    string name(){
        return title;
    }
    void action(PC &pc);
};

#endif