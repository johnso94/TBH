#include<iostream>
using namespace std;
#include<vector>
#include<string>
#include"Inventory.h"
#include<cstdlib>
#include<ifstream>

struct PlaceHolder;
struct stats{
    int hp;
    int str;
    int dex;
    int cha;
    int temp_hp;
    int intel;
};
class NPC{
    protected:
    stats st;
    public:
    int NPC::get_health(){
        return st.temp_hp;
    }
    void NPC::take_damage(int i){
        st.temp_hp -= i;
    }
    int NPC::AC(){
        int def = 10 + st.dex;
        return def;
    }
    int return_int(){
        return st.intel;
    }
};
class PC{
    stats st;
    int wep;
    int EXP;
    int level;
    public:
    PC(ifstream &is){
        is >> st.hp;
        is >> st.str;
        is >> st.dex;
        is >> st.cha;
        is >> st.temp_hp;
        is >> st.intel;
        is >> wep;
        is >> EXP;
        is >> level;
    }
    void attack(Enemy &npc){
        srand(time(0));
        int roll = rand() % 20 + 1;
        if (roll + st.str > npc.AC()){
            int damage = rand() % 6 + st.str + wep;
            npc.take_damage(damage);
        }
    }
    void talk(Enemy &npc){
        srand(time(0));
        int roll = rand() % 20 + 1;
        if (roll + st.cha > 10 + npc.return_CR() + npc.return_int()){
            npc.convince();
        }
    }
    void level_up();
    void gain_exp(int i){
        EXP += i;
        if (EXP >= 100 * level){
            EXP -= 100* level;
            level++;
            level_up();
        }
    }
    void run(NPC &npc){}
    int get_health(){
        return st.temp_hp;
    }
    void PC::take_damage(int i){
        st.temp_hp -= i;
    }
};
class Enemy:public NPC{
    bool convinced = 0;
    int CR=0;
    int gold;
    int EXP;
    string t;
    public:
    Enemy(int cr, int gp, int Exp, int hp, int str, int dex, int cha, int temp_hp, int intel){
        st.hp = hp;
        st.str = str;
        st.dex = dex;
        st.cha = cha;
        st.temp_hp = temp_hp;
        st.intel = intel;
        EXP = Exp;
        gold = gp;
        CR = cr;

    }
    void action(PC &p){
        
    }
    void give_wealth(Inventory &i){
        i.Add_gold(gold);
        i.Add_Inventory(t);
    }
    void give_exp(PC &p){
        p.gain_exp(EXP);
    }
    void die(){}
    void take_damage(int i){}
    void convince(){
        convinced = 1;
    }
    bool is_convinced(){
        return convinced;
    }
    int return_CR(){
        return CR;
    }
};