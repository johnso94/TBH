#include <iostream>
#include <fstream>
#include <string>
#include "sd_fun.h"
#include "fighter.h"
#include "commands.h"
#include "Enemy.h"
#include "PC.h"
#include "Inventory.h"
using namespace std;

int find_len2(int pos) 
{ // returns the pos of a string of chars starting at mem[pos].
    int i = 0;
    while (mem[(i++)+pos] != 0);
    return i;
}

// Gets user input from yaml
string get_yaml_input2() 
{
    string str_input;
    Range t_range = find_value(yaml, "content:");
    if (t_range.len == -1) {
        return "";
    } else {
        char testing[t_range.len];
        write_at(testing,0,yaml,t_range);
        str_input = testing;
        return str_input;
    }
}

void screen(){ // Makes the basic Screen
    add_yaml("boxes.yaml", {{"id", "Screen"}, {"x", 20}, {"y", 20}, {"w", 800}, {"h", 450}, {"back", "white"}, {"border", "black"}, {"borderw", 10}, {"children", "Image_Background, Image_Foreground"}});
    add_yaml("boxes.yaml", {{"id", "TextOutput"}, {"x", 840}, {"y", 20}, {"w", 400}, {"h", 450}, {"back", "white"}, {"border", "black"}, {"borderw", 10}, {"children", "Text_Output"}});
    add_yaml("text.yaml", {{"id", "Output"}});
    add_yaml("input.yaml", {{"id", 1}, {"x", 20}, {"y", 490}, {"w", 1220}, {"h", 30}, {"f", 20}, {"border", "black"}, {"borderw", 5}, {"p", 1}, {"l", 150}});
}

void add_images(ifstream &m) { // Sets images for yaml
    string x, y;
    m >> x >> y;
    add_yaml("image.yaml", {{"id", "Background"}, {"im", x.c_str()}, {"l", 0}, {"w", 780}, {"h", 430}});
    add_yaml("image.yaml", {{"id", "Foreground"}, {"im", y.c_str()}, {"l", 225}, {"w", 330}, {"h", 430}});
}

// Starts a round of combat
void round(PC &player, Enemy &monster, string is, Inventory &inv)
{
    string output;
    map<string, int> actions;
    vector<string> commands;
    fill_map(actions);
    mem[100] = 0;
    if (actions.find(is) == actions.end())
    {
        output += player.named() += " does not know how to ";
        output += is += '\n';
        write_at(mem, 99+find_len(100), output.c_str());
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
            monster.action(player);
            monster.missed_reset();
            if (player.get_health() <= 0)
            {
                // PlaceHolder here we would incorporate the deathsystem
                player.DIE();
                break;
            }
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
            monster.action(player);
            monster.missed_reset();
            if (player.get_health() <= 0)
            {
                player.DIE();
            }
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
            for (unsigned int i = 0; i < commands.size(); i++)
            {
                output = commands[i];
                output += '\n';
                write_at(mem, 99+find_len(100), output.c_str());
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
        case 12:
        {
            if (player.get_potion() > 0) {
                player.drink_potion();
                if (monster.get_hp() <= 0)
                {
                    //PlaceHolder returns the player to the location
                    monster.give_wealth(inv);
                    monster.give_exp(player);
                    monster.die();
                    break;
                }
                monster.action(player);
                monster.missed_reset();
                if (player.get_health() <= 0)
                {
                    // PlaceHolder here we would incorporate the deathsystem
                    player.DIE();
                    break;
                }
                }
                else {
                write_at(mem, 99+find_len(100), "You have no potions to drink.");
                }
            break;
        }
        }
    }
}

