#include<iostream>
#include"sd_fun.h"
#include"Rectangle.h"
#include"Circle.h"
using namespace std;

void text_box() {
    append(yaml, "Text_output:\n");
    append(yaml, "  style:\n");
    append(yaml, "    marginLeft: 5\n");
    append(yaml, "    marginTop: 5\n");
    append(yaml, "    color: black\n");
    append(yaml, "    fontSize: 20\n");
    append(yaml, "  pos: 100\n");
    append(yaml, "  len: 900\n");
}

/*
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
    text_box();
    input.drawText_input(1);
    view.drawBorder(10, white, black);
    append(yaml, "  children: [Image_1]\n");
}
*/

void screen(){
    add_yaml("boxes.yaml", {{"id", 1}, {"x", 20}, {"y", 20}, {"w", 900}, {"h", 450}, {"back", "white"}, {"border", "black"}, {"borderw", 10}, {"child", 1}});
}

int main() {
    init();

//    if (length_of(yaml) < 50) {
//        mem[100] = 0;
//    }

//    write_at(mem, 100, "Description"); // Writes info from user to mem
//    Range t_range = find_value(yaml, "content:"); // Gets info from user
//    write_at(mem, 100, yaml, t_range); // Writes info from user to mem

    yaml[0] = 0;
    screen();
//    add_yaml("image.yaml", {{"id", 1}, {"im", "cat.png"}, {"w", 880}, {"h", 430}});

//    mem[1] = 0;
    quit();
}