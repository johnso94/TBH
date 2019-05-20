#include "Shape.h"
#include "sd_fun.h"
using namespace std;

int Shape::num_shapes = 0;

Shape::Shape() {
    color.red = 10;
    color.green = 0;
    color.blue = 0;
    position.x = 200;
    position.y = 200;
    id = num_shapes++;
}

Shape::Shape(Point2 p) {
    color.red = 10;
    color.green = 0;
    color.blue = 0;
    position = p; 
    id = num_shapes++;
}

Shape::Shape(istream & is) {
    is >> color.red >> color.green >> color.blue; // reads data from is to color
    is >> position.x >> position.y; // reads data from is to position
    id = num_shapes++;
}

Color Shape::getColor() {
    return color;
}

Point2 Shape::getPosition() {
    return position;
}

void Shape::setColor(Color c) {
    color = c;
}

void Shape::setPosition(int x, int y) {
    position.x = x;
    position.y = y;
}

void Shape::display() {
    color.display(); cout << "   ";
    position.display(); cout << "   ";
}

void Shape::send_color() {
    append(yaml, "rgb(", color.red);
    append(yaml, ",", color.green);
    append(yaml, ",", color.blue, ")\n");
}
