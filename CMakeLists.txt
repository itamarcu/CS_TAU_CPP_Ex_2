cmake_minimum_required(VERSION 3.9)
project(CS_TAU_CPP_Ex_2)

set(CMAKE_CXX_STANDARD 11)

add_executable(CS_TAU_CPP_Ex_2
        Auxiliary.cpp
        Auxiliary.h
        Board.h
        BoardIO.cpp
        BoardIO.h
        FightInfo.h
        Game.cpp
        Game.h
        GameLogic.cpp
        GameLogic.h
        GameManager.cpp
        GameManager.h
        JokerChange.h
        main.cpp
        Move.h
        PiecePosition.h
        PlayerAlgorithm.h
        Point.h MyPoint.cpp MyPoint.h MyBoard.cpp MyBoard.h GamePiece.cpp GamePiece.h PlannedMove.cpp PlannedMove.h)
