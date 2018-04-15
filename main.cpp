#include <iostream>
#include "Auxiliary.h"
#include <fstream>
#include "BoardIO.h"
#include "GameManager.h"

using std::cout;
using std::endl;


int main() {
    print_line("---Program started---");

    Game game = Game();
    BoardIO::setup_game(game);
    GameManager gm = GameManager(game);
    GameMoves moves = GameMoves();
    BoardIO::load_moves(moves);
    gm.run_moves(moves);
    BoardIO::store_game(game);
    print_line("---Program ended---");
}