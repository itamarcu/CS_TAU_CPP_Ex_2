#include "MyPoint.h"

int MyPoint::getX() const {
    return x;
}

int MyPoint::getY() const {
    return y;
}

MyPoint::MyPoint(int x, int y) : x(x), y(y) {}



MyPoint::~MyPoint() = default;