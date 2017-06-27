#!/bin/sh
rm -rf bin
mkdir bin

g++ -c src/main/main.cpp -o bin/main.o
g++ -c src/main/engine.cpp -o bin/engine.o
g++ -c src/main/Player.cpp -o bin/Player.o
g++ -c src/main/Persona.cpp -o bin/Persona.o
g++ -c src/main/Bullet.cpp -o bin/Bullet.o

g++ -c src/loader/load.cpp -o bin/loader.o

g++ bin/main.o bin/engine.o bin/Player.o bin/Persona.o bin/Bullet.o bin/loader.o -o bin/duelgraph -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

./bin/duelgraph ./dat/demo.stage
