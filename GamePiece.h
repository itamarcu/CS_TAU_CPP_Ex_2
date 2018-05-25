#ifndef CS_TAU_CPP_EX_2_GAMEPIECE_H
#define CS_TAU_CPP_EX_2_GAMEPIECE_H
/**
 * game piece type - for jokers, this is what their non-joker type is
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
     * initialize game piece
     * @param pieceType the type of piece (current "type", if it's a joker)
     * @param pieceIsJoker true if piece is a joker
     * @param playerIsFirst - true if it's the first false if it's the second
     */
    explicit GamePiece(bool playerIsFirst, GamePieceType pieceType, bool pieceIsJoker = false) : player(playerIsFirst),
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

    GamePieceType getType() const;
    static char chrFromType(const GamePieceType &gamePieceType);
};


GamePieceType type_from_char(char c);

char nonjoker_lowercase_char_from_type(GamePieceType gamePieceType);
#endif //CS_TAU_CPP_EX_2_GAMEPIECE_H
