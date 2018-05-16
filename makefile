COMP = g++-5.3.0

OBJS = Auxiliary.o BoardIO.o Classes.o Game.o GameLogic.o GameManager.o main.o 

EXEC = ex1
CPP_COMP_FLAG = -std=c++14 -Wall -Wextra \
-Werror -pedantic-errors -DNDEBUG

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) -o $@
Auxiliary.o: Auxiliary.cpp Auxiliary.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
BoardIO.o: BoardIO.cpp BoardIO.h Auxiliary.h Classes.h GameLogic.h Game.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Classes.o: Classes.cpp Classes.h Auxiliary.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Game.o: Game.cpp Game.h Classes.h Auxiliary.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
GameLogic.o: GameLogic.cpp GameLogic.h Classes.h Auxiliary.h Game.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
GameManager.o: GameManager.cpp GameManager.h Classes.h Auxiliary.h Game.h BoardIO.h GameLogic.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
main.o: main.cpp Auxiliary.h BoardIO.h Classes.h GameLogic.h Game.h GameManager.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
clean:
	rm -f $(OBJS) $(EXEC)
