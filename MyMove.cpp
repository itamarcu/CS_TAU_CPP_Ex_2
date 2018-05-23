//
// Created by Daniel Meltzer on 23/05/2018.
//

#include "MyMove.h"

const Point &MyMove::getFrom() const {
    return this->from;
}

const Point &MyMove::getTo() const {
    return this->to;
}

MyMove::~MyMove()  = default;