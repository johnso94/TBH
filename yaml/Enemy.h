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
    int Challenge_Rating = 0;
    int gold;
    int EXP;
    string t;
    string title;
    string disposal;
    int blocked = 0;
    int escaped = 0;
    int missed = 0;
public:
    Enemy(string filename)
    {
        temp_hp = stoi(get_value("Game.txt","temp_hp:"));
        title = get_value("Game.txt","title:");
        Challenge_Rating = stoi(get_value("Game.txt","cr:"));
        gold = stoi(get_value("Game.txt","gold:"));
        EXP = stoi(get_value("Game.txt","Exp:"));
        hp = stoi(get_value("Game.txt","hp:"));
        atk = stoi(get_value("Game.txt","atk:"));
        def = stoi(get_value("Game.txt","def:"));
    }

    void give_wealth(Inventory &i);
    void give_exp(PC &p);
    void die();
    void convince();
    bool is_convinced();
    int return_CR();
    int get_hp();
    int AC();
    int total_hp();
    string name(){
        return title;
    }
    void action(PC &pc);
    void display();
    void set_temp_hp();
    void block(){
        blocked = 1;
        cout << "you block the" << title << "'s next attack" << endl;
    }
    void escape(){
        escaped = 1;
    }
    bool fled(){
        return escaped;
    }
    void missed_reset(){
        missed = 0;
    }
    int miss(){
        return missed;
    }
};

#endif