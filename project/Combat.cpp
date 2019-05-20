#include <iostream>
using namespace std;
#include "fighter.h"
#include "commands.h"
#include "Enemy.h"
#include "PC.h"
#include "Inventory.h"

void round(PC &player, Enemy &monster, string is, Inventory &inv)
{
    map<string, int> actions;
    vector<string> commands;
    fill_map(actions);

    if (actions.find(is) == actions.end())
    {
        cout << player.named() << " does not know how to " << is << endl;
    }
    else
    {
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
                player.DIE();
                break;
            }
            monster.action(player);
            monster.missed_reset();
            break;
        }
        case 2:
        {
            player.talk(monster);
            if (monster.is_convinced())
            {
                //PlaceHolder returns the player to the location
                monster.give_exp(player);
                break;
            }
            if (monster.get_hp() <= 0)
            {
                // PlaceHolder returns the player to the location
                monster.give_wealth(inv);
                monster.give_exp(player);
                monster.die();
                break;
            }
            if (player.get_health() <= 0)
            {
                player.DIE();
            }
            monster.action(player);
            monster.missed_reset();
            break;
        }
        case 3:
        {
            player.run(monster);
            if (monster.fled())
            {
                break;
            }
            monster.action(player);
            monster.missed_reset();
            if (player.get_health() <= 0)
            {
                player.DIE();
            }
            break;
        }
        case 4:
        {
            player.steal(monster, inv);
            monster.action(player);
            monster.missed_reset();
            if (player.get_health() <= 0)
            {
                player.DIE();
            }
            break;
        }
        case 5:
        {
            monster.block();
            monster.action(player);
            monster.missed_reset();
            if (player.get_health() <= 0)
            {
                player.DIE();
            }
            break;
        }
        case 6:
        {
            monster.display();
            monster.action(player);
            monster.missed_reset();
            if (player.get_health() <= 0)
            {
                player.DIE();
            }
            break;
        }
        case 7:
        {
            monster.action(player);
            if (player.get_health() <= 0)
            {
                player.DIE();
            }
            if (monster.miss())
            {
                player.riposte(monster, is);
            }
            monster.missed_reset();
            break;
        }
        case 8:
        {
            player.heavy_attack(monster, is);
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
                player.DIE();
                break;
            }
            monster.action(player);
            monster.missed_reset();
            break;
        }
        case 9:
        {
            player.light_attack(monster, is);
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
                player.DIE();
                break;
            }
            monster.action(player);
            monster.missed_reset();
            break;
        }
        case 10:
        {
            // for (string elem : commands)
            // {
            //     cout << elem << endl;
            // }
            fill_commands(commands);
            for (int i = 0; i < 4; i++)
            {
                cout << commands[i] << endl;
            }
            break;
        }
        case 11:
        {
            player.fireball(monster, is);
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
                player.DIE();
                break;
            }
            monster.action(player);
            monster.missed_reset();
            break;
        }
        }
    }
}
void encounter(PC &player, Enemy &monster, Inventory &inv)
{
    monster.reset();
    player.reset();
    while (player.get_hp() > 0 && monster.get_hp() > 0 && (monster.is_convinced() == 0) && (monster.fled() == 0))
    {
        string input;
        cin >> input;
        round(player, monster, input, inv);
        cout << endl;
        cout << "you have " << player.get_hp() << " health" << endl;
        cout << "the " << monster.name() << " has " << monster.get_hp() << " health" << endl;
    }
    string Back_to = get_value("Game.txt", "Back_to:");
    set_value("Game.txt", "Event:", Back_to);
}
int main()
{
    PC Aarsanuvf("Player_Stats.txt");
    Enemy monster("Game.txt");
    Inventory test;
    encounter(Aarsanuvf, monster, test);
    // Aarsanuvf.level_up();
}