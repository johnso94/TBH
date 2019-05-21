#ifndef _Circle_H_
#define _Circle_H_
#include "Shape.h"

class Circle : public Shape {
  protected:
    int radius;
  public:
    Circle() {
        radius = 5;
    }
    Circle(Point2 p, int r) : Shape(p) {
        radius = r;
    }
    Circle(istream & is) : Shape(is) {
        is >> radius;
    }
    void display();
    void draw();
};

#endif /* _Circle_H_ */