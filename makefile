CXX=g++
RM=rm -f
LIBS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

OBJS=main.cpp Game.cpp

all: bario

bario: $(OBJS)
	$(CXX) $(OBJS) -o main.exe $(LIBS)

clean:
	$(RM) *.out