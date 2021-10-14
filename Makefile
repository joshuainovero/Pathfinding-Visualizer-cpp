CC := g++
CFLAGS := -Wall

OBJS := main.o App.o Textures.o Events.o
SFLIB := -LExternal/SFML/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
INCLUDES := -IExternal/SFML/include
SRC := src

all: Compile clean

Compile: $(OBJS)
	$(CC) $(CFLAGS) Assets/iconres.res $^  $(SFLIB)

main.o: $(SRC)/main.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

App.o: $(SRC)/App.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

Textures.o: $(SRC)/Textures.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

Events.o: $(SRC)/Events.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

clean:
	del *.o