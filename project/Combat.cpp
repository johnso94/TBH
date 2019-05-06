#include<iostream>
using namespace std;
#include"stats.cpp"
void combat(PC &player, Enemy &monster, string is, Inventory &inv){
    //if the player types attack
    if (is == "attack"){
        player.attack(monster);
        if(monster.get_health()<=0){
            PlaceHolder; //returns the player to the location
            monster.give_wealth(inv);
            monster.give_exp(player);
            monster.die();
        }
        if(player.get_health() <=0){
            PlaceHolder; //here we would incorporate the deathsystem
        }
        monster.action(player);
    }
    if (is == "talk"){
        player.talk(monster);
        if(monster.is_convinced()){
            PlaceHolder; //returns the player to the location
            monster.give_exp(player);
        }
        if(monster.get_health()<=0){
            PlaceHolder; //returns the player to the location
            monster.give_wealth(inv);
            monster.give_exp(player);
            monster.die();
        }
        if(player.get_health<=0){
            PlaceHolder; //here we would incorporate the deathsystem
        }
        monster.action(player);
    }
    if (is == "run"){
        player.run(monster);
        monster.action(player);
    }
}