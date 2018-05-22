//
// Created by daniel meltzer on 22/05/2018.
//

#ifndef CS_TAU_CPP_EX_2_GAMEPIECE_H
#define CS_TAU_CPP_EX_2_GAMEPIECE_H
/**
 * game piece type according doesn't takes to account whether it's a joker
 */
enum GamePieceType {
    None, // empty spaces are this type
    Rock, Paper, Scissors, Bomb,//Jokers have a current type but also the boolean
    Flag // jokers can't be flags
};

class GamePiece {
public:
    bool player;
    GamePieceType type;
    bool isJoker;

    /**
     * initalize game piece
     * @param pieceType the type of piece
     * @param pieceIsJoker is the piece a joker - meaning it can change type
     * @param player - true if it's the first false if it's the second
     */
    explicit GamePiece(bool player, GamePieceType pieceType = None, bool pieceIsJoker = false) : player(player),
                                                                                                 type(pieceType),
                                                                                                 isJoker(pieceIsJoker) {}

    /**
     *
     * @return char representing type and player. Jokers give J always.
     */
    char to_char();

    /**
     *
     * @return true if this unit can move (if it is not a flag or a bomb or a bomb-joker)
     */
    bool canMove();
};



GamePieceType type_from_char(char c);
#endif //CS_TAU_CPP_EX_2_GAMEPIECE_H
