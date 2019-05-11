#include "Circle.h"
#include "sd_fun.h"
using namespace std;

void Circle::display() {
    cout << "Circle ";
    Shape::display();
    cout << radius;
}

void Circle::draw() {
    append(yaml, "View_", id, ":\n");
    append(yaml, "  style:\n");
    append(yaml, "    position: absolute\n");
    append(yaml, "    borderRadius: 50%\n");
    append(yaml, "    left: ", position.x - radius, "\n");
    append(yaml, "    top: ", position.y - radius, "\n");
    append(yaml, "    width: ", 2*radius, "\n");
    append(yaml, "    height: ", 2*radius, "\n");
    send_color();
}