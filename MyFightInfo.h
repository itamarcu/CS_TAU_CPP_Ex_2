//
// Created by Daniel Meltzer on 23/05/2018.
//

#ifndef CS_TAU_CPP_EX_2_MYFIGHTINFO_H
#define CS_TAU_CPP_EX_2_MYFIGHTINFO_H


#include "FightInfo.h"
#include "MyPoint.h"
#define FIRST_PLAYER_CONST 1
#define SECOND_PLAYER_CONST 2
/*
 * @author: Daniel Meltzer and Itamar Curiel
 */
class MyFightInfo : public FightInfo {
public:
    MyFightInfo(int winner, const MyPoint &position, char firstPlayerPiece, char secondPlayerPiece);

    const Point &getPosition() const override;

    char getPiece(int player) const override;

    int getWinner() const override;

    ~MyFightInfo() override;

private:
    int winner;
    MyPoint position;
    char firstPlayerPiece;
    char secondPlayerPiece;

};


#endif //CS_TAU_CPP_EX_2_MYFIGHTINFO_H
