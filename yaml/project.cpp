#include<iostream>
#include"sd_fun.h"
#include <string>
#include"Client.h"
using namespace std;

void screen(){
    add_yaml("boxes.yaml", {{"id", "Screen"}, {"x", 20}, {"y", 20}, {"w", 900}, {"h", 450}, {"back", "white"}, {"border", "black"}, {"borderw", 10}, {"children", "Image_Background, Image_Foreground"}});
    add_yaml("boxes.yaml", {{"id", "TextOutput"}, {"x", 940}, {"y", 20}, {"w", 300}, {"h", 450}, {"back", "white"}, {"border", "black"}, {"borderw", 10}, {"children", "Text_Output"}});
    add_yaml("text.yaml", {{"id", "Output"}});
    add_yaml("input.yaml", {{"id", 1}, {"x", 20}, {"y", 490}, {"w", 1220}, {"h", 30}, {"f", 20}, {"border", "black"}, {"borderw", 5}, {"p", 1}, {"l", 150}});
}

void add_images(ifstream &m) {
    string x, y;
    m >> x >> y;
    add_yaml("image.yaml", {{"id", "Background"}, {"im", x.c_str()}, {"l", 0}, {"w", 880}, {"h", 430}});
    add_yaml("image.yaml", {{"id", "Foreground"}, {"im", y.c_str()}, {"l", 225}, {"w", 430}, {"h", 430}});
}

int main() {
    init();

    if (length_of(yaml) < 50) {
        mem[100] = 0;
//        write_at(mem, 500, "World");
    }

    Client game;
    game.run();

/*
    write_at(mem, 100, "Start"); // Writes info from user to mem
    Range t_range = find_value(yaml, "content:"); // Gets info from user
    write_at(mem, 100, yaml, t_range); // Writes info from user to mem
*/

    yaml[0] = 0;
    screen();
    ifstream file("images.txt");
    add_images(file);

    mem[1] = 0;
    quit();

}