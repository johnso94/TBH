#include "Enemy.h"
#include "PC.h"

void Enemy::give_wealth(Inventory &i)
{
    i.Add_gold(gold);
    i.Add_Inventory(t);
}
void Enemy::give_exp(PC &p)
{
    p.gain_exp(EXP);
}
void Enemy::die() {
    cout << "The " << title << " has died." << endl;
}
void Enemy::convince()
{
    convinced = 1;
}
bool Enemy::is_convinced()
{
    return convinced;
}
int Enemy::return_CR()
{
    return CR;
}
int Enemy::get_hp()
{
    return temp_hp;
}
int Enemy::AC()
{
    int defense = 10 + def;
    return defense;
}
int Enemy::total_hp(){
    return hp;
}
void Enemy::action(PC &pc)
{
     srand(time(0));
     int roll = rand() % 20 + 1;
     if (roll + atk > pc.AC())
     {
         int damage = rand() % 6 + atk;
         pc.take_damage(damage);
         cout << "The " << title << " strikes." << endl;
        cout << "You take " << damage <<" damage." << endl;
    }
    else{
        cout << "The " << title << " misses" << endl;
     }
}