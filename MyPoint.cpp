//
// Created by daniel meltzer on 22/05/2018.
//

#include "MyPoint.h"

void MyPoint::setX(int x) {
    MyPoint::x = x;
}

void MyPoint::setY(int y) {
    MyPoint::y = y;
}
int MyPoint::getX() const {
    return x;
}

int MyPoint::getY() const {
    return y;
}

MyPoint::MyPoint(int x, int y) : x(x), y(y) {}



MyPoint::~MyPoint() = default;