#include"Rectangle.h"
#include"Circle.h"

#include<fstream>
#include<iostream>
#include"sd_fun.h"
#include"Rectangle.h"
#include"Circle.h"
#include <string>

#include"Client.h"
using namespace std;


void screen() { // Makes a screen
    Point2 pview, pobox, pinput;
    Color white, black;
    white.red = white.blue = white.green = 255; // Color white for background
    black.red = black.blue = black.green = 0; // Color black for border
    pview.x = 20; pview.y = 20; // Point2's for view
    pobox.x = 940; pobox.y = 20; // Point2's for pobox
    pinput.x = 20; pinput.y = 490; // Point2's for pinput
    Rectangle view(pview, 900, 450); // Makes the view screen
    Rectangle obox(pobox, 300, 450); // Makes the output box
    Rectangle input(pinput, 1220, 30); // Makes the input box
    obox.drawBorder(10, white, black);
    append(yaml, "  children: [Text_output]\n");
    add_yaml("text.yaml", {{"id", "output"}});
    input.drawText_input(1);
    view.drawBorder(10, white, black);
    append(yaml, "  children: [Image_1, Image_2]\n");
}

string find_string(int pos) { // returns the string of chars starting at mem[500].
    string x = "";
    int i = 0;
    while (mem[(i++)+pos] != 0);
    for (int j = 1; j < i; j++) {
        x += mem[j+pos-1];
    }
    return x;
}



int main() {
    init();

    if (length_of(yaml) < 50) {
        mem[100] = 0;
        write_at(mem, 500, "Universe");
    }

    // string display = find_string(500);
    // write_at(mem,100,display.c_str());

    // User Input 
    // game.run(input)
    // 

    Client game;
    string display_text = game.run();
        

//    write_at(mem,100,display_text.c_str());
//    game.run(); // Input is used twice etc 1 = Red Star to Red Sea

/*
    char testing[t_range.len];
    write_at(testing, 0, yaml, t_range);
    string z;
    z = testing;
*/

    yaml[0] = 0;
    screen();
    add_yaml("image.yaml", {{"id", 1}, {"im", "wood.png"}, {"l", 0}, {"w", 880}, {"h", 430}});
    add_yaml("image.yaml", {{"id", 2}, {"im", "cat.png"}, {"l", 225}, {"w", 430}, {"h", 430}});

    mem[1] = 0;
    quit();

}