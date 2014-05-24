CXXFLAGS = -ansi -Wall -Werror -pedantic -std=c++11 -DSFML_STATIC
INCFLAGS = -Iinclude -Idepend/include
LIBFLAGS = -Ldepend/lib/SFML -lsfml-graphics-s -lsfml-window-s -lsfml-system-s

default: all

all: folders main CommandInfo SpriteModifier
	g++ $(CXXFLAGS) $(INCFLAGS) obj/SpriteModifier.o obj/CommandInfo.o \
	obj/main.o -o bin/SpriteUtility $(LIBFLAGS)

folders:
	mkdir -p bin obj data

main:
	g++ $(CXXFLAGS) $(INCFLAGS) -c src/main.cpp -o obj/main.o

CommandInfo:
	g++ $(CXXFLAGS) $(INCFLAGS) -c src/CommandInfo.cpp -o obj/CommandInfo.o

SpriteModifier:
	g++ $(CXXFLAGS) $(INCFLAGS) -c src/SpriteModifier.cpp -o obj/SpriteModifier.o

clean_all: clean
	rm -rf data

clean:
	rm -rf -f bin obj
