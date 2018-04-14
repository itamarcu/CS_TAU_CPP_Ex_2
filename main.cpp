#include <iostream>
#include "Auxiliary.h"
#include <fstream>
#include "BoardIO.h"

using std::cout;
using std::endl;


int main() {
    print_line("---Program started---");

    auto game = BoardIO::setup_game();

//    cout << "Address of piece in [1,1] is " << game->board[0][0] << endl;

    print_line("---Program ended---");
}