cmake_minimum_required(VERSION 3.9)
project(CS_TAU_CPP_RPS)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c++14 -lmingw32 -Wall -Wextra -Werror -pedantic-errors")

add_executable(CS_TAU_CPP_RPS
        main.cpp
        AutoPlayerAlgorithm.cpp
        AutoPlayerAlgorithm.h
        Auxiliary.cpp
        Auxiliary.h
        BoardIO.cpp
        BoardIO.h
        FightInfo.h
        FilePlayerAlgorithm.cpp
        FilePlayerAlgorithm.h
        Game.cpp
        Game.h
        GameLogic.cpp
        GameLogic.h
        GameManager.cpp
        GameManager.h
        GamePiece.cpp
        GamePiece.h
        MyBoard.cpp
        MyBoard.h
        MyFightInfo.cpp
        MyFightInfo.h
        MyJokerChange.cpp
        MyJokerChange.h
        MyMove.cpp
        MyMove.h
        MyPiecePosition.cpp
        MyPiecePosition.h
        MyPoint.cpp
        MyPoint.h
        PlannedMove.cpp
        PlannedMove.h
        PiecePosition.h
        Move.h
        Board.h
        PlayerAlgorithm.h
        JokerChange.h
        Point.h)
