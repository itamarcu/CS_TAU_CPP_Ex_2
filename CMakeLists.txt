cmake_minimum_required(VERSION 3.9)
project(CS_TAU_CPP_Ex_2)

set(CMAKE_CXX_STANDARD 11)

add_executable(CS_TAU_CPP_RPS main.cpp
        Auxiliary.cpp Auxiliary.h GameLogic.cpp GameLogic.h Classes.cpp Classes.h
        BoardIO.cpp BoardIO.h GameManager.cpp GameManager.h Game.cpp Game.h

        Board.h
        FightInfo.h
        JokerChange.h
        Move.h
        PiecePosition.h
        PlayerAlgorithm.h
        Point.h)