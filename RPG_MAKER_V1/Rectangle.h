#ifndef _Rectangle_H_
#define _Rectangle_H_
#include "Shape.h"

class Rectangle : public Shape {
  protected:
    int width;
    int height;
  public:
    Rectangle() : Shape() {
      width = 20;
      height = 25;
    };
    Rectangle(Point2 p, int w, int h) : Shape(p) {
      width = w;
      height = h;
    };
    Rectangle(istream & is) : Shape(is) {
      is >> width >> height;
    };
    void display();
    void drawView();
    void drawView(int num);
    void drawView(char c);
    void drawText_input(int pos);
    void drawButton();
    void drawBorder(int w, Color bg, Color border);
};

#endif /* _Rectangle_H_ */