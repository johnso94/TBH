#ifndef _ColorPoint2_H_
#define _ColorPoint2_H_
#include<iostream>
using namespace std;

struct Color {
    int red;
    int green;
    int blue;
    void display() {
        cout << red << " " << green << " " << blue;
    }
};

struct Point2 {
    int x;
    int y;
    void display() {
        cout << x << " " << y;
    }
};

#endif /* _ColorPoint2_H_ */