//
// Created by Daniel Meltzer on 23/05/2018.
//

#ifndef CS_TAU_CPP_EX_2_MYMOVE_H
#define CS_TAU_CPP_EX_2_MYMOVE_H


#include "Move.h"

class MyMove : public Move {
public:
    const Point &getFrom() const override;

    const Point &getTo() const override;

    ~MyMove() override;

};


#endif //CS_TAU_CPP_EX_2_MYMOVE_H
