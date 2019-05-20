#include "Rectangle.h"
#include "sd_fun.h"
using namespace std;

void Rectangle::display() {
    cout << "Rectangle ";
    Shape::display();
    cout << width << " " << height;
}

void Rectangle::drawView() {
    append(yaml, "View_", id, ":\n");
    append(yaml, "  style:\n");
    append(yaml, "    position: absolute\n");
    double x0 = min(position.x, position.x + width);
    double y0 = min(position.y, position.y + height);
    append(yaml, "    left: ", x0, "\n");
    append(yaml, "    top: ", y0, "\n");
    append(yaml, "    width: ", abs(width), "\n");
    append(yaml, "    height: ", abs(height), "\n");
    append(yaml, "    backgroundColor: ");
    send_color();
}

void Rectangle::drawView(int num) {
    append(yaml, "View_", num, ":\n");
    append(yaml, "  style:\n");
    append(yaml, "    position: absolute\n");
    double x0 = min(position.x, position.x + width);
    double y0 = min(position.y, position.y + height);
    append(yaml, "    left: ", x0, "\n");
    append(yaml, "    top: ", y0, "\n");
    append(yaml, "    width: ", abs(width), "\n");
    append(yaml, "    height: ", abs(height), "\n");
    append(yaml, "    backgroundColor: ");
    send_color();
}

void Rectangle::drawView(char c) {
    append(yaml, "View_", c, ":\n");
    append(yaml, "  style:\n");
    append(yaml, "    position: absolute\n");
    double x0 = min(position.x, position.x + width);
    double y0 = min(position.y, position.y + height);
    append(yaml, "    left: ", x0, "\n");
    append(yaml, "    top: ", y0, "\n");
    append(yaml, "    width: ", abs(width), "\n");
    append(yaml, "    height: ", abs(height), "\n");
    append(yaml, "    backgroundColor: ");
    send_color();
}

void Rectangle::drawText_input(int pos) {
    append(yaml, "TextInput_last:\n");
    append(yaml, "  style:\n");
    append(yaml, "    position: absolute\n");
    double x0 = min(position.x, position.x + width);
    double y0 = min(position.y, position.y + height);
    append(yaml, "    left: ", x0, "\n");
    append(yaml, "    top: ", y0, "\n");
    append(yaml, "    width: ", abs(width), "\n");
    append(yaml, "    height: ", abs(height), "\n");
    append(yaml, "    fontSize: 20\n");
    append(yaml, "    borderColor: black\n");
    append(yaml, "    borderWidth: 5\n");
    append(yaml, "  pos: ", pos, "\n");
    append(yaml, "  len: 150\n");
}

void Rectangle::drawBorder(int w, Color bg, Color border) {
    setColor(bg);
    drawView();
    append(yaml, "    borderWidth: ", w, "\n");
    append(yaml, "    borderColor: ");
    setColor(border);
    send_color();
}