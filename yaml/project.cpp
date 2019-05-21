#include<iostream>
#include<fstream>
#include"sd_fun.h"
#include <string>
using namespace std;

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

int main() {
    init();

    if (length_of(yaml) < 50) { // Sets up the game.
        mem[100] = 0;
    }

    yaml[0] = 0; // Gets yaml from server then sends an updated screen
    screen();
    ifstream file("images.txt");
    add_images(file);

    mem[1] = 0;
    quit();

}