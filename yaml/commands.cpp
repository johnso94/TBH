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
    actions["steal"] = 4;
    actions["loot"] = 4;
    actions["rob"] = 4;
    actions["pilfer"] = 4;
    actions["swipe"] = 4;
    actions["take"] = 4;
    actions["defend"] = 5;
    actions["shield"] = 5;
    actions["block"] = 5;
    actions["examine"] = 6;
    actions["check"] = 6;
    actions["look"] = 6;
    actions["riposte"] = 7;
    actions["couterattack"] = 7;
    actions["counter"] = 7;
    actions["heavy attack"] = 8;
    actions["light attack"] = 9;
    actions["commands"] = 10;
    actions["fireball"] = 11;
    actions["imolate"] = 11;
    actions["BURN!"] = 11;
    actions["drink"] = 12;
}
void fill_commands(vector<string> &commands){
    commands.push_back("attack");
    commands.push_back("fight");
    commands.push_back("run");
    commands.push_back("steal");
    commands.push_back("defend");
    commands.push_back("examine");
    commands.push_back("counter");
    commands.push_back("heavy attack");
    commands.push_back("light attack");
    commands.push_back("fireball");
    commands.push_back("commands");
}
