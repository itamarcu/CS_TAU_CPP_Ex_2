//
// Created by Daniel Meltzer on 23/05/2018.
//

#include "MyMove.h"

/**
 * get move starting point
 * @return Point subclass instance for starting point representation
 */
const Point &MyMove::getFrom() const {
    return from;
}
/**
 * get move destination
 * @return Point subclass instance for destination representation
 */
const Point &MyMove::getTo() const {
    return to;
}

MyMove::~MyMove()  = default;