//
// Created by daniel meltzer on 22/05/2018.
//

#ifndef CS_TAU_CPP_EX_2_MYPOINT_H
#define CS_TAU_CPP_EX_2_MYPOINT_H


#include "Point.h"

class MyPoint : public Point {
public:
    int x;
    int y;

    MyPoint(int x, int y);

    ~MyPoint() override;

    explicit MyPoint(const Point &p) : x(p.getX()), y(p.getY()) {}

    int getX() const override;

    int getY() const override;

    void setX(int x);

    void setY(int y);
};


#endif //CS_TAU_CPP_EX_2_MYPOINT_H
