//
// Created by Daniel Meltzer on 23/05/2018.
//

#ifndef CS_TAU_CPP_EX_2_MYPIECEPOSITION_H
#define CS_TAU_CPP_EX_2_MYPIECEPOSITION_H


#include "PiecePosition.h"
#include "MyPoint.h"

class MyPiecePosition : public PiecePosition {
public:
    MyPiecePosition(char piece, char jokerRep, const MyPoint &position);

    const Point &getPosition() const override;

    char getPiece() const override;

    char getJokerRep() const override;

    ~MyPiecePosition() override;
private:
    char piece;
    char jokerRep;
    MyPoint position;
};


#endif //CS_TAU_CPP_EX_2_MYPIECEPOSITION_H
