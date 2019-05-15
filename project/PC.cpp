#include "PC.h"
#include "Enemy.h"

void PC::attack(Enemy &monster, string & is)
{
    srand(time(0));
    int roll = rand() % 20 + 1;
    if (roll + atk > monster.AC())
    {
        int damage = rand() % 6 + atk + wep;
        monster.take_damage(damage);
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
        cout << "Congratulations! Through flawless reasoning you convince the goblin ";
        cout << "that it would do better  waiting for a weaker traveler ";
        cout << "to pass by. The goblin lets you go and shares some gold for the advice." <<endl;
    }
}
void PC::run(Enemy &monster){
    srand(time(0));
    int roll = rand() % 20 + 1;
    if (roll > 10 + monster.return_CR() - return_level()/4){
        cout << "Congratulatoins! Like a wuss you have somehow escaped one puny goblin who, in your wussness, ";
        cout << "you did not believe you could defeat. Again, congratdulation!" << endl;
    }
}
void PC::level_up(){};