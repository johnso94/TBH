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
    string output = "The ";
    output += title;
    output += " has died.\n";
    output +=  get_value("Game.txt","victory:");
    output += '\n';
    write_at(mem, 99+find_len(100), output.c_str());
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
    return Challenge_Rating;
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
    string output;
     srand(time(0));
     int roll = rand() % 20 + 1;
     if (roll + atk > pc.AC())
     {
         int damage = rand() % 6 + atk;
         if (blocked){
             damage /= 2;
             blocked = 0;
         }
         pc.take_damage(damage, "slashing");
         pc.set_temp_hp();
         output += "The ";
         output += title;
         output += " strikes.\n";
        output += "You take ";
        output += to_string(damage) += " damage.\n";
        write_at(mem, 99+find_len(100), output.c_str());
    }
    else{
        output += "The ";
        output += title;
        output += " misses its attack\n";
        write_at(mem, 99+find_len(100), output.c_str());
        missed = 1;
     }
}

void Enemy::display(){
    string output;
    output +=  "name: ";
    output +=  title;
    output +=  "\nChallenge Rating: ";
    output +=  to_string(Challenge_Rating);
    output +=  "\ngold carried: ";
    output +=  to_string(gold);
    output +=  "\nEXP given:";
    output +=  to_string(EXP);
    output +=  "\nhp: ";
    output +=  to_string(temp_hp) += '/';
    output +=  to_string(hp);
    output +=  "\natk: ";
    output +=  to_string(atk);
    output += "\ndef: ";
    output +=  to_string(def);
    output += '\n';
    string is =  get_value("Game.txt","Description:");
    output += is += '\n';
    write_at(mem, 99+find_len(100), output.c_str());
}

void Enemy::set_temp_hp(){
    set_value("Game.txt", "temp_hp:", to_string(temp_hp));
}