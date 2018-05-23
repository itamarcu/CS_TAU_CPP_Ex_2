//
// Created by Daniel Meltzer on 23/05/2018.
//

#ifndef CS_TAU_CPP_EX_2_MYFIGHTINFO_H
#define CS_TAU_CPP_EX_2_MYFIGHTINFO_H


#include "FightInfo.h"

/*
 * @author: Daniel Meltzer and Itamar Curiel
 */
class MyFightInfo : public FightInfo {
public:
    const Point &getPosition() const override;

    char getPiece(int player) const override;

    int getWinner() const override;

    ~MyFightInfo() override;
};


#endif //CS_TAU_CPP_EX_2_MYFIGHTINFO_H
