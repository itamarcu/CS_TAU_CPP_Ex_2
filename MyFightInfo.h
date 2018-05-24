//
// Created by Daniel Meltzer on 23/05/2018.
//

#ifndef CS_TAU_CPP_EX_2_MYFIGHTINFO_H
#define CS_TAU_CPP_EX_2_MYFIGHTINFO_H


#include "FightInfo.h"
#include "MyPoint.h"
#define FIRST_PLAYER_CONST 1
#define SECOND_PLAYER_CONST 2

/**
 * @authors: Daniel Meltzer and Itamar Curiel
 */
class MyFightInfo : public FightInfo {
public:
    MyFightInfo(int winner, const MyPoint &position, char firstPlayerPiece, char secondPlayerPiece);

    /**
     * get position of fight
     * @return fight position
     */
    const Point &getPosition() const override;

    /**
     * get piece
     * @param player for player 1 this should be FIRST_PLAYER_CONST, for player 2 this should be SECOND_PLAYER_CONST
     * @return piece char
     */
    char getPiece(int player) const override;

    /**
     * get fight winner
     * @return 0 - if both lose / tie, FIRST_PLAYER_CONST - if first player wins and SECOND_PLAYER_CONST - if
     * second player wins
     */
    int getWinner() const override;

    ~MyFightInfo() override;

private:
    int winner;
    MyPoint position;
    char firstPlayerPiece;
    char secondPlayerPiece;

};


#endif //CS_TAU_CPP_EX_2_MYFIGHTINFO_H