// Starts a combat encounter
void encounter(PC &player, Enemy &monster, Inventory &inv)
{
    if (mem[600] == 0) {
        monster.reset(); // Figure out a set-up
        player.reset();
        mem[600] = 1;
    }
    if (player.get_hp() > 0 && monster.get_hp() > 0 && (monster.is_convinced() == 0) && (monster.fled() == 0)) 
    {
        string output;
        string input;
        input = get_yaml_input2();
        round(player, monster, input, inv);
        if (player.get_hp() > 0 && monster.get_hp() > 0) {
            output += '\n';
            output += "You have ";
            output += to_string(player.get_hp());
            output += " health.\n";
            output += "The ";
            output += monster.name();
            output += " has ";
            output += to_string(monster.get_hp());
            output += " health.";
            write_at(mem, 99+find_len(100), output.c_str());
        }
    } else {
        string output = "Combat end"; // Testing only
        write_at(mem, 100, output.c_str()); // Testing only

        // NAV stuf here

        mem[600] = 0;
    }
}

void new_game() { // Resets Player_Stats.txt to base and the location to the begining location.
    ofstream file;
    file.open("Player_Stats.txt");
    file << "name: \nhp: 12\ncon: 3\natk: 3\ndef: 3\ncha: 2\ntemp_hp: 12\nintel: 1\nwep: 1\nExp: 1\nlevel: 1\npotion: 3\nfireball: 0\n";
    file.close();
    // Set begining location.
}

void character_name() { // Gets a name from the user for their character
    write_at(mem, 100, "Type in your character's name."); // Testing only
    string name = get_yaml_input2();
    set_value("Player_Stats_Test.txt", "name:", name);
}

void setup_monster() { // Sets up the template for a monster in Game.txt
    ofstream file;
    file.open("Game.txt");
    file << "temp_hp: \ntitle: \ncr: \ngold: \nExp: \nhp: \natk: \ndef: \n\nDescription: \n\nvictory: \n\nPersuasion: \n\nrun: \n\nrob: \n\ndeath: \n";
    file.close();
}

void make_monster(string mfile) { // Puts information about a monster into Game.txt
    int temp_hp = stoi(get_value(mfile,"temp_hp:"));
    string title = get_value(mfile,"title:");
    int cr = stoi(get_value(mfile,"cr:"));
    int gold = stoi(get_value(mfile,"gold:"));
    int Exp = stoi(get_value(mfile,"Exp:"));
    int hp = stoi(get_value(mfile,"hp:"));
    int atk = stoi(get_value(mfile,"atk:"));
    int def = stoi(get_value(mfile,"def:"));
    set_value("Game_Test.txt", "temp_hp:", to_string(temp_hp));
    set_value("Game_Test.txt", "title:", title);
    set_value("Game_Test.txt", "cr:", to_string(cr));
    set_value("Game_Test.txt", "gold:", to_string(gold));
    set_value("Game_Test.txt", "Exp:", to_string(Exp));
    set_value("Game_Test.txt", "hp:", to_string(hp));
    set_value("Game_Test.txt", "atk:", to_string(atk));
    set_value("Game_Test.txt", "def:", to_string(def));
}

int main() {
    init();
    if (length_of(yaml) < 50) { // Sets up the game.
        mem[100] = 0;
        mem[600] = 0;
    }

//    setup_monster();
//    make_monster("Allosaurus.txt");

//    new_game();
//    character_name();
//    god_mode();
//    if(state == "NAV")
//        func()

//    if(state = "COMBAT")
//    {
/*
        PC Aarsanuvf("Player_Stats_Test.txt");
        Enemy monster("Game.txt");
        Inventory test;
        encounter(Aarsanuvf, monster, test);
        //Aarsanuvf.level_up();
*/
//    }
    if (get_yaml_input2() == "god mode") { // Cheat to be super powerful in game.
            set_value("Player_Stats.txt", "def:", "1000");
            set_value("Player_Stats.txt", "con:", "1000");
            set_value("Player_Stats.txt", "atk:", "1000");
            set_value("Player_Stats.txt", "level:", "1000");
            write_at(mem, 100, "You have activated god mode. There is no going back.");
    }

    if (get_yaml_input2() == "quit") { // Exit condition
            exit(EXIT_SUCCESS);
    }




    yaml[0] = 0; // Gets yaml from server then sends an updated screen
    screen();
    ifstream file("images.txt");
    add_images(file);

    mem[1] = 0;
    quit();

}