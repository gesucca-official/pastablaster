#!/bin/sh
rm -rf bin
mkdir bin

g++ -c src/main.cpp -o bin/main.o
g++ -c src/engine.cpp -o bin/engine.o
g++ -c src/Player.cpp -o bin/Player.o
g++ -c src/Persona.cpp -o bin/Persona.o
g++ bin/main.o bin/engine.o bin/Player.o bin/Persona.o -o bin/duelgraph -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

./bin/duelgraph
