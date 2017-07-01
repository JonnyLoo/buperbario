CXX=g++
RM=rm -f
LIBS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

OBJS=test.cpp Object.cpp Unit.cpp Bario.cpp

all: bario

bario: $(OBJS)
	$(CXX) $(OBJS) -o test.exe $(LIBS)

clean:
	$(RM) *.out