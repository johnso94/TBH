#include<iostream>
#include<fstream>
#include<iostream>
#include <string>

#include"sd_fun.h"
#include"Rectangle.h"
#include"Client.h"
#include"Util.h"
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
    }

    Client game;
    game.run();

    Util util;
    string foreground = util.get_str_value("Game.txt","Foreground:");
    string background = util.get_str_value("Game.txt","Background:");
    
    if(foreground.size() == 0)
    {
        foreground = "nothing.png";
    }
    if(background.size() == 0)
    {
        background = "white.png";
    }

    yaml[0] = 0;
    screen();
    add_yaml("image.yaml", {{"id", 1}, {"im",background.c_str()}, {"l", 0}, {"w", 880}, {"h", 430}});
    add_yaml("image.yaml", {{"id", 2}, {"im", foreground.c_str()}, {"l", 225}, {"w", 430}, {"h", 430}});

    mem[1] = 0;
    quit();

}
