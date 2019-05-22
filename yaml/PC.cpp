#include "PC.h"
#include "Enemy.h"
#include"sd_fun.h"

int find_len(int pos) 
{ // returns the pos of a string of chars starting at mem[pos].
    int i = 0;
    while (mem[(i++)+pos] != 0);
    return i;
}

string get_yaml_input() 
{
    string str_input;
    Range t_range = find_value(yaml, "content:");
    char testing[t_range.len];
    write_at(testing,0,yaml,t_range);
    str_input = testing;
    return str_input;
}

void PC::attack(Enemy &monster, string & is)
{
    string output;
    srand(time(0));
    int roll = rand() % 20 + 1;
    if (roll + atk > monster.AC())
    {
        int damage = rand() % 6 + atk + wep;
        monster.take_damage(damage, is);
        monster.set_temp_hp();
        output += "You ";
        output += is += " the ";
        output += monster.name() += '\n';
        write_at(mem, 99+find_len(100), output.c_str());
    }
    else{
        output += "Your attack misses\n";
        write_at(mem, 99+find_len(100), output.c_str());
    }
}
void PC::riposte(Enemy &monster, string & is)
{
    string output;
    srand(time(0));
    int roll = rand() % 20 + 1;
    if (roll + 2*atk > monster.AC())
    {
        int damage = rand() % 6 + 2 * atk + wep;
        monster.take_damage(damage, is);
        monster.set_temp_hp();
        output += "You counter the ";
        output += monster.name() += "'s attack.\n";
        output += "It takes ";
        output += to_string(damage);
        output += " damage.\n";
        write_at(mem, 99+find_len(100), output.c_str());
    }
    else{
        output += "Your attack misses\n";
        write_at(mem, 99+find_len(100), output.c_str());
    }
}
void PC::heavy_attack(Enemy &monster, string & is){
    string output;
    srand(time(0));
    int roll = rand() % 20 + 1;
    if (roll > monster.AC())
    {
        int damage = rand() % 6 + 2 * (atk) + wep;
        monster.take_damage(damage, is);
        monster.set_temp_hp();
        output += "You bring the full wieght of your blade down upon the ";
        output += monster.name() += ".\n";
        output += "It takes ";
        output += to_string(damage);
        output += " damage.\n";
        write_at(mem, 99+find_len(100), output.c_str());
    }
    else{
        output += "Your attack misses";
        write_at(mem, 99+find_len(100), output.c_str());
    }
}
void PC::light_attack(Enemy &monster, string & is){
    string output;
    srand(time(0));
    int roll = rand() % 20 + 1;
    if (roll + 2 * atk > monster.AC())
    {
        int damage = rand() % 6 + wep;
        monster.take_damage(damage, is);
        monster.set_temp_hp();
        output += "You nimbly slice at the ";
        output += monster.name() += ".\n";
        output += "It takes ";
        output += to_string(damage);
        output += " damage.\n";
        write_at(mem, 99+find_len(100), output.c_str());
    }
    else{
        output += "Your attack misses\n";
        write_at(mem, 99+find_len(100), output.c_str());
    }
}
void PC::fireball(Enemy &monster, string & is){
    string output;
    srand(time(0));
    int roll = rand() % 20 + 1;
    if (roll + intel> monster.AC())
    {
        int damage = (2 * (rand() % 6)) + intel;
        monster.take_damage(damage, is);
        monster.set_temp_hp();
        output += "You ";
        output += is;
        output += " the ";
        output += monster.name() += '\n';
        output += "It takes ";
        output += to_string(damage);
        output += " damage.\n";
        write_at(mem, 99+find_len(100), output.c_str());
    }
    else{
        output += "Your attack misses\n";
        write_at(mem, 99+find_len(100), output.c_str());
    }
}
void PC::talk(Enemy &monster)
{
    string output;
    srand(time(0));
    int roll = rand() % 20 + 1;
    if (roll + cha > 10 + 5 * (monster.get_hp())/(monster.total_hp()) + monster.return_CR()- (return_level()/4))
    {
        monster.convince();
        output =  get_value("Game.txt","persuasion:");
        output += '\n';
        write_at(mem, 99+find_len(100), output.c_str());
    }
}
void PC::run(Enemy &monster){
    srand(time(0));
    int roll = rand() % 20 + 1;
    if (roll + level/2 > 10 + monster.return_CR()){
        string output =  get_value("Game.txt","run:");
        output += '\n';
        write_at(mem, 99+find_len(100), output.c_str());
        monster.escape();
    }
}
void PC::steal(Enemy &monster, Inventory &inv){
    srand(time(0));
    int roll = rand() % 20 + 1;
    if (roll > 10 + monster.return_CR() - return_level()/4){
        string output =  get_value("Game.txt","rob:");
        output += '\n';
        write_at(mem, 99+find_len(100), output.c_str());
    }
}
void PC::level_up(){
    string output;
    level ++;
    string stat;
    output = "Type in stat to level up\n";
    write_at(mem, 99+find_len(100), output.c_str());
    while(stat != "con" && stat != "atk" && stat != "def" && stat != "cha" && stat != "intel"){
        stat = get_yaml_input();
        if (stat != "con" && stat != "atk" && stat != "def" && stat != "cha" && stat != "intel")
            output = "Error, wrong message.\n";
            write_at(mem, 99+find_len(100), output.c_str());
    }

    stat += ':';
    int point = stoi(get_value("Player_Stats.txt",stat));
    point += 1;
    set_value("Player_Stats.txt", stat, to_string(point));
    set_value("Player_Stats.txt", "level:", to_string(level));
}

void PC::set_temp_hp(){
    set_value("Player_Stats.txt", "temp_hp:", to_string(temp_hp));
}

void PC::drink_potion() {
    reset();
    potion -= 1;
    set_value("Player_Stats.txt", "potion:", to_string(potion));
}