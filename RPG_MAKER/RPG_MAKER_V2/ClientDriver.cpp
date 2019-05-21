#include"Client.h"


int main(){

    Client game;

    string current_event = game.get_value("Game.txt","Event:");
    
    game.run(current_event);

    return 0;
}