#include <iostream>
using namespace std;
#include "fighter.h"
#include "commands.h"
#include "Enemy.h"
#include "PC.h"
#include "Inventory.h"

void round(PC &player, Enemy &monster, string is, Inventory &inv)
{
    map<string,int> actions;
    vector<string> commands;
    fill_map(actions);

    switch (actions[is])
    {
    case 1:
    {
        player.attack(monster, is);
        if (monster.get_hp() <= 0)
        {
            //PlaceHolder returns the player to the location
            monster.give_wealth(inv);
            monster.give_exp(player);
            monster.die();
            break;
        }
        if (player.get_health() <= 0)
        {
            // PlaceHolder here we would incorporate the deathsystem
            cout << "you have died" << endl;
            break;
        }
        monster.action(player);
        break;
    }
    case 2:
    {
        player.talk(monster);
        if (monster.is_convinced())
        {
            //PlaceHolder returns the player to the location
            monster.give_exp(player);
        }
        if (monster.get_hp() <= 0)
        {
            // PlaceHolder returns the player to the location
            monster.give_wealth(inv);
            monster.give_exp(player);
            monster.die();
        }
        if (player.get_health() <= 0)
        {
            //PlaceHolder here we would incorporate the deathsystem
        }
        monster.action(player);
        break;
    }
    case 3:
    {
        {
            player.run(monster);
            monster.action(player);
        }
        break;
    }
    case 10:
    {
        // for (string elem : commands)
        // {
        //     cout << elem << endl;
        // }
        fill_commands(commands);
        for(int i = 0; i<4; i++){
            cout << commands[i] << endl;
        }
        break;
    }
    }
}
void encounter(PC &player, Enemy &monster, Inventory &inv){
    monster.reset();
    while(player.get_hp() >0 && monster.get_hp() > 0){
        string input;
        cin >> input;
        round(player, monster, input, inv);
        cout << "you have " << player.get_hp() << " health"<< endl;
        cout << "the "<< monster.name() << " has " << monster.get_hp() << " health" << endl;
    }
}
int main() {
    ifstream f("Player_Stats.txt");
    PC Aarsanuvf(f);
    Enemy goblin("goblin scout", 0, 0, 0, 10, 0,0);
    Inventory test;
    encounter(Aarsanuvf, goblin, test);
}