CC := g++
CFLAGS := -Wall

OBJS := main.o App.o Node.o Graph.o Texture.o Algorithms.o
SFLIB := -LExternal/SFML/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
INCLUDES := -IExternal/SFML/include
SRC := src

all: Compile clean

Compile: $(OBJS)
	$(CC) $(CFLAGS) Assets/iconres.res $^ -mwindows $(SFLIB) -o "Pathfinding Visualizer - Joshua Inovero"

main.o: $(SRC)/main.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

App.o: $(SRC)/App.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

Node.o: $(SRC)/Node.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

Graph.o: $(SRC)/Graph.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

Texture.o: $(SRC)/Texture.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

Algorithms.o: $(SRC)/Algorithms.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<
clean:
	del *.o