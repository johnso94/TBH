#include"commands.h"
void fill_map(map<string, int> &actions){
    actions["attack"] = 1;
    actions["fight"] = 1;
    actions["strike"] = 1;
    actions["clash"] = 1;
    actions["battle"] = 1;
    actions["combat"] = 1;
    actions["slice"] = 1;
    actions["crush"] = 1;
    actions["stab"] = 1;
    actions["persuade"] = 2;
    actions["talk"] = 2;
    actions["speak"] = 2;
    actions["pacify"] = 2;
    actions["decieve"] = 2;
    actions["communicate"] = 2;
    actions["run"] = 3;
    actions["flee"] = 3;
    actions["escape"] = 3;
    actions["retreat"] = 3;
    actions["desert"] = 3;
    actions["withdraw"] = 3;
    actions["commands"] = 10;
}
void fill_commands(vector<string> &commands){
    commands.push_back("attack");
    commands.push_back("fight");
    commands.push_back("run");
    commands.push_back("commands");
}
