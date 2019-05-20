#ifndef _Shape_H_
#define _Shape_H_
#include"ColorPoint2.h"
#include <iostream>
#include <fstream>
using namespace std;

class Shape {
    static int num_shapes;
  protected:
    Color color;
    Point2 position;
    int id;
  public:
    Shape();
    Shape(Point2 p);
    Shape(istream & is);
    Color getColor();
    Point2 getPosition();
    void setColor(Color c);
    void setPosition(int x, int y);
    void display();
    void send_color();
};

#endif /* _Shape_H_ */