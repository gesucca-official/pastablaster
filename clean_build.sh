#!/bin/sh

# clean stuff
rm -rf bin
mkdir bin

# build loader library
g++ -c -fPIC src/loader/load.cpp -o bin/load.o
g++ -shared bin/load.o -o bin/load.so

# build object files
g++ -c src/main/main.cpp -o bin/main.o
g++ -c src/main/engine.cpp -o bin/engine.o
g++ -c src/main/Player.cpp -o bin/Player.o
g++ -c src/main/Persona.cpp -o bin/Persona.o
g++ -c src/main/Bullet.cpp -o bin/Bullet.o

# link everything
g++ bin/main.o bin/engine.o bin/Player.o bin/Persona.o bin/Bullet.o bin/load.so -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -o bin/combat

# clean object files
rm bin/*.o

# run that shit
./run.sh
