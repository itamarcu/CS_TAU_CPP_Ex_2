cmake_minimum_required(VERSION 3.9)
project(CS_TAU_CPP_Ex_2)

set(CMAKE_CXX_STANDARD 11)

add_executable(CS_TAU_CPP_Ex_2
        AutoPlayerAlogrithm.cpp
        AutoPlayerAlogrithm.h
        Auxiliary.cpp
        Auxiliary.h
        Board.h
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
        JokerChange.h
        main.cpp
        Move.h
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
        PiecePosition.h
        PlannedMove.cpp
        PlannedMove.h
        PlayerAlgorithm.h
        Point.h)
