#include "PC.h"
#include "Enemy.h"

void PC::attack(Enemy &monster, string & is)
{
    srand(time(0));
    int roll = rand() % 20 + 1;
    if (roll + atk > monster.AC())
    {
        int damage = rand() % 6 + atk + wep;
        monster.take_damage(damage, is);
        monster.set_temp_hp();
        cout << "You " << is << " the " << monster.name() << endl;
        cout << "It takes " << damage <<" damage." << endl;
    }
    else{
        cout << "Your attack misses" << endl;
    }
}
void PC::talk(Enemy &monster)
{
    srand(time(0));
    int roll = rand() % 20 + 1;
    if (roll + cha > 10 + 5 * (monster.get_hp())/(monster.total_hp()) + monster.return_CR()- (return_level()/4))
    {
        monster.convince();
        string is =  get_value("Game.txt","persuasion:");
        cout << is << endl;
    }
}
void PC::run(Enemy &monster){
    srand(time(0));
    int roll = rand() % 20 + 1;
    if (roll + level/2 > 10 + monster.return_CR()){
        string is =  get_value("Game.txt","run:");
        cout << is << endl;
        monster.escape();
    }
}
void PC::steal(Enemy &monster, Inventory &inv){
    srand(time(0));
    int roll = rand() % 20 + 1;
    if (roll > 10 + monster.return_CR() - return_level()/4){
        string is =  get_value("Game.txt","rob:");
        cout << is << endl;
    }
}
void PC::level_up(){
    string stat;
    cin >> stat;

    stat += ':';
    int point = stoi(get_value("Player_Stats.txt",stat));
    point += 1;
    set_value("Player_Stats.txt", stat, to_string(point));
};
void PC::set_temp_hp(){
    set_value("Player_Stats.txt", "temp_hp:", to_string(temp_hp));
}