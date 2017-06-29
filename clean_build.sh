#!/bin/sh

# clean stuff
rm -rf bin
mkdir bin

# build loader library
g++ -O3 -c -fPIC src/loader/load.cpp -o bin/load.o
g++ -O3 -shared bin/load.o -o bin/load.so

# build object files
g++ -O3 -c src/main/main.cpp -o bin/main.o
g++ -O3 -c src/main/engine.cpp -o bin/engine.o
g++ -O3 -c src/main/Player.cpp -o bin/Player.o
g++ -O3 -c src/main/Persona.cpp -o bin/Persona.o
g++ -O3 -c src/main/Bullet.cpp -o bin/Bullet.o

# link everything
g++ -O3 bin/main.o bin/engine.o bin/Player.o bin/Persona.o bin/Bullet.o bin/load.so -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -o bin/combat

# clean object files
rm bin/*.o

# run that shit
./run.sh
