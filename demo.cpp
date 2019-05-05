#include<iostream>
#include"sd_fun.h"
#include"Rectangle.h"
#include"Circle.h"
using namespace std;

void text_box(char c, int pos) {
    append(yaml, "Text_", c, ":\n");
    append(yaml, "  style:\n");
    append(yaml, "    marginLeft: 5\n");
    append(yaml, "    marginTop: 5\n");
    append(yaml, "    color: black\n");
    append(yaml, "    fontSize: 20\n");
    append(yaml, "  pos: ", pos, "\n");
    append(yaml, "  len: 900\n");
}

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
    view.drawBorder(10, white, black);
    obox.drawBorder(10, white, black);
    append(yaml, "  children: [Text_97]\n");
    input.drawText_input(50);
    text_box('a', 500);
}

void npcPicture() {
    Point2 pview;
    Color purple;
    purple.red = purple.blue = 100; purple.green = 0;
    pview.x = 450; pview.y = 220; // Point2's for view
    Rectangle view(pview, 100, 200);
    view.setColor(purple);
    view.drawView(2);
}

void worldPicture() {
    Point2 pone, ptwo, pthree;
    Color green, red, blue;

    green.red = green.blue = 0; green.green = 255;
    pone.x = 250; pone.y = 120; // Point2's for view

    red.green = red.blue = 0; red.red = 255;
    ptwo.x = 350; ptwo.y = 120; // Point2's for view

    blue.red = blue.green = 0; blue.blue = 255;
    pthree.x = 250; pthree.y = 320; // Point2's for view

    Rectangle one(pone, 100, 200);
    Rectangle two(ptwo, 100, 200);
    Rectangle three(pthree, 200, 100);
    one.setColor(green);
    one.drawView(6);
    two.setColor(red);
    two.drawView(7);
    three.setColor(blue);
    three.drawView(8);
}

void regionPicture() {
    Point2 pregion, ploc1, ploc2;
    Color green, red, blue;
    green.red = green.blue = 0; green.green = 255;
    pregion.x = 30; pregion.y = 30; // Point2's for view

    red.green = red.blue = 0; red.red = 255;
    ploc1.x = 575; ploc1.y = 125; // Point2's for view

    blue.red = blue.green = 0; blue.blue = 255;
    ploc2.x = 150; ploc2.y = 50; // Point2's for view

    Rectangle region(pregion, 880, 430);
    region.setColor(green);
    region.drawView(9);

    Rectangle loc1(ploc1, 175, 275);
    loc1.setColor(red);
    loc1.drawView('a');

    Rectangle loc2(ploc2, 325, 100);
    loc2.setColor(blue);
    loc2.drawView('b');
}

void locationPicture() {
    Point2 ploc;
    Color grey, brown;
    grey.red = grey.blue = grey.green = 128;
    ploc.x = 30; ploc.y = 30; // Point2's for view

    brown.green = 69; brown.blue = 19; brown.red = 139;

    Rectangle loc(ploc, 880, 430);
    loc.setColor(grey);
    loc.drawView('c');
    loc.setColor(brown);
    append(yaml, "    borderLeftWidth: 10\n");
    append(yaml, "    borderLeftColor: ");
    loc.send_color();
    append(yaml, "    borderTopWidth: 10\n");
    append(yaml, "    borderTopColor: ");
    loc.send_color();
    append(yaml, "    borderRightWidth: 10\n");
    append(yaml, "    borderRightColor: ");
    loc.send_color();
}

void combatPicture() {
    Point2 pview;
    Color red;
    red.green = red.blue = 0; red.red = 255;
    pview.x = 450; pview.y = 220; // Point2's for view
    Rectangle view(pview, 100, 200);
    view.setColor(red);
    view.drawView('d');
}

void endPicture() {
    Point2 ploc;
    Color white;
    white.red = white.blue = white.green = 255;
    ploc.x = 30; ploc.y = 30; // Point2's for view
    Rectangle loc(ploc, 880, 430);
    loc.setColor(white);
    loc.drawView('e');
    append(yaml, "  children: [Text_98]\n");
    append(yaml, "Text_", 'b', ":\n");
    append(yaml, "  style:\n");
    append(yaml, "    marginLeft: 150\n");
    append(yaml, "    marginTop: 100\n");
    append(yaml, "    color: gold\n");
    append(yaml, "    fontSize: 150\n");
    append(yaml, "  pos: ", 900, "\n");
    append(yaml, "  len: 900\n");
}



void make_button(int i)
{
  append(yaml, "Button_", i, ":\n");
  append(yaml, R"(
  style:
    position: absolute
    top: 150
    width: 225
    height: 700
    borderBottomWidth: 1
    borderBottomColor: gray
    backgroundColor: white)");
  append(yaml, "\n    left: ", 10 + 250*i, "\n");
  append(yaml, R"(
  on_touch:
    backgroundColor: white)");
  append(yaml, "\n");
}

void handle_button(int i) {
    if (i == 0) {
        write_at(mem, 500, "World");
        worldPicture();
    } else if (i == 1) {
        write_at(mem, 500, "Region");
        regionPicture();
    } else if (i == 2) {
        write_at(mem, 500, "Location");
        locationPicture();
    } else if (i == 3) {
        write_at(mem, 500, "Shop");
        npcPicture();
    } else if (i == 4) {
        write_at(mem, 500, "Combat");
        combatPicture();
    } else if (i == 5) {
        write_at(mem, 500, "End Screen");
        write_at(mem, 900, "Victory!");
        endPicture();
    }
}

int main() {
    init();

    if (length_of(yaml) < 30 || was_pressed(yaml, "Button_New")) {
    yaml[0] = 0;
    for (int i = 0; i < 6; ++i) 
      make_button(i);
    screen();
  } else {
    // check if a button was pressed
    for (int i = 0; i < 6; ++i) {
      if (was_pressed(yaml, "Button_", i)) {
        handle_button(i);
      }
    }
  }
  mem[50] = 0;
    quit();

}