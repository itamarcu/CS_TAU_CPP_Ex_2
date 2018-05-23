//
// Created by Daniel Meltzer on 22/05/2018.
// @authors Daniel Meltzer and Itamar Curiel

#include "MyPoint.h"

int MyPoint::getX() const {
    return x;
}

int MyPoint::getY() const {
    return y;
}

MyPoint::MyPoint(int x, int y) : x(x), y(y) {}



MyPoint::~MyPoint() = default;