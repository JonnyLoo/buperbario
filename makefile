CXX=g++
DEBUG=-g
RM=rm -f
LIBS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

OBJS=main.cpp Game.cpp Object.cpp Unit.cpp Bario.cpp
OBJST=test.cpp Object.cpp Unit.cpp Bario.cpp Koopa.cpp

all: bario

bario: $(OBJS)
	$(CXX) $(OBJS) -o main.exe $(LIBS)

test: $(OBJST)
	$(CXX) $(OBJST) -o test.exe $(LIBS)

debug: $(OBJS)
	$(CXX) $(DEBUG) $(OBJS) -o main.exe $(LIBS)

clean:
	$(RM) *.out *.exe